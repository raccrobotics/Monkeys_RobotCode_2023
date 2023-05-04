#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0_MotorControl.h"
#include "ApplicationFunctionSet_xxx0_MotorControl.cpp"
#include "DeviceDriverSet_xxx0_LineTracking.h"

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_SmartRobotCarxxx0;
DeviceDriverSet_ITR20001 AppITR20001;
int SPEED = 90, ON = 500; //constants for speed and value that determines whether or not the robot is on the line
bool isBoost = true; //used for boost to prevent driving off of the line

void setup() {
  // put your setup code here, to run once:
  AppMotor.DeviceDriverSet_Motor_Init();
  Serial.begin(9600);  // Establish a data transfer rate
  AppITR20001.DeviceDriverSet_ITR20001_Init();  // Set the Line Tracking Module to its corresponding pins
}

void loop() {
  // put your main code here, to run repeatedly:
  if (getMiddle() > ON){ //if the robot is on the line
    if (isBoost && getLeft() < 100 && getRight < 100){ //goes max speed if the robot is traveling straight
      go("F", 255);
      delay(50);
      isBoost = false;
    }
    go("F", SPEED + 60); //resumes "normal" speed
  }
  else if (getRight() > ON){
    while (getRight() > ON){ //turns right until robot is back on the line
      go("R", SPEED);
    }
    isBoost = true;
  }
  else if (getLeft() > ON){
    while(getLeft() > ON){ //turns left until robot is back on the line
      go("L", SPEED);
    }
    isBoost = true;
  }
}

void go(String direction, int speed){ //turning these functions into english because it makes my life easier
  //this extensive chain of if statements assigns the direction based on the string that is passed
  if (direction.equalsIgnoreCase("F")){
    Application_SmartRobotCarxxx0.Motion_Control = 0;
  }
  else if (direction.equalsIgnoreCase("B")){
    Application_SmartRobotCarxxx0.Motion_Control = 1;
  }
  else if (direction.equalsIgnoreCase("L")){
    Application_SmartRobotCarxxx0.Motion_Control = 2;
  }
  else if (direction.equalsIgnoreCase("R")){
    Application_SmartRobotCarxxx0.Motion_Control = 3;
  }
  else if (direction.equalsIgnoreCase("LF")){
    Application_SmartRobotCarxxx0.Motion_Control = 4;
  }
  else if (direction.equalsIgnoreCase("LB")){
    Application_SmartRobotCarxxx0.Motion_Control = 5;
  }
  else if (direction.equalsIgnoreCase("RF")){
     Application_SmartRobotCarxxx0.Motion_Control = 6;
  }
  else if (direction.equalsIgnoreCase("RB")){
    Application_SmartRobotCarxxx0.Motion_Control = 7;
  }
  else{
    Application_SmartRobotCarxxx0.Motion_Control = 8;
  }
  ApplicationFunctionSet_SmartRobotCarMotionControl(Application_SmartRobotCarxxx0.Motion_Control, speed); //makes the robot go in the assigned direction at the assigned speed
}

//returns the values from the left, middle, and right functions, respectively
int getLeft(){
  return AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L();
}
int getMiddle(){
  return AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M();
}
int getRight(){
  return AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R();
}
