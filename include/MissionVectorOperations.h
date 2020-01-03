// MissionVectorOperations.h

#ifndef MISSION_VECTOR_OPERATIONS_H
#define MISSION_VECTOR_OPERATIONS_H

#include <iostream>
#include <vector>

#include <LetterWaypoint.h>

#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

using namespace std;

namespace mavsdk_skywriting
{

	class MissionVectorOperations
	{
	public:
		static vector<Letter *> stringToMissionVec(std::string str, float _letter_height=3.0f,
	float _letter_spacing=0.25f, float _row_spacing=0.25f, float _scale_factor=3.0f, float _whitespace_width=2.0f);

		static bool execute(std::shared_ptr<mavsdk::Offboard> offboard, std::shared_ptr<mavsdk::Telemetry> telemetry,
    vector<mavsdk_skywriting::Letter *> _letter_waypoints, bool error_comp=false, float _wp_hit_thres=0.3f,
    float _speed=1.0f);

	};


}



#endif //MISSION_VECTOR_OPERATIONS_H