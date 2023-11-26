// VectorOperations.cpp

#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <future>
#include <memory>

#include <LetterWaypoint.h>
#include <Trajectory.h>
#include <MissionVectorOperations.h>
#include <Common.h>
#include <Safeguard.h>

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/geofence/geofence.h>

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

using namespace std;
using namespace mavsdk;

static Geofence::Polygon::Point add_point(double latitude_deg, double longitude_deg);

namespace mavsdk_skywriting {

// //static function for computing the x,y,z coverage of trajectories (in NED)
// static float* Safeguard::calculateSize(Offboard::PositionNEDYaw *letters) {
//     //find the extremes of the set of waypoints

//     //compute x

//     //compute y

//     //compute z


// }


Geofence::Polygon::Point add_point(double latitude_deg, double longitude_deg)
{
    Geofence::Polygon::Point new_point;
    new_point.latitude_deg = latitude_deg;
    new_point.longitude_deg = longitude_deg;
    return new_point;
}

//creates a vector of setpoints based on an input string
static void Safeguard::setGeofence(Offboard::PositionNEDYaw origin, float text_length,
                                float x_buf, float y_buf, std::shared_ptr<mavsdk::Geofence> geofence)
{
    auto prom = std::make_shared<std::promise<void>>();
    auto future_result = prom->get_future();


    Offboard::PositionNEDYaw pt1, pt2, pt3, pt4; 

    pt1 = origin + {x_buf,-y_buf,0.0f,0.0f};
    pt2 = origin + {x_buf,text_length+y_buf,0.0f,0.0f};
    pt3 = origin + {-x_buf,text_length+y_buf,0.0f,0.0f};
    pt4 = origin + {x_buf,-y_buf,0.0f,0.0f};

    std::vector<Geofence::Polygon::Point> points;
    points.push_back(add_point(47.39929240, 8.54296524));
    points.push_back(add_point(47.39696482, 8.54161340));
    points.push_back(add_point(47.39626761, 8.54527193));
    points.push_back(add_point(47.39980072, 8.54736050));

    std::vector<std::shared_ptr<Geofence::Polygon>> polygons;
    std::shared_ptr<Geofence::Polygon> new_polygon(new Geofence::Polygon());
    new_polygon->type = Geofence::Polygon::Type::INCLUSION;
    new_polygon->points = points;

    polygons.push_back(new_polygon);

    {
        std::cout << "Uploading geofence..." << std::endl;

        auto prom = std::make_shared<std::promise<Geofence::Result>>();
        auto future_result = prom->get_future();
        geofence->send_geofence_async(
            polygons, [prom](Geofence::Result result) { prom->set_value(result); });

        const Geofence::Result result = future_result.get();
        if (result != Geofence::Result::SUCCESS) {
            std::cout << "Geofence upload failed (" << Geofence::result_str(result) << "), exiting."
                      << std::endl;
            return 1;
        }
        std::cout << "Geofence uploaded." << std::endl;
    }
}

}

Geofence::Polygon::Point add_point(double latitude_deg, double longitude_deg)
{
    Geofence::Polygon::Point new_point;
    new_point.latitude_deg = latitude_deg;
    new_point.longitude_deg = longitude_deg;
    return new_point;
}
