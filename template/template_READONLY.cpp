#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
rotation Rotation2 = rotation(PORT2, false);

digital_out DigitalOutA = digital_out(Brain.ThreeWirePort.A);


// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*
todo list
1. 
2. 
3. 
*/
 

// Include Libarys
#include "vex.h"
#include "algorithm"
#include "utility"
  
// Allows for easier use of the VEX Library
using namespace vex;
competition Competition = competition();                                 


// keyword Declreation 
#define Spin 0
#define Stop 1
#define SetSpeed 2
#define SpinFor 3
#define SetBraking 4
#define SetTimeout 5
#define SpinTo 6

#define Brake 0
#define Coast 1
#define Hold 2

#define Left 0
#define Right 1
#define Both 2

#define Match 0
#define Skills 1

// Function and variable teasers
  void autonHelper();

  void driveMacro(int action, float argument1 = 100000, float argument2 = 100000);
  void turnToDegree(int destination, int pivotSetting = Both, float timeout = 100000);
  void moveForTurns(float destination, int timeout = 100000);

  void driver_Control();
  void auton_one();
  void auton_two();
  void auton_skills();
  void auton_init();

// Ports decleration
  // drivetrain 
  //TODO[1] --> edit the ports, gear ratio, and rotation of your drivetrain motors
  controller Controller1 = controller(primary);
  motor drive_leftFront = motor(PORT14, ratio18_1, true);
  motor drive_leftMid = motor(PORT15, ratio18_1, false);
  motor drive_leftBack = motor(PORT16, ratio18_1, true);
  motor drive_rightFront = motor(PORT11, ratio18_1, false);
  motor drive_rightMid = motor(PORT12, ratio18_1, true);
  motor drive_rightBack = motor(PORT13, ratio18_1, false);
  inertial drive_gyro = inertial(PORT19); // TODO[2] --> edit the port of your gyro sensor

  //Periphrals
  //TODO[3] --> define the other stuff your using eg.
  // motor intake_motor = motor(PORT1, ratio18_1, false); // for a motor
  // rotation Rotation2 = rotation(PORT2, false); // for a v5 rotation sensor
  // digital_out hang_piston = digital_out(Brain.ThreeWirePort.A); // for a solonoid at port A
  // digital_in intake_limitSwitch = digital_out(Brain.ThreeWirePort.b); // for a limit switch at port B
  // see https://api.vex.com/v5/home/cpp/

  //variables
  int mode = Match; // TODO[4] --> choose whether you are running a 'Match' or a 'Skills' run before uploading

  //TODO[5] --> these are the pid variables for turnToDegree() and moveForTurns(). you have to tune them like you tune
  //a line tracking bot. the values below were from 8068e worlds bot
  float turnP = 0.57;
  float turnConst = 2;
  float turnD = 0;
  float moveP = 80;
  float moveConst = 17;

  
void pre_auton(void){
  auton_init();
}

int main() {
  //TODO[6] --> uncomment the code that you want to run before uploading
  //--COMPETITION TEMPLATE--//
  //Competition.drivercontrol(driver_Control);

  //For auton_one:
  //Competition.autonomous(auton_one);

  // For auton_two
  //Competition.autonomous(auton_two);

  //For Auton Skills:
  //Competition.autonomous(auton_skills);

  pre_auton();
  //--COMPETITION TEMPLATE--//



  //--TESTING--//
  //driver_Control();
  //auton_one();
  //auton_two();
  //auton_skills();
  //autonHelper();
}







// fuunctions
void driver_Control() {
  driveMacro(SetBraking, Coast); // TODO[7] --> choose Brake, Coast or Hold for your drive train during driver control
  int fwd, sideways, leftTrain, rightTrain;

  //initalises controller vibration
  int timeLast = Brain.Timer.time(seconds);
  int matchLength = 105; 
  if (mode == Skills) {
    matchLength = 60;
  }
  int last_rumble = matchLength;

  while (true) {
    // drivetrain control
    fwd = Controller1.Axis3.position();
    sideways = Controller1.Axis1.position();
    leftTrain = fwd + sideways;
    rightTrain = fwd - sideways;
    driveMacro(SetSpeed, leftTrain, rightTrain);
    driveMacro(Spin);

    //TODO[8] --> code stuff other than the drivetrain for your driver control mode
    //github has the over under code for you to refer to
    




    //rumble for timer --> will vibrate the controller in the last 30, 15 and 10 seconds of the match
    // if you dont want, you can delete or edit the rumble timings
    if (Brain.Timer.time(seconds) - timeLast > matchLength - 30 && last_rumble > 30) {
      Controller1.rumble("-");
      last_rumble = 30;
    } else if (Brain.Timer.time(seconds) - timeLast > matchLength - 15 && last_rumble > 16) {
      Controller1.rumble("--");
      last_rumble = 15;
    } else if (Brain.Timer.time(seconds) - timeLast > matchLength - 10 && last_rumble > 11) {
      Controller1.rumble("---");
      last_rumble = 10;
    }
    wait(0.005, seconds);
  }
}


//autons
void auton_one() {
  //TODO[9] --> your auton_one code


  driveMacro(Stop);
  Brain.Screen.print("code ended ");
}

void auton_two() {
  //TODO[9] --> your auton_two code


  driveMacro(Stop);
  Brain.Screen.print("code ended ");
}

void auton_skills(){
  //TODO[9] --> your skills code

  driveMacro(Stop);
  Brain.Screen.print("code ended ");
}

void auton_init(){
  //TODO[10] --> do wtv you want to set up before each auton
  //this function is called the moment the brain powers up, even before the match starts, in the pre_auton() funciton
  //below is some suggestions
  drive_gyro.calibrate();
  driveMacro(SetBraking, Hold); //recomendded to set to hold during auton
  driveMacro(SetTimeout, 30);
  driveMacro(SetSpeed, 100, 100);
  Brain.Screen.print("ready to run ");
  Brain.Screen.newLine();
}





















//helping functions, see documentation
void autonHelper() {
  driveMacro(SetBraking, Coast);
  float pastLeft = 0;
  float pastRight = 0;
  while (1) {
    if (Controller1.ButtonRight.pressing()) {
      Controller1.Screen.print("gyro: ");
      Controller1.Screen.print(drive_gyro.heading(degrees));
      Controller1.Screen.print("               ");
    } 
    else {
    Controller1.Screen.print("L: ");
    Controller1.Screen.print(drive_leftFront.position(turns) - pastLeft);
    Controller1.Screen.print(" R: ");
    Controller1.Screen.print(drive_rightFront.position(turns) - pastRight);
    Controller1.Screen.print("               ");
    }
    Controller1.Screen.newLine();
    wait(0.3,seconds);

    if (Controller1.ButtonUp.pressing()) {
      pastRight = drive_rightFront.position(turns);
      pastLeft = drive_leftFront.position(turns);
    }
  }
}

void turnToDegree(int destination, int pivotSetting, float timeout) {
  driveMacro(SetSpeed, 0, 0);
  float error, seam, noseam, currentHeading, leftTurn, rightTurn, timeMax, pastError;
  int dir;
  leftTurn = 1;
  rightTurn = 1;
  timeMax = Brain.Timer.time(seconds) + timeout;
  pastError = 0;
  if (pivotSetting != Both) {
    if (pivotSetting == Left) {
      leftTurn = 2.5;
      rightTurn = 0;
    } 
    else if (pivotSetting == Right) {
      leftTurn = 0;
      rightTurn = 2.5;
    }
  }
  do {
    currentHeading = drive_gyro.heading(degrees);
    noseam = (::fabs(destination - currentHeading)) * -1;
    seam = 360 - std::max((float) destination, currentHeading) + std::min( (float) destination, currentHeading);
    dir = (currentHeading - destination) / (::fabs(currentHeading - destination));
    if (seam < ::fabs(noseam)) {
      error = seam * dir;
    }
    else {
      error = noseam * dir;
    }
    dir = error / ::fabs(error);

    driveMacro(SetSpeed, ((error * turnP) + (turnConst + ((error - pastError) * turnD)) * dir ) * leftTurn, ((error * turnP) + (turnConst + ((error - pastError) * turnD)) * dir ) * -1 * rightTurn);
    driveMacro(Spin);
    printf("current: %f, error: %f\n", currentHeading, error);
    pastError = error;
  } while (::fabs(error) > 1 && Brain.Timer.time(seconds) < timeMax);
  Brain.Screen.print("finsih ");
  Brain.Screen.print(currentHeading);
  Brain.Screen.newLine();
  driveMacro(SetSpeed, 100, 100);
}

void moveForTurns(float destination, int timeout) {
  driveMacro(SetBraking, Coast);
  int timeMax = Brain.Timer.time(seconds) + timeout;
  float endGoal = drive_leftFront.position(turns) + destination;
  float error = 0;
  int dir;
  do {
    error = endGoal - drive_leftFront.position(turns);
    dir = error / ::fabs(error);
    driveMacro(SetSpeed, (error * moveP) + (moveConst * dir), (error * moveP) + (moveConst * dir));
    driveMacro(Spin);
  } while (::fabs(error) > 0.1 && Brain.Timer.time(seconds) < timeMax);
  driveMacro(SetBraking, Hold);
  driveMacro(SetSpeed, 100, 100);
}

void driveMacro(int action, float argument1, float argument2) {  
  if (action == Spin) {
    drive_leftFront.spin(forward);
    drive_leftMid.spin(forward);
    drive_leftBack.spin(forward);
    drive_rightFront.spin(forward);
    drive_rightMid.spin(forward);
    drive_rightBack.spin(forward);
  } 
  else if (action == Stop){
    drive_leftFront.stop();
    drive_leftMid.stop();
    drive_leftBack.stop();
    drive_rightFront.stop();
    drive_rightMid.stop();
    drive_rightBack.stop();
  }
  else if (action == SetSpeed) {
    drive_leftFront.setVelocity(argument1, percent);
    drive_leftMid.setVelocity(argument1, percent);
    drive_leftBack.setVelocity(argument1, percent);
    drive_rightFront.setVelocity(argument2, percent);
    drive_rightMid.setVelocity(argument2, percent);
    drive_rightBack.setVelocity(argument2, percent);
  }
  else if (action == SpinFor) {
    drive_leftFront.spinFor(forward, argument1, turns, false);
    drive_leftMid.spinFor(forward, argument1, turns, false);
    drive_leftBack.spinFor(forward, argument1, turns, false);
    drive_rightFront.spinFor(forward, argument2, turns, false);
    drive_rightMid.spinFor(forward, argument2, turns, false);
    drive_rightBack.spinFor(forward, argument2, turns, true);
    driveMacro(Stop);
  } 
  else if (action == SetBraking) {
    if (argument1 == Brake) {
    drive_leftFront.setStopping(brake);
    drive_leftMid.setStopping(brake);
    drive_leftBack.setStopping(brake);
    drive_rightFront.setStopping(brake);
    drive_rightMid.setStopping(brake);
    drive_rightBack.setStopping(brake);
    }
    else if (argument1 == Coast) {
    drive_leftFront.setStopping(coast);
    drive_leftMid.setStopping(coast);
    drive_leftBack.setStopping(coast);
    drive_rightFront.setStopping(coast);
    drive_rightMid.setStopping(coast);
    drive_rightBack.setStopping(coast);
    }
    else if (argument1 == Hold) {
    drive_leftFront.setStopping(hold);
    drive_leftMid.setStopping(hold);
    drive_leftBack.setStopping(hold);
    drive_rightFront.setStopping(hold);
    drive_rightMid.setStopping(hold);
    drive_rightBack.setStopping(hold);
    }
  }
  else if (action == SetTimeout) {
    drive_leftFront.setTimeout(argument1, seconds);
    drive_leftMid.setTimeout(argument1, seconds);
    drive_leftBack.setTimeout(argument1, seconds);
    drive_rightFront.setTimeout(argument1, seconds);
    drive_rightMid.setTimeout(argument1, seconds);
    drive_rightBack.setTimeout(argument1, seconds);
  }
  else if (action == SpinTo) {
    drive_leftFront.spinToPosition(argument1, turns);
    drive_leftMid.spinToPosition(argument1, turns);
    drive_leftBack.spinToPosition(argument1, turns);
    drive_rightFront.spinToPosition(argument2, turns);
    drive_rightMid.spinToPosition(argument2, turns);
    drive_rightBack.spinToPosition(argument2, turns);
  }
}

