// MissionVectorOperations.h

#ifndef MISSION_VECTOR_H
#define MISSION_VECTOR_H

#include <iostream>
#include <vector>

#include <LetterWaypoint.h>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

using namespace std;

namespace mavsdk_skywriting
{

	class MissionVector
	{
	
	float mission_width = 0.0f;
	vector<mavsdk_skywriting::Letter *> letter_waypoints;

	public:

		MissionVector(std::string str, float _letter_height=3.0f,
	float _letter_spacing=0.25f, float _row_spacing=0.25f, float _scale_factor=3.0f, float _whitespace_width=2.0f);

		float getMissionLength();

		bool execute(mavsdk::Offboard &offboard, mavsdk::Telemetry &telemetry,
						 bool error_comp=false, float _wp_hit_thres=0.3f,
    					float _speed=1.0f);

	};


}



#endif //MISSION_VECTOR_H
