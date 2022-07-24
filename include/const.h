#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible

// all pins defined here

#define BIG_SERVO PA_0
#define CLAWSERVO PA_1
#define HALL PA_2
#define REFLC3 PA_3
#define IR1 PA_4
#define IR2 PA_5
#define BIG_SERVO_ARM PA_6
#define SERVO_JOINT PA_7
#define SERVO_HOOK PA_8
#define MOTOR_L_PINION PA_9
#define MOTOR_R_PINION PA_10
#define SONAR_LA_EDGE PA_11
#define SONAR_LB_EDGE PA_12
#define SONAR_RA_EDGE PA_13
#define SONAR_RB_EDGE PA_14
#define MSWITCH PA_15
#define REFLEC1 PB_0
#define REFLEC2 PB_1
// PB 2 skipped
#define ENCODER_A PB_3
#define ENCODER_B PB_4
// PB 5 tentative if needed
#define ENCODER PB_5

#define WHEEL_L_A PB_6
#define WHEEL_L_B PB_7
#define WHEEL_R_A PB_8
#define WHEEL_R_B PB_9
#define SONAR_ZIPLINE_A PB_10
#define SONAR_ZIPLINE_B PB_11
// PB 12 & 13 for sonar sensor
#define SONAR_CLAW_A PB_14
#define SONAR_CLAW_B PB_15

//other constants defined here
