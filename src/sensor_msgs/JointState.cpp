#include "JointState.h"

namespace sensor_msgs {
  JointState::JointState() : Msg("sensor_msgs/JointState") {
    data_length = 0;
    _includeHeader = true;
  }

  int JointState::serialize(JsonObject& json) {

    JsonArray& jsonName = json.createNestedArray("name");
    JsonArray& jsonPosition = json.createNestedArray("position");
    JsonArray& jsonVelocity = json.createNestedArray("velocity");
    JsonArray& jsoonEffort = json.createNestedArray("effort");

    for (int i = 0; i < data_length; i++) {
      jsonName.add(name[i]);
      jsonPosition.add(position[i]);
      jsonVelocity.add(velocity[i]);
      jsoonEffort.add(effort[i]);
    }
  }

  int JointState:: deserialize(JsonObject& json) {
  }
}
