#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0_MotorControl.h"
#include "ApplicationFunctionSet_xxx0_MotorControl.cpp"
#include "DeviceDriverSet_xxx0_LineTracking.h"

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_SmartRobotCarxxx0;
DeviceDriverSet_ITR20001 AppITR20001;

void setup() {
  // put your setup code here, to run once:
  AppMotor.DeviceDriverSet_Motor_Init();
  Serial.begin(9600);  // Establish a data transfer rate
  AppITR20001.DeviceDriverSet_ITR20001_Init();  // Set the Line Tracking Module to its corresponding pins
}

void loop() {
  // put your main code here, to run repeatedly:
  go("F", 255);

  static unsigned long print_time = 0;
  if (millis() - print_time > 500){
    print_time = millis();

    if (getLeft() > 500){
      go("L", 255);
      delay(500);
    }
    if(getLeft > 200){
      go("LF", 255);
      delay(250);
    }
    if(getRight() > 500){
      go("R", 255);
      delay(500);
    }
    if(getRight() > 200){
      go("RF", 255);
      delay(250);
    }
  }

}

void go(String direction, int speed){
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
  ApplicationFunctionSet_SmartRobotCarMotionControl(Application_SmartRobotCarxxx0.Motion_Control, speed);
}

int getLeft(){
  return AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L();
}
int getMiddle(){
  return AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M();
}
int getRight(){
  return AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R();
}