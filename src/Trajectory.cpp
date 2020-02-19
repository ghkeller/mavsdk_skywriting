// Trajectory.cpp

#include <iostream>
#include <memory>
#include <chrono>

#include <LetterWaypoint.h>
#include <Trajectory.h>
#include <MissionVector.h>
#include <pid_control.h>

#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#define TRAV_TIME_OVERSHOOT 1.0f

namespace mavsdk_skywriting
{

//registers waypoint hit without a timeout
bool Trajectory::reached_waypoint(Offboard::PositionNEDYaw pos, std::shared_ptr<mavsdk::Telemetry> telemetry, float _wp_hit_thres) {
		Telemetry::PositionVelocityNED curr_pos = telemetry->position_velocity_ned();
	if (abs(curr_pos.position.north_m - pos.north_m) < _wp_hit_thres &&
		abs(curr_pos.position.east_m - pos.east_m) < _wp_hit_thres &&
		abs(curr_pos.position.down_m - pos.down_m) < _wp_hit_thres) {
		std::cout << "Waypoint hit. x: " << pos.north_m
			<< " y: " << pos.east_m
			<< " z: " << pos.down_m << std::endl;
		return true;
	} else {
		return false;
	}

}

//registers a waypoint hit either by surpassing the predicted time or registering hitting the waypint bubble
bool Trajectory::reached_waypoint(Offboard::PositionNEDYaw pos, std::shared_ptr<mavsdk::Telemetry> telemetry,
        float expected_traversal_time, std::chrono::duration<double> elapsed_time, float _wp_hit_thres) {
    Telemetry::PositionVelocityNED curr_pos = telemetry->position_velocity_ned();
    if ((abs(curr_pos.position.north_m - pos.north_m) < _wp_hit_thres &&
        abs(curr_pos.position.east_m - pos.east_m) < _wp_hit_thres &&
        abs(curr_pos.position.down_m - pos.down_m) < _wp_hit_thres) || elapsed_time.count() > expected_traversal_time + TRAV_TIME_OVERSHOOT) {
        std::cout << "Waypoint hit. x: " << pos.north_m
            << " y: " << pos.east_m
            << " z: " << pos.down_m << std::endl;
        return true;
    } else {
        return false;
    }
}

void TrajNoPref::traverse(std::shared_ptr<mavsdk::Offboard> offboard,
            std::shared_ptr<mavsdk::Telemetry> telemetry, float _wp_hit_thres, float _speed) {
    
    //execute direct wp traversal
    offboard->set_position_ned(target_wp);
    while(!reached_waypoint(target_wp,telemetry,_wp_hit_thres)); //keep traversing until we're at our waypoint
}

// this is a blocking function
void TrajStraight::traverse(std::shared_ptr<mavsdk::Offboard> offboard,
    std::shared_ptr<mavsdk::Telemetry> telemetry,
    float _wp_hit_thres, float _speed) {

    //initialize our PID controller
    pid_init(3.0f,0.000000f,0.0000f);

    //current coords
    Telemetry::PositionVelocityNED curr_pos = telemetry->position_velocity_ned();
    std::cout << "Where we are: " << curr_pos << std::endl;

    float deltax = target_wp.north_m - curr_pos.position.north_m;
    float deltay = target_wp.east_m - curr_pos.position.east_m;
    float deltaz = target_wp.down_m - curr_pos.position.down_m;

    std::cout << "How far to go x: " << deltax << std::endl;
    std::cout << "How far to go y: " << deltay << std::endl;
    std::cout << "How far to go z: " << deltaz << std::endl;
    //compute the expected traversal time and velocity in each direction
    float dist_mag = sqrt(pow(deltax,2) + pow(deltay,2) + pow(deltaz,2));
    float t = dist_mag/_speed;
    float vx = _speed*deltax/dist_mag;
    float vy = _speed*deltay/dist_mag;
    float vz = _speed*deltaz/dist_mag;

    //set the target velocities and wait for EITHER us to reach that waypoint OR to overshoot slightly (measured time elapsed)
    offboard->set_velocity_body({vx, vy, vz, 0.0f});
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now(), end;
    std::chrono::duration<double> elapsed_seconds;  
    do {
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;

        //calculate deviation from our line
        float approx_y = vy*elapsed_seconds.count() + curr_pos.position.east_m;
        float approx_z = vz*elapsed_seconds.count() + curr_pos.position.down_m;
        Telemetry::PositionVelocityNED _curr_pos = telemetry->position_velocity_ned();
        float err_y = approx_y - _curr_pos.position.east_m;
        float err_z = approx_z - _curr_pos.position.down_m;
        float err_mag = sqrt(pow(err_y,2) + pow(err_z,2));
        float u = pid_step(err_mag);

        offboard->set_velocity_body({vx, vy+u*(err_y/err_mag), vz+u*(err_z/err_mag), 0.0f});
        //sleep_for(std::chrono::microseconds(100));

    } while(!reached_waypoint(target_wp,telemetry,t,elapsed_seconds,_wp_hit_thres));

    // go to the true waypoint to reset (because we might have missed by a bit)
    //offboard->set_position_ned(*it);
    //while(!reached_waypoint(*it,telemetry));
    // we've hit the waypoint, so stop for two seconds
    offboard->set_velocity_ned({0.0f, 0.0f, 0.0f, 0.0f});
    sleep_for(seconds(1));

}

// this is a blocking function
void TrajCurved::traverse(std::shared_ptr<mavsdk::Offboard> offboard,
    std::shared_ptr<mavsdk::Telemetry> telemetry,
    float _wp_hit_thres, float _speed) {
    //adjust for our accumulated error
        // it->east_m += y_err; (it+1)->east_m += y_err;
        // it->down_m += z_err; (it+1)->down_m += z_err;

    //initialize our PID controller
    pid_init(3.0f,0.000000f,0.0000f);

    float dir_scalar;
    if (direction == Direction::CLOCKWISE)
        dir_scalar = -1.0f;
    else 
        dir_scalar = 1.0f; // for counter clockwise; only other option

    //current coords
    Telemetry::PositionVelocityNED curr_pos = telemetry->position_velocity_ned();
    std::cout << "Where we are: " << curr_pos << std::endl;

    //at the beginning, figure out approx how long this should take
    float theta1 = atan2(center_wp.down_m - curr_pos.position.down_m,curr_pos.position.east_m - center_wp.east_m); //theta between curr_pos and theta 0
    std::cout << "Theta1 " << theta1 << std::endl;
    float theta2 = atan2(center_wp.down_m - target_wp.down_m,target_wp.east_m - center_wp.east_m);
    std::cout << "Theta2 " << theta2 << std::endl;
    float R = sqrt(pow(curr_pos.position.down_m - center_wp.down_m,2) + pow(curr_pos.position.east_m - center_wp.east_m,2));
    std::cout << "R " << R << std::endl;
    float theta_tot = dir_scalar*(theta2 - theta1);
    if (theta_tot < 0.0f)
        theta_tot += 2*M_PI;
    std::cout << "theta_tot " << theta_tot << std::endl;
    float t = abs(theta_tot*R/_speed);
    std::cout << "t " << t << std::endl;

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now(), end; 
    std::chrono::duration<double> elapsed_seconds;
    do {
        //compute theta
        curr_pos = telemetry->position_velocity_ned();
        float deltay = curr_pos.position.east_m - center_wp.east_m;
        float deltaz = curr_pos.position.down_m - center_wp.down_m;
        float theta = atan2(deltaz,deltay);

        //step through the pid controller
        float y_exp = R*cos(theta) + center_wp.east_m;
        float z_exp = R*sin(theta) + center_wp.down_m;
        float err_y = y_exp - curr_pos.position.east_m;
        float err_z = z_exp - curr_pos.position.down_m;
        float err_mag = sqrt(pow(err_y,2) + pow(err_z,2));
        float u = pid_step(err_mag);

        //get linear velocities from this 
        float vy = _speed*sin(theta)*dir_scalar;
        float vz = -_speed*cos(theta)*dir_scalar;

        //get adjustment for discrete system
        float half_delta_theta = -atan2(DELTA_D_APPROX,R)/2*dir_scalar;
        float vy_adj = vy*cos(half_delta_theta) - vz*sin(half_delta_theta);
        float vz_adj = vy*sin(half_delta_theta) + vz*cos(half_delta_theta);

        //set the target velocities and wait for EITHER us to reach that waypoint OR to overshoot slightly (measured time elapsed)
        offboard->set_velocity_body({0.0, vy_adj+u*(err_y/err_mag), vz_adj+u*(err_z/err_mag), 0.0f});

        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start; 
    } while(!reached_waypoint(target_wp,telemetry,t,elapsed_seconds,_wp_hit_thres));


    // go to the true waypoint to reset (because we might have missed by a bit)
    //offboard->set_position_ned(*(it+1));
    //while(!reached_waypoint(*(it+1),telemetry));
    // we've hit the waypoint, so stop for two seconds
    offboard->set_velocity_ned({0.0f, 0.0f, 0.0f, 0.0f});
}

}


