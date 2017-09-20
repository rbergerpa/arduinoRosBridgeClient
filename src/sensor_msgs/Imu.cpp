#include "Imu.h"

namespace sensor_msgs {
  Imu::Imu() : Msg("sensor_msgs/Imu") {
    orientation.x = 0.0;
    orientation.y = 0.0;
    orientation.z = 0.0;
    orientation.w = 0.0;

    angular_velocity.x = 0.0;
    angular_velocity.y = 0.0;
    angular_velocity.z = 0.0;

    linear_acceleration.x = 0.0;
    linear_acceleration.y = 0.0;
    linear_acceleration.z = 0.0;

  }

  int Imu::serialize(JsonObject& json) {
    JsonObject& orientation_Json = json.createNestedObject("orientation");
    orientation_Json["x"] = orientation.x;
    orientation_Json["y"] = orientation.y;
    orientation_Json["z"] = orientation.z;
    orientation_Json["w"] = orientation.w;

    JsonObject& angular_velocity_Json = json.createNestedObject("angular_velocity");
    angular_velocity_Json["x"] = angular_velocity.x;
    angular_velocity_Json["y"] = angular_velocity.y;
    angular_velocity_Json["z"] = angular_velocity.z;

    JsonObject& linear_acceleration_Json = json.createNestedObject("linear_acceleration");
    linear_acceleration_Json["x"] = linear_acceleration.x;
    linear_acceleration_Json["y"] = linear_acceleration.y;
    linear_acceleration_Json["z"] = linear_acceleration.z;
  }

  int Imu:: deserialize(JsonObject& json) {
  }


}
