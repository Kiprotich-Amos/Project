#include "lineFollowing.h"
#include "objectsOperation.h"

//DECLARING THE START PUSH BUTTON PIN
const int startButton = 30;

void setup() {
  Serial.begin(9600);//setting the serial communication speed for screen displays
  //ASSIGNING THE ANALOG REFERENCE TO REFERENCE EXTERNAL SOURCE
  analogReference(EXTERNAL);

  pinMode (startButton, INPUT);
  bool startButtonState = LOW;//To store the state of the start push button
  do { //wait for the push button to start
    startButtonState = digitalRead(startButton);
  } while (startButtonState == LOW);

  lineFollowingSetup();
  objectsOperationSetup();
}

void loop() {
  delay(500);
  //WAIT FOR THE PUSH BUTTON TO BE PRESSED TO START
  bool startButtonState = LOW;//To store the state of the start push button
  do { //wait for the push button to start loop
    startButtonState = digitalRead(startButton);
  } while (startButtonState == LOW);

  //START FROM THE START ZONE
  //startZoneStart();
  normalSpeed = 1.125 * masterSpeed;
  followLineCheckRightTurn();//FOLLOW LINE CHECKING FOR A RIGHT TURN TO THE TURNEL
  forwardBreak();
  rightTurn90();//TURN RIGHT TO ENTER THE TURNEL
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckTJunction();//FOLLOW LINE TO PASS THE TURN CHECKING FOR A T-JUNCTION AHEAD
  
  leftTurn90T_Junction();//TURN LEFT AT THE T-JUNCTION
  
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckTJunction();//FOLLOW LINE UP TO THE + JUNCTION (DETECTED AS A T-JUNCTION)
  leftTurnPlus_Junction();//TURN LEFT AT THE +-JUNCTION
  normalSpeed = 0.5 * masterSpeed; //REDUCE SPEED TO FOLLOW LINE CHECKING FOR M1
  followLineCheckObstacle(1, 12);//FOLLOW LINE CHECKING FOR M1
  delay(10);
  getM1();
  delay(10);
  
  placeM1toCarrier();
  delay(10);
  normalSpeed = 0.7 * masterSpeed;
  reverseCheckTJuction();
  turnRight90_AfterReverse();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(1, 12);
  delay(10);
  getM2();
  delay(10);
  setObjectSensor(HIGH);
  yield();
  
  
  normalSpeed = 0.7 * masterSpeed;
  reverseCheckTJuction();
  turnRight90_AfterReverse();
  normalSpeed = masterSpeed;
  followLineCheckRightTurn();
  followLineCheckTJunction();
  passT_Junction();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckTJunction();
  forwardBreak();
  normalSpeed = 0.9 * masterSpeed;
  positionM2();
  delay(10);
  placeM2();
  delay(10);
  normalSpeed = 0.7 * masterSpeed;
  reverseTurnLeftToTrack();
  normalSpeed = 0.8 * masterSpeed;
  followLineCheckTJunction();
  rightTurnPlus_Junction();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckTJunction();
  forwardBreak();
  rightTurnT_Junction();
  forwardBreak();
  setObjectSensor(LOW);
  yield();
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckObstacle(1, 12);
  delay(10);
  getM1fromCarrier();
  delay(10);
  placeM1();
  delay(10);
  
  setObjectSensor(HIGH);
  yield();
  reverseTurnRightT_Juction();
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckTJunction();
  passT_Junction();
     
  normalSpeed = 0.9 * masterSpeed;
  followLineCheckTJunction();
  normalSpeed = 0.7 * masterSpeed;
  leftTurnPlus_Junction();
  setObjectSensor(LOW);
  yield();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(1, 12);
  delay(10);
  getB1();
  delay(10);
  placeB1toCarrier();
  delay(10);
  normalSpeed = 0.7 * masterSpeed;
  reverseCheckTJuction();
  turnRight90_AfterReverse();
  delay(10);
  setArmForB2();
  delay(10);
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(1, 12);
  delay(10);
  getB2();
  delay(10);
  setObjectSensor(HIGH);
  normalSpeed = 0.6 * masterSpeed;
  followLineCheckLeftTurn();
  leftTurnT_JunctionSideway();
  followLineCheckTJunction();
  leftTurnT_JunctionWithYellow();
  normalSpeed = 0.6 * masterSpeed;
  followYellowLineCheckLeftTurn();
  passLeftTurnOnYellow();
  normalSpeed = 0.5 * masterSpeed;
  //setObjectSensor(LOW);
  followYellowLineCheckObstacle(2, 17);
  delay(10);
  placeB2();
  delay(10);
  setObjectSensor(HIGH);
  normalSpeed = 0.7 * masterSpeed;
  reverseTurnLeftToTrack();
  normalSpeed = 0.9 * masterSpeed;
  followLineCheckTJunction();
  rightTurnPlus_Junction();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckTJunction();
  forwardBreak();
  rightTurnT_Junction();
  forwardBreak();
  setObjectSensor(LOW);
  yield();
  normalSpeed = 0.5 * masterSpeed;
  followYellowLineCheckObstacle(1, 12);
  delay(10);
  getB1fromCarrier();
  delay(10);
  placeB1();
  delay(10);
  setObjectSensor(HIGH);
  yield();
  
  normalSpeed = 0.6 * masterSpeed;
  reverseTurnRightT_Juction();
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckTJunction();
  passT_Junction();
  
  normalSpeed = masterSpeed;
  followLineCheckTJunction();
  passT_Junction();
  followLineCheckLeftTurn();
  
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckRightTurn();
  normalSpeed = 0.5 * masterSpeed;
  rightTurnT_JunctionSideway();
  
  setObjectSensor(LOW);
  normalSpeed = 0.6 * masterSpeed;
  followLineCheckRightTurn();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(2, 17);
  delay(10);
  getJ1();
  delay(10);
  setObjectSensor(HIGH);
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckTJunction();
  leftTurnT_Junction();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(2, 12);
  delay(10);
  placeJ1();
  delay(10);
  
  normalSpeed = 0.8 * masterSpeed;
  reverseTurnLeftAfterJ1();
  normalSpeed = masterSpeed;
  followLineCheckLeftTurn();
  normalSpeed = 0.8 * masterSpeed;
  followLineCheckTJunction();
  rightTurnT_Junction();
  
  normalSpeed = masterSpeed;
  followLineCheckTJunction();
  normalSpeed = 0.8 * masterSpeed;
  rightTurnPlus_Junction();
  setObjectSensor(LOW);
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(2, 12);
  delay (10);
  getB3();
  delay (10);
  placeB3toCarrier();
  delay(10);
  normalSpeed = 0.8 * masterSpeed;
  reverseCheckTJuction();
  turnRight180Plus_Junction_AfterReverse();
  setObjectSensor(LOW);
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(2, 10);
  delay (10);
  getM3();//to get M3
  delay (10);
  setObjectSensor(HIGH);
  normalSpeed = 0.8 * masterSpeed;
  reverseCheckTJuction();
  turnRight90_AfterReverse();
  followLineCheckTJunction();
  rightTurnT_JunctionM3();
  followLineCheckTJunction();
  leftTurnPlus_Junction();
  followLineCheckRightTurn();
  
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckTJunction();
  forwardBreak();
  rightTurnT_Junction();
  forwardBreak();
  setObjectSensor(LOW);
  yield();
  normalSpeed = 0.5 * masterSpeed;
  followYellowLineCheckObstacle(1, 12);
  delay(10);
  placeM3();
  delay(10);
  getB3fromCarrier();
  delay(10);
  placeB3();
  delay(10);
  
  normalSpeed = 0.6 * masterSpeed;
  setObjectSensor(HIGH);
  yield();
  reverseTurnRightT_Juction();
  setObjectSensor(LOW);
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckTJunction();
  //forwardBreak();
  positionB4();
  //passT_Junction();
  //followLineCheckObstacle(2, 16);
  //reverseAfterGettingObstacle();
  
  delay (10);
  getB4();
  delay (10);
  placeB4toCarrier();
  delay(10);
  
  normalSpeed = 0.8 * masterSpeed;
  followLineCheckTJunction();
  rightTurnPlus_Junction();
  followLineCheckTJunction();
  passT_Junction();
  followLineCheckLeftTurn();
  normalSpeed = 0.5 * masterSpeed;
  followLineCheckObstacle(1, 12);
  delay(10);
  getM4();
  delay(10);
  reverseTurnRight180AfterM4();
  
  normalSpeed = 0.7 * masterSpeed;
  followLineCheckTJunction();
  passT_Junction();
  followLineCheckTJunction();
  passT_Junction();
  
  followLineCheckTJunction();
  leftTurnT_JunctionWithYellow();
  normalSpeed = 0.5 * masterSpeed;
  followYellowLineCheckLeftTurn();
  passLeftTurnOnYellow();
  followYellowLineCheckObstacle(1, 12);
  delay(10);
  placeM4();
  delay(10);
  getB4fromCarrier();
  delay (10);
  placeB4();
  delay (10);
  
  normalSpeed = 0.8 * masterSpeed;
  reverseTurnLeftToTrack();
  followLineCheckTJunction();
  passT_Junction();
  followLineCheckTJunction();
  leftTurnT_Junction();
  followLineCheckTJunction();
  rightTurnT_Junction();
  followLineCheckTJunction();
  leftTurnPlus_Junction();
  
  normalSpeed = 0.9 * masterSpeed;
  followLineCheckLeftTurn();
  normalSpeed = 0.8 * masterSpeed;
  leftTurnT_JunctionSideway();
  followLineCheckRightTurn();
  followLineCheckTJunction();
  rightTurnT_Junction();
  
  normalSpeed = 0.8 * masterSpeed;
  followLineCheckLeftTurn();
  leftTurnT_JunctionSideway();
  followLineCheckLeftTurn();
  leftTurn90();
  normalSpeed = 1.2 * masterSpeed;
  followLineCheckTJunction();
  packStartZone();
  
  stopMove();
  while (1);
}
