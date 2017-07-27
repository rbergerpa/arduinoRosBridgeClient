//#define USE_SERIAL
#ifdef USE_SERIAL
#include <ros.h>
#else
#include <rosBridgeClient.h>
#endif
//#include <std_msgs/Int8.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Int64MultiArray.h>

ros::NodeHandle nh;
#include "callbacks.h"

#ifndef USE_SERIAL
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177); // The static IP address to use if the DHCP fails to assign
const char* host = "192.168.2.1";
#endif

//ros::Subscriber<std_msgs::Int8> int8Subscriber("/int8Sub" , &integerCallback<std_msgs::Int8>);

ros::Subscriber<std_msgs::Float32MultiArray> float32MultiSubscriber("/float32MultiSub" , &floatArrayCallback<std_msgs::Float32MultiArray>);
ros::Subscriber<std_msgs::Int8MultiArray> int8MultiSubscriber("/int8MultiSub" , &integerArrayCallback<std_msgs::Int8MultiArray>);
ros::Subscriber<std_msgs::Int16MultiArray> int16MultiSubscriber("/int16MultiSub" , &integerArrayCallback<std_msgs::Int16MultiArray>);
ros::Subscriber<std_msgs::Int32MultiArray> int32MultiSubscriber("/int32MultiSub" , &integerArrayCallback<std_msgs::Int32MultiArray>);
ros::Subscriber<std_msgs::Int64MultiArray> int64MultiSubscriber("/int64MultiSub" , &integerArrayCallback<std_msgs::Int64MultiArray>);

 void setup() {
  Serial.begin(57600);

#ifdef USE_SERIAL
  nh.initNode();
#else
  Serial.println("calling initNode");
  nh.initNode("Arduiono", mac, ip, host);
  Serial.println("after initNode");
#endif

  nh.loginfo("Starting");
//  nh.subscribe(int8Subscriber);
  nh.subscribe(int8MultiSubscriber);
  nh.subscribe(int16MultiSubscriber);
  nh.subscribe(int32MultiSubscriber);
  nh.subscribe(int64MultiSubscriber);
  nh.subscribe(float32MultiSubscriber);

} // setup

void loop() {
  nh.spinOnce();
} // loop

