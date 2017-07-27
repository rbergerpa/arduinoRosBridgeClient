//#define USE_SERIAL
#ifdef USE_SERIAL
#include <ros.h>
#else
#include <rosBridgeClient.h>
#endif
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int8.h>
#include <ackermann_msgs/AckermannDrive.h>
ros::NodeHandle nh;

std_msgs::Float32MultiArray float32MulitArrayMsg;
ros::Publisher float32MultiArrayPub("/float32MulitArray", &float32MulitArrayMsg); 

std_msgs::Int16MultiArray int16MulitArrayMsg;
ros::Publisher int16MultiArrayPub("/int16MulitArray", &int16MulitArrayMsg); 

std_msgs::Int8 int8Msg;
ros::Publisher int8Pub("/int8", &int8Msg); 

ackermann_msgs::AckermannDrive ackermannMsg;
ros::Publisher ackermannPub("/ackermann", &ackermannMsg);

#ifndef USE_SERIAL
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 177); // The static IP address to use if the DHCP fails to assign
const char* host = "192.168.2.1";
#endif

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
  nh.advertise(float32MultiArrayPub);
  nh.advertise(int16MultiArrayPub);
  nh.advertise(int8Pub);
  nh.advertise(ackermannPub);
} // setup

void loop() {
  float float32MultiArrayData[] = {1.5, 2.5, 3.5};
  int16_t int16MultiArrayData[] = {1, 2, 3, 4};

  float32MulitArrayMsg.data = float32MultiArrayData;
  float32MulitArrayMsg.data_length = sizeof(float32MultiArrayData) / sizeof(float);
  float32MultiArrayPub.publish(&float32MulitArrayMsg);

  int16MulitArrayMsg.data = int16MultiArrayData;
  int16MulitArrayMsg.data_length = sizeof(int16MultiArrayData) / sizeof(int16_t);
  int16MultiArrayPub.publish(&int16MulitArrayMsg);

  int8Msg.data = 42;
  int8Pub.publish(&int8Msg);

  ackermannMsg.steering_angle = 1.2;
  ackermannMsg.steering_angle_velocity = 2.2;
  ackermannMsg.speed = 3.2;
  ackermannMsg.acceleration = 4.2;
  ackermannMsg.jerk = 5.2;
  ackermannPub.publish(&ackermannMsg);

  nh.spinOnce();
  delay(100);
} // loop

