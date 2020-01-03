// Trajectory.h

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

// a trajectory in the mavsdk_skywriting namespace is an object
// with at least a target waypoint and a "traverse" blocking function

// the abstract class "Trajectory" is the base class for the other
// trajectory types: TrajNoPref, TrajStraight, and TrajCurved

#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <thread>

#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::chrono::seconds;
using namespace mavsdk;

#define DELTA_D_APPROX 0.3f

namespace mavsdk_skywriting
{
	class Trajectory
	{
	protected:
	//registers a waypoint hit when inside the waypoint bubble
	bool reached_waypoint(Offboard::PositionNEDYaw pos, std::shared_ptr<mavsdk::Telemetry> telemetry, float _wp_hit_thres=0.3);
	bool reached_waypoint(Offboard::PositionNEDYaw pos, std::shared_ptr<mavsdk::Telemetry> telemetry,
        float expected_traversal_time, std::chrono::duration<double> elapsed_time, float _wp_hit_thres=0.3);

	public:
		Offboard::PositionNEDYaw target_wp;

	    Trajectory();
	    Trajectory(Offboard::PositionNEDYaw _target_wp) { target_wp = _target_wp; }
	    virtual void traverse(std::shared_ptr<mavsdk::Offboard> offboard,
	    	std::shared_ptr<mavsdk::Telemetry> telemetry, float _wp_hit_thres, float _speed) = 0;

	    Trajectory(const Trajectory &_traj) { target_wp= _traj.target_wp; } 
	    // void operator +(Offboard::PositionNEDYaw _a) {
	    // 	float north_m = target_wp.north_m + _a.north_m;
	    // 	float east_m = target_wp.east_m + _a.east_m;
	    // 	float down_m = target_wp.down_m + _a.down_m;
	    // 	return new Trajectory({north_m,east_m,down_m,0.0f});
	    // }

    	virtual Trajectory *copy() = 0;
	    virtual void print() = 0;

	    virtual void operator +=(Offboard::PositionNEDYaw _a) {
	    	target_wp.north_m = target_wp.north_m + _a.north_m;
	    	target_wp.east_m = target_wp.east_m + _a.east_m;
	    	target_wp.down_m = target_wp.down_m + _a.down_m;
	    	target_wp.yaw_deg = target_wp.yaw_deg + _a.yaw_deg;
	    }

	    virtual void operator +=(Telemetry::PositionNED _a) {
	    	target_wp.north_m = target_wp.north_m + _a.north_m;
	    	target_wp.east_m = target_wp.east_m + _a.east_m;
	    	target_wp.down_m = target_wp.down_m + _a.down_m;
	    }

	    virtual void operator *=(float _a) {
	    	target_wp.north_m = target_wp.north_m * _a;
	    	target_wp.east_m = target_wp.east_m * _a;
	    	target_wp.down_m = target_wp.down_m * _a;
	    }
	};

	class TrajNoPref : public Trajectory
	{
	public:
		TrajNoPref();
		TrajNoPref(Offboard::PositionNEDYaw _target_wp) : Trajectory(_target_wp) { target_wp=_target_wp; }
	    // this is a blocking function
	    TrajNoPref* copy() {
	    	return new TrajNoPref({target_wp.north_m,
	    							target_wp.east_m,
	    							target_wp.down_m,
	    							0.0f});
	    }
	    TrajNoPref(const TrajNoPref &_traj) : Trajectory(_traj) { std::cout << "using" << std::endl; target_wp = _traj.target_wp; }

	    void traverse(std::shared_ptr<mavsdk::Offboard> offboard,
	    	std::shared_ptr<mavsdk::Telemetry> telemetry, float _wp_hit_thres, float _speed);

	    void print() { std::cout << "TrajNoPref: " << target_wp << std::endl; }
	};

	class TrajStraight : public Trajectory
	{
	public:
		TrajStraight();
		TrajStraight(Offboard::PositionNEDYaw _target_wp) : Trajectory(_target_wp) { target_wp=_target_wp;}
	    
		TrajStraight* copy() {
	    	return new TrajStraight({target_wp.north_m,
	    							target_wp.east_m,
	    							target_wp.down_m,
	    							0.0f});
	    }

	    TrajStraight(const TrajStraight &_traj) : Trajectory(_traj) { std::cout << "using" << std::endl; target_wp = _traj.target_wp; }

	    // this is a blocking function
	    void traverse(std::shared_ptr<mavsdk::Offboard> offboard,
	    	std::shared_ptr<mavsdk::Telemetry> telemetry,
	    	float _wp_hit_thres, float _speed);

	    void print() { std::cout << "TrajStraight: " << target_wp << std::endl; }
	};

	class TrajCurved : public Trajectory
	{
	public:
		enum Direction {
			CLOCKWISE,
			COUNTER_CLOCKWISE
		};

		Direction direction;
		Offboard::PositionNEDYaw center_wp;

		TrajCurved();
		TrajCurved(Offboard::PositionNEDYaw _target_wp,
				Offboard::PositionNEDYaw _center_wp,
				Direction _direction) : Trajectory(_target_wp) {
				center_wp = _center_wp;
				direction = _direction;
				}
		TrajCurved(const TrajCurved &_traj) : Trajectory(_traj) { std::cout << "using" << std::endl; target_wp = _traj.target_wp; }

		void operator +=(Offboard::PositionNEDYaw _a) {
	    	target_wp.north_m = target_wp.north_m + _a.north_m;
	    	target_wp.east_m = target_wp.east_m + _a.east_m;
	    	target_wp.down_m = target_wp.down_m + _a.down_m;
			target_wp.yaw_deg = target_wp.yaw_deg + _a.yaw_deg;
	    
	    	center_wp.north_m = center_wp.north_m + _a.north_m;
	    	center_wp.east_m = center_wp.east_m + _a.east_m;
	    	center_wp.down_m = center_wp.down_m + _a.down_m;
	    	center_wp.yaw_deg = center_wp.yaw_deg + _a.yaw_deg;
	    }

	    void operator +=(Telemetry::PositionNED _a) {
	    	target_wp.north_m = target_wp.north_m + _a.north_m;
	    	target_wp.east_m = target_wp.east_m + _a.east_m;
	    	target_wp.down_m = target_wp.down_m + _a.down_m;

	    	center_wp.north_m = center_wp.north_m + _a.north_m;
	    	center_wp.east_m = center_wp.east_m + _a.east_m;
	    	center_wp.down_m = center_wp.down_m + _a.down_m;
	    }

	    void operator *=(float _a) {
	    	target_wp.north_m = target_wp.north_m * _a;
	    	target_wp.east_m = target_wp.east_m * _a;
	    	target_wp.down_m = target_wp.down_m * _a;

	    	center_wp.north_m = center_wp.north_m *_a;
	    	center_wp.east_m = center_wp.east_m *_a;
	    	center_wp.down_m = center_wp.down_m *_a;
	    }
	    
		TrajCurved* copy() {
	    	return new TrajCurved({target_wp.north_m,
	    							target_wp.east_m,
	    							target_wp.down_m,
	    							0.0f},
	    							{center_wp.north_m,
	    							center_wp.east_m,
	    							center_wp.down_m,
	    							0.0f},
	    							direction);
	    }

	    // this is a blocking function
	    void traverse(std::shared_ptr<mavsdk::Offboard> offboard,
	    	std::shared_ptr<mavsdk::Telemetry> telemetry,
	    	float _wp_hit_thres, float _speed);

	    void print() { std::cout << "TrajCurved: " << target_wp << center_wp << std::endl; }
	};
}

#endif // TRAJECTORY_H