// tests.cpp
#include <Trajectory.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <gtest/gtest.h>

using namespace mavsdk_skywriting;
using namespace mavsdk;

#define ABS_THRES 0.0001

//using ASSERT_NEAR as small discrepancies in floating-point
//math call for it
 
TEST(ErrorCorrectionTest, Operators) {
	TrajNoPref *tnp = new TrajNoPref({0.0f,1.5f,2.0f,0.0f});
	*tnp += Offboard::PositionNEDYaw({0.23f,0.12f,-0.11f,0.0f}); // the error


    TrajStraight *ts = new TrajNoPref({0.0f,3.0f,1.3f,0.0f});
    ASSERT_NEAR(0.1f, tnp->target_wp.north_m,ABS_THRES);



}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}