// VectorOperations.cpp

#include <vector>
#include <iostream>
#include <string>

#include <LetterWaypoint.h>
#include <Trajectory.h>
#include <MissionVectorOperations.h>
#include <Common.h>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

using namespace std;

extern mavsdk_skywriting::LetterWaypoints* _letters;

namespace mavsdk_skywriting {

//creates a vector of setpoints based on an input string
vector<Letter *> MissionVectorOperations::stringToMissionVec(std::string str, float _letter_height,
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

		Letter *new_letter = new Letter(*(_letters->characterLookupTable[c]));
        std::cout << "Fetched: " << std::endl;
        new_letter->print();
		
        for (Trajectory *_traj : new_letter->trajs) {
            Offboard::PositionNEDYaw adjustment = {0.0f,0.0f,0.0f,0.0f};
            adjustment.east_m = running_text_width;
            adjustment.down_m = (_row_spacing + _letter_height)*line;
            *_traj += adjustment;
            *_traj *= _scale_factor;
        }
        std::cout << "After adjusting for placement and scaling: " << std::endl;
        new_letter->print();

        running_text_width += (new_letter->letter_width + _letter_spacing);
		_mission_wps.push_back(new_letter);
	}
	return _mission_wps;
}

bool MissionVectorOperations::execute(std::shared_ptr<mavsdk::Offboard> offboard, std::shared_ptr<mavsdk::Telemetry> telemetry,
    vector<mavsdk_skywriting::Letter *> _letter_waypoints, bool error_comp, float _wp_hit_thres, float _speed)
{
    const std::string offb_mode = "NED";
    // Send it once before starting offboard, otherwise it will be rejected.
    offboard->set_velocity_ned({0.0f, 0.0f, 0.0f, 0.0f});

    Offboard::Result offboard_result = offboard->start();
    offboard_error_exit(offboard_result, "Offboard start failed");
    offboard_log(offb_mode, "Offboard started");

    // set the origin
    Telemetry::PositionVelocityNED text_origin = telemetry->position_velocity_ned();
    for (mavsdk_skywriting::Letter *_letter : _letter_waypoints) {
        std::cout << "Before we've adjusted for start position: " << std::endl;
        _letter->print();
        for (mavsdk_skywriting::Trajectory *_traj : _letter->trajs) {
            *_traj += text_origin.position;
        }
    }

    // traverse the waypoints
    for (mavsdk_skywriting::Letter *_letter : _letter_waypoints) {
        std::cout << "After we've adjusted for start position: " << std::endl;
        _letter->print();

        Offboard::PositionNEDYaw err = {0.0f,0.0f,0.0f,0.0f};

        for (mavsdk_skywriting::Trajectory * _traj : _letter->trajs) {
            // if we aren't doing err correction, will be 0
            *_traj += err;
            _traj->print();
            _traj->traverse(offboard,telemetry,_wp_hit_thres,_speed);
            sleep_for(seconds(1));

            if (error_comp == true) {
                Telemetry::PositionVelocityNED _curr_pos = telemetry->position_velocity_ned();
                err.east_m += _curr_pos.position.east_m - _traj->target_wp.east_m;
                err.down_m += _curr_pos.position.down_m - _traj->target_wp.down_m;
            }
        }
    }

    return true;
}

}
