// VectorOperations.cpp

#include <vector>
#include <iostream>
#include <string>

#include <LetterWaypoint.h>
#include <Trajectory.h>
#include <MissionVector.h>
#include <Common.h>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

using namespace std;

namespace mavsdk_skywriting {

float MissionVector::getMissionLength() {
    return mission_width;
}

//creates a vector of setpoints based on an input string
MissionVector::MissionVector(std::string str, float _letter_height,
	float _letter_spacing, float _row_spacing, float _scale_factor, float _whitespace_width)
{
    std::vector<Letter *> _mission_wps;

    float line = 0.0f;
    float running_text_width = 0.0f;
	for (char const &c: str) {
		if (c == '\n') {

			line += 1.0f;
            running_text_width = 0.0f;
            continue;
		} else if (c == ' ') {
            running_text_width += _whitespace_width;
            continue;
        }

		Letter *new_letter = new Letter();//*(_letters->characterLookupTable[c])); adding to debug temporarily
        std::cout << "Fetched: " << std::endl;
        new_letter->print();
		
        for (Trajectory *_traj : new_letter->trajs) {
            Offboard::PositionNedYaw adjustment = {0.0f,0.0f,0.0f,0.0f};
            adjustment.east_m = running_text_width;
            adjustment.down_m = (_row_spacing + _letter_height)*line;
            *_traj += adjustment;
            *_traj *= _scale_factor;
        }
        std::cout << "After adjusting for placement and scaling: " << std::endl;
        new_letter->print();

        running_text_width += (new_letter->letter_width + _letter_spacing);
		letter_waypoints.push_back(new_letter);
	}

    //update the mission vector description
    mission_width = running_text_width;

}

bool MissionVector::execute(mavsdk::Offboard &offboard, mavsdk::Telemetry &telemetry,
                                 bool error_comp, float _wp_hit_thres, float _speed)
{
    std::cout << "we're trying to be in offboard now..." << std::endl;

    // Send it once before starting offboard, otherwise it will be rejected.
    const Offboard::VelocityNedYaw stay{};
    offboard.set_velocity_ned(stay);

    Offboard::Result offboard_result = offboard.start();
    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard start failed: " << offboard_result << '\n';
        return false;
    }

    std::cout << "Offboard started\n";

    // set the origin
    Telemetry::PositionVelocityNed text_origin = telemetry.position_velocity_ned();
    for (mavsdk_skywriting::Letter *_letter : letter_waypoints) {
        std::cout << "Before we've adjusted for start position: " << std::endl;
        _letter->print();
        for (mavsdk_skywriting::Trajectory *_traj : _letter->trajs) {
            *_traj += text_origin.position;
        }
    }

    // traverse the waypoints
    for (mavsdk_skywriting::Letter *_letter : letter_waypoints) {
        std::cout << "After we've adjusted for start position: " << std::endl;
        _letter->print();

        Offboard::PositionNedYaw err = {0.0f,0.0f,0.0f,0.0f};

        for (mavsdk_skywriting::Trajectory * _traj : _letter->trajs) {
            // if we aren't doing err correction, will be 0
            *_traj += err;
            _traj->print();
            _traj->traverse(offboard,telemetry,_wp_hit_thres,_speed);
            sleep_for(seconds(1));

            if (error_comp == true) {
                Telemetry::PositionVelocityNed _curr_pos = telemetry.position_velocity_ned();
                err.east_m += _curr_pos.position.east_m - _traj->target_wp.east_m;
                err.down_m += _curr_pos.position.down_m - _traj->target_wp.down_m;
            }
        }
    }

    return true;
}

}
