/**
 * offboard_skywriting_main.cpp
 * a skywriting program by Gordon Keller based on:
 * 
 * @file offboard_velocity.cpp
 * @brief Example that demonstrates offboard velocity control in local NED and body coordinates
 *
 * @authors Author: Julian Oes <julian@oes.ch>,
 *                  Shakthi Prashanth <shakthi.prashanth.m@intel.com>
 * @date 2017-10-17
 */

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
#include <array>
#include <map>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

#include <Common.h>
#include <LetterWaypoint.h>
#include <Trajectory.h>
#include <MissionVector.h>
#include <Safeguard.h>

using namespace mavsdk;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::chrono::seconds;

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

#define WP_HIT_THRES 0.05f // m

#define LETTER_HEIGHT 3.0f // m
#define LETTER_SPACING 0.25f // m
#define ROW_SPACING 0.25f // m
#define SCALE_FACTOR 10.0f // 
#define WHITESPACE_WIDTH 2.0f // m

#define TAKEOFF_ALTITUDE 100.0f // m
#define TARGET_YZ_VEL 1.0f // m/s
#define TRAV_TIME_OVERSHOOT 3.0f // s

#define DELTA_D_APPROX 0.3f // m
#define ERR_COMP true // should we reset our curves 

mavsdk_skywriting::LetterWaypoints* _letters;

using namespace mavsdk_skywriting;

void usage(std::string bin_name)
{
    std::cout << NORMAL_CONSOLE_TEXT << "Usage : " << bin_name << " <connection_url>" << std::endl
              << "Connection URL format should be :" << std::endl
              << " For TCP : tcp://[server_host][:server_port]" << std::endl
              << " For UDP : udp://[bind_host][:bind_port]" << std::endl
              << " For Serial : serial:///path/to/serial/dev[:baudrate]" << std::endl
              << "For example, to connect to the simulator use URL: udp://:14540" << std::endl;
}

int main(int argc, char** argv)
{
	//instatiate vars
    Mavsdk dc;
    std::string connection_url;
    std::string mission_string = "";
    ConnectionResult connection_result;

    // initialize our lookup table
    _letters = new LetterWaypoints();

    
    MissionVector *mission_letters;  
    if (argc == 3) {

        //process the mission string, returning a vector of position setpoints
        mission_letters = new MissionVector(argv[2], LETTER_HEIGHT,
    LETTER_SPACING, ROW_SPACING, SCALE_FACTOR, WHITESPACE_WIDTH);
    	//establish connection with the vehicle
        connection_url = argv[1];
        connection_result = dc.add_any_connection(connection_url);
    } else {
        usage(argv[0]);
        return 1;
    }

    // check if connection to vehicle worked
    if (connection_result != ConnectionResult::SUCCESS) {
        std::cout << ERROR_CONSOLE_TEXT
                  << "Connection failed: " << connection_result_str(connection_result)
                  << NORMAL_CONSOLE_TEXT << std::endl;
        return 1;
    }

    // Wait for the system to connect via heartbeat
    while (!dc.is_connected()) {
        std::cout << "Wait for system to connect via heartbeat" << std::endl;
        sleep_for(seconds(1));
    }

    // System got discovered.
    System& system = dc.system();
    auto action = std::make_shared<Action>(system);
    auto offboard = std::make_shared<Offboard>(system);
    auto telemetry = std::make_shared<Telemetry>(system);
    auto geofence = std::make_shared<Geofence>(system)

    // vehicle will need to initialize before we can take control
    while (!telemetry->health_all_ok()) {
        std::cout << "Waiting for system to be ready" << std::endl;
        sleep_for(seconds(1));
    }
    std::cout << "System is ready" << std::endl;

    //if we haven't taken off yet, takeoff
    if (!telemetry->in_air()) {
	    Action::Result tko_height_result = action->set_takeoff_altitude(TAKEOFF_ALTITUDE);
	    action_error_exit(tko_height_result, "Setting takeoff altitude failed");
	    std::cout << "Takeoff altitude set to " << TAKEOFF_ALTITUDE << "m" << std::endl;

	    Action::Result arm_result = action->arm();
	    action_error_exit(arm_result, "Arming failed");
	    std::cout << "Armed" << std::endl;

	    Action::Result takeoff_result = action->takeoff();
	    action_error_exit(takeoff_result, "Takeoff failed");
	    std::cout << "In Air..." << std::endl;
	    sleep_for(seconds(50));
	}

    //set a geofence for the missions
    Safeguard::setGeofence({0.0f,0.0f,0.0f,0.0f}, 0.0f, 0.0f, 0.0f, geofence);

    //  using local NED co-ordinates
    bool ret = mission_letters->execute(offboard, telemetry, ERR_COMP);
    if (ret == false) {
        return EXIT_FAILURE;
    }

    // land after we've completed the mission
    const Action::Result land_result = action->land();
    action_error_exit(land_result, "Landing failed");

    // Check if vehicle is still in air
    while (telemetry->in_air()) {
        std::cout << "Vehicle is landing..." << std::endl;
        sleep_for(seconds(1));
    }
    std::cout << "Landed!" << std::endl;

    // We are relying on auto-disarming but let's keep watching the telemetry for a bit longer.
    sleep_for(seconds(3));
    std::cout << "Finished..." << std::endl;

    return EXIT_SUCCESS;
}
