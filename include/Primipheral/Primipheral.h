// Primipheral.h

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


#ifndef PRIMIPHERAL_H
#define PRIMIPHERAL_H

#include <vector>
#include <map>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/offboard/offboard.h>

using namespace std;
using namespace mavsdk;

namespace mavsdk_skywriting
{

class Primipheral
{
	private:
		//variables

		//functions
		bool func();

	public:
		//constructor/desctructor
		Primipheral();

		//variables

		//functions

};

} // namespace mavsdk_skywriting

#endif //PRIMIPHERAL_H
