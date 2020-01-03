// LetterWaypoints.cpp - written by Gordon Keller

#include <LetterWaypoint.h>
#include <Trajectory.h>
#include <MissionVectorOperations.h>

#include <iostream>

using namespace std;

namespace mavsdk_skywriting
{

LetterWaypoints::LetterWaypoints()
{
	//initialize the lookup table
	LetterWaypoints::initializeLookupTable();

	// if success {

	// } else {

	// }
}

bool LetterWaypoints::initializeLookupTable()
{
	cout << "Initializing lookup table..." << endl;

	//initialize our lookup table
    // TrajNoPref *t1 = new TrajNoPref({0.0f,0.0f,3.0f,0.0f});
    // TrajStraight *t2 = new TrajStraight({0.0f,1.5f,0.0f,0.0f});
    // TrajStraight *t3 = new TrajStraight({0.0f,3.0f,3.0f,0.0f});
    // TrajNoPref *t4 = new TrajNoPref({0.0f,0.75f,1.5f,0.0f});
    // TrajStraight *t5 = new TrajStraight({0.0f,2.25f,1.5f,0.0f});
    characterLookupTable['A'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,1.5f,0.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,3.0f,0.0f}),
        new TrajNoPref({0.0f,0.75f,1.5f,0.0f}),
        new TrajStraight({0.0f,2.25f,1.5f,0.0f})},
         3.0f);

    characterLookupTable['B'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajCurved({0.0f,0.0f,1.0f,0.0f},
                        {0.0f,0.0f,0.5f,0.0f},
                        TrajCurved::CLOCKWISE),
        new TrajCurved({0.0f,0.0f,3.0f,0.0f},
                        {0.0f,0.0f,2.0f,0.0f},
                        TrajCurved::CLOCKWISE),
        },
         2.0f);

    characterLookupTable['C'] = new Letter(
        {new TrajNoPref({0.0f,2.561f,0.439f,0.0f}),
        new TrajCurved({0.0f,2.561f,2.561f,0.0f},
                        {0.0f,1.5f,1.5f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE)},
         3.0f);

    characterLookupTable['D'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajCurved({0.0f,0.0f,3.0f,0.0f},
                        {0.0f,0.0f,1.5f,0.0f},
                        TrajCurved::CLOCKWISE)},
        2.0f);

    characterLookupTable['E'] = new Letter(
        {new TrajNoPref({0.0f,2.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,3.0f,0.0f}),
        new TrajNoPref({0.0f,0.0f,1.5f,0.0f}),
        new TrajStraight({0.0f,1.0f,1.5f,0.0f})},
        2.0f);

    characterLookupTable['F'] = new Letter(
        {new TrajNoPref({0.0f,2.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,3.0f,0.0f}),
        new TrajNoPref({0.0f,0.0f,1.5f,0.0f}),
        new TrajStraight({0.0f,1.0f,1.5f,0.0f})},
        2.0f);

    characterLookupTable['G'] = new Letter(
        {new TrajNoPref({0.0f,2.561f,0.439f,0.0f}),
        new TrajCurved({0.0f,2.561f,2.561f,0.0f},
                        {0.0f,1.5f,1.5f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajNoPref({0.0f,1.5f,2.0f,0.0f}),
        new TrajStraight({0.0f,2.561f,2.0f,0.0f}),
        new TrajStraight({0.0f,2.561f,3.0f,0.0f})},
        3.0f);

    characterLookupTable['H'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajNoPref({0.0f,0.0f,1.5f,0.0f}),
        new TrajStraight({0.0f,2.0f,1.5f,0.0f}),
        new TrajNoPref({0.0f,2.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,3.0f,0.0f})},
        2.0f);

    characterLookupTable['I'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,0.0f,0.0f}),
        new TrajNoPref({0.0f,1.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,1.0f,3.0f,0.0f}),
        new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,3.0f,0.0f})},
        2.0f);

    characterLookupTable['J'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,2.0f,0.0f}),
        new TrajCurved({0.0f,1.5f,2.0f,0.0f},
                        {0.0f,0.75f,2.0f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajStraight({0.0f,1.5f,0.0f,0.0f}),
        new TrajNoPref({0.0f,0.5f,0.0f,0.0f}),
        new TrajStraight({0.0f,2.5f,0.0f,0.0f})},
        2.5f);

    characterLookupTable['K'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajNoPref({0.0f,1.5f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,1.5f,0.0f}),
        new TrajStraight({0.0f,1.5f,3.0f,0.0f})},
        1.5f);

    characterLookupTable['L'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,3.0f,0.0f})},
        2.0f);

    characterLookupTable['M'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,1.5f,1.5f,0.0f}),
        new TrajStraight({0.0f,3.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,3.0f,0.0f})},
        3.0f);

    characterLookupTable['N'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,2.0f,0.0f,0.0f})},
        2.0f);

    characterLookupTable['O'] = new Letter(
        {new TrajNoPref({0.0f,1.5f,0.0f,0.0f}),
        new TrajCurved({0.0f,1.5f,3.0f,0.0f},
                        {0.0f,1.5f,1.5f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajCurved({0.0f,1.5f,0.0f,0.0f},
                        {0.0f,1.5f,1.5f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE)},
        3.0f);

    characterLookupTable['P'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajCurved({0.0f,0.0f,1.5f,0.0f},
                        {0.0f,0.0f,0.75f,0.0f},
                        TrajCurved::CLOCKWISE)},
        2.0f);

    characterLookupTable['Q'] = new Letter(
        {new TrajNoPref({0.0f,1.5f,0.0f,0.0f}),
        new TrajCurved({0.0f,1.5f,3.0f,0.0f},
                        {0.0f,1.5f,1.5f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajCurved({0.0f,1.5f,0.0f,0.0f},
                        {0.0f,1.5f,1.5f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajNoPref({0.0f,2.0f,2.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,3.0f,0.0f})},
        3.0f);

    characterLookupTable['R'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,0.0f,0.0f}),
        new TrajCurved({0.0f,0.0f,1.5f,0.0f},
                        {0.0f,0.0f,0.75f,0.0f},
                        TrajCurved::CLOCKWISE),
        new TrajStraight({0.0f,1.5f,3.0f,0.0f})},
        1.5f);

    characterLookupTable['S'] = new Letter(
        {new TrajNoPref({0.0f,0.75f,2.25f,0.0f}),
        new TrajCurved({0.0f,1.5f,1.5f,0.0f},
                        {0.0f,1.5f,2.25f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajCurved({0.0f,2.25f,0.75f,0.0f},
                        {0.0f,1.5f,0.75f,0.0f},
                        TrajCurved::CLOCKWISE)},
        3.0f);

    characterLookupTable['T'] = new Letter(
        {new TrajNoPref({0.0f,1.5f,3.0f,0.0f}),
        new TrajStraight({0.0f,1.5f,0.0f,0.0f}),
        new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,0.0f,0.0f})},
        3.0f);

    characterLookupTable['U'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,2.0f,0.0f}),
        new TrajCurved({0.0f,2.0f,2.0f,0.0f},
                        {0.0f,1.0f,2.0f,0.0f},
                        TrajCurved::COUNTER_CLOCKWISE),
        new TrajStraight({0.0f,2.0f,0.0f,0.0f})},
        2.0f);

    characterLookupTable['V'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,1.5f,3.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,0.0f,0.0f})},
        3.0f);

    characterLookupTable['W'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,1.5f,1.5f,0.0f}),
        new TrajStraight({0.0f,3.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,0.0f,0.0f})},
        3.0f);

    characterLookupTable['X'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,0.0f,0.0f}),
        new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,3.0f,0.0f})},
        3.0f);

    characterLookupTable['Y'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,1.0f,1.5f,0.0f}),
        new TrajStraight({0.0f,1.0f,3.0f,0.0f}),
        new TrajNoPref({0.0f,1.0f,1.5f,0.0f}),
        new TrajStraight({0.0f,2.0f,0.0f,0.0f})},
        2.0f);

    characterLookupTable['Z'] = new Letter(
        {new TrajNoPref({0.0f,0.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,0.0f,0.0f}),
        new TrajStraight({0.0f,0.0f,3.0f,0.0f}),
        new TrajStraight({0.0f,3.0f,3.0f,0.0f})},
        3.0f);

    cout << "Finished initializing lookup table." << endl;
    return true;
}

}
