#ifndef CONST_H
#define CONST_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible

// all pins defined here

//claw
#define stp PB12
#define dir PB13
#define SERVOCLAW PA1
#define SERVOJOINT PA10
#define SERVOBASE PA0

#define HALL PA2

//Reflectance
#define R1 PB1
#define R2 PB0
#define R3 A7
#define R4 A6

//IR
#define IR1 PA4
#define IR2 PA5

//Wheels & H-bridge
#define MOTOR_L_F PB_6
#define MOTOR_L_B PB_7
#define MOTOR_R_F PB_8
#define MOTOR_R_B PB_9

//Rotary Enc
#define enc_1 PB3
#define enc_2 PB4

//Reflectance on the edges
#define edgeL PA12
#define edgeR PA15

//Claw sonar sensor
#define TRIG_PIN PB15
#define ECHO_PIN PB15

//4 bar linkage
#define linkL PA8
#define linkR PA9

///////
//other constants defined here
//////

//clawTreasure
Servo servoClaw;
Servo servoJoint;
Servo servoBase;
const int CLAWMAX = 150;
const int BASEMAXDISP = 60;
const int JOINTMAX = 130;

//SONAR
#define MAX_DISTANCE 400
#define ITERATIONS 5
#define HUM 40
#define TEMP 20
#define ANGLE 30

//HALL
#define bombThreshold 100



#define MOTOR_FREQ 500

//Encoders
#define PWMFREQ 2000
#define FWD_SPEED 885
#define BACK_SPEED 885


// from Zephko:
#define ENC_R_FWD 61
#define ENC_L_FWD 61
#define ENC_STRAIGHT_SPEED 890

#endif