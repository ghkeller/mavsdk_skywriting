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
 
TEST(TrajNoPrefTest, Operators) {
	TrajNoPref *tnp = new TrajNoPref({0.0f,0.0f,0.0f,0.0f});
	*tnp += Offboard::PositionNEDYaw({0.1f,0.2f,0.3f,0.4f});
    ASSERT_NEAR(0.1f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(0.2f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(0.3f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
    *tnp += Offboard::PositionNEDYaw({-0.2f,0.5f,1.3f,0.0f});
    ASSERT_NEAR(-0.1f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(0.7f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(1.6f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
    *tnp += Telemetry::PositionNED({2.3f,-0.9f,100.1f});
    ASSERT_NEAR(2.2f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(-0.2f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(101.7f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
    *tnp *= 0.5f;
    ASSERT_NEAR(1.1f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(-0.1f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(50.85f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
}

TEST(TrajStraightTest, Operators) {
	TrajStraight *tnp = new TrajStraight({0.0f,0.0f,0.0f,0.0f});
	*tnp += Offboard::PositionNEDYaw({0.1f,0.2f,0.3f,0.4f});
    ASSERT_NEAR(0.1f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(0.2f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(0.3f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
    *tnp += Offboard::PositionNEDYaw({-0.2f,0.5f,1.3f,0.0f});
    ASSERT_NEAR(-0.1f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(0.7f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(1.6f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
    *tnp += Telemetry::PositionNED({2.3f,-0.9f,100.1f});
    ASSERT_NEAR(2.2f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(-0.2f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(101.7f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
    *tnp *= 0.5f;
    ASSERT_NEAR(1.1f, tnp->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(-0.1f, tnp->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(50.85f, tnp->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, tnp->target_wp.yaw_deg,ABS_THRES);
}

TEST(TrajCurvedTest, Operators) {
	TrajCurved *traj = new TrajCurved({0.0f,0.0f,0.0f,0.0f},
										{-1.0f,20.3f,14.9f,0.0f},
										TrajCurved::COUNTER_CLOCKWISE);
	*traj += Offboard::PositionNEDYaw({0.1f,0.2f,0.3f,0.4f});
    ASSERT_NEAR(0.1f, traj->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(0.2f, traj->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(0.3f, traj->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->target_wp.yaw_deg,ABS_THRES);
    ASSERT_NEAR(-0.9f, traj->center_wp.north_m,ABS_THRES);
    ASSERT_NEAR(20.5f, traj->center_wp.east_m,ABS_THRES);
    ASSERT_NEAR(15.2f, traj->center_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->center_wp.yaw_deg,ABS_THRES);
    *traj += Offboard::PositionNEDYaw({-0.2f,0.5f,1.3f,0.0f});
    ASSERT_NEAR(-0.1f, traj->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(0.7f, traj->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(1.6f, traj->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->target_wp.yaw_deg,ABS_THRES);
    ASSERT_NEAR(-1.1f, traj->center_wp.north_m,ABS_THRES);
    ASSERT_NEAR(21.0f, traj->center_wp.east_m,ABS_THRES);
    ASSERT_NEAR(16.5f, traj->center_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->center_wp.yaw_deg,ABS_THRES);
    *traj += Telemetry::PositionNED({2.3f,-0.9f,100.1f});
    ASSERT_NEAR(2.2f, traj->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(-0.2f, traj->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(101.7f, traj->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->target_wp.yaw_deg,ABS_THRES);
    ASSERT_NEAR(1.2f, traj->center_wp.north_m,ABS_THRES);
    ASSERT_NEAR(20.1f, traj->center_wp.east_m,ABS_THRES);
    ASSERT_NEAR(116.6f, traj->center_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->center_wp.yaw_deg,ABS_THRES);
    *traj *= 0.5f;
    ASSERT_NEAR(1.1f, traj->target_wp.north_m,ABS_THRES);
    ASSERT_NEAR(-0.1f, traj->target_wp.east_m,ABS_THRES);
    ASSERT_NEAR(50.85f, traj->target_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->target_wp.yaw_deg,ABS_THRES);
    ASSERT_NEAR(0.6f, traj->center_wp.north_m,ABS_THRES);
    ASSERT_NEAR(10.05f, traj->center_wp.east_m,ABS_THRES);
    ASSERT_NEAR(58.3f, traj->center_wp.down_m,ABS_THRES);
    ASSERT_NEAR(0.4f, traj->center_wp.yaw_deg,ABS_THRES);
}
 

 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}