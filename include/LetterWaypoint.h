// LetterWaypoints.h

#ifndef LETTER_WAYPOINTS_H
#define LETTER_WAYPOINTS_H

#include <vector>
#include <map>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/offboard/offboard.h>

#include <Trajectory.h>

using namespace std;
using namespace mavsdk;

namespace mavsdk_skywriting
{

class Letter {
public:
    vector<Trajectory *> trajs; // pointer since abstraction of several different types of Trajs
    float letter_width;
    //constructor 
    Letter(vector<Trajectory *> _trajs,float _letter_width) { trajs = _trajs; letter_width = _letter_width;}
    
    //copy constructor
    Letter(const Letter &l2) { 
    	std::cout << "in hurr" << std::endl;
    for (Trajectory * _traj : l2.trajs)
    	trajs.push_back(_traj->copy());
    letter_width = l2.letter_width; } 

    void print() {
    	cout << "Letter trajs: " << endl;
    	for (Trajectory * traj : trajs) traj->print();
    }
};

class LetterWaypoint
{
	private:
		//variables

		//functions
		bool initializeLookupTable();

	public:
		//constructor/desctructor
		LetterWaypoint();

		//variables
		map<char, Letter *> characterLookupTable;

		//functions

};

} // namespace mavsdk_skywriting

#endif //LETTER_WAYPOINTS_H
