#include "AckermannDrive.h"
#include <Arduino.h>

namespace ackermann_msgs {

  AckermannDrive::AckermannDrive() : Msg("ackermann_msgs/AckermannDrive") {
    steering_angle = 0,0;
    steering_angle_velocity = 0,0;
    speed = 0,0;
    acceleration = 0,0;
    jerk = 0,0;
  }

  int AckermannDrive::serialize(JsonObject& json) {
    json["steering_angle"] = steering_angle;
    json["steering_angle_velocity"] = steering_angle_velocity;
    json["speed"] = speed;
    json["acceleration"] = acceleration;
    json["jerk"] = jerk;
  }

  int AckermannDrive:: deserialize(JsonObject& json) {
    JsonVariant msgJson = json["msg"];

    steering_angle = msgJson["steering_angle"];
    steering_angle_velocity = msgJson["steering_angle_velocity"];
    speed = msgJson["speed"];
    acceleration = msgJson["acceleration"];;
    jerk = msgJson["jerk"];
  }
}
