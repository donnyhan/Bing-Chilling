#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <const.h>
#include <pinSetup.h>
#include <Encoders.h>
#include <claw.h>
#include <sonar.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void handle_R_interrupt();

Encoders encoders1 = Encoders();

Servo servoClaw;
Servo servoJoint;
Servo servoBase;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

const float soundc = 331.4 + (0.606 * TEMP) + (0.0124 * HUM);
const float soundcm = soundc / 100;

HardwareSerial Serial2(USART2);   // PA3  (RX)  PA2  (TX)

void setup() {
  pinSetup();
<<<<<<< HEAD

 
=======
  Serial2.begin(9600);  // PA3  (RX)  PA2  (TX)
>>>>>>> 6cc692e6d404fd4fd398b52a975acba9868fde3a
  attachInterrupt(digitalPinToInterrupt(enc_R), handle_R_interrupt, FALLING);

    Claw::initializeClaw(&servoClaw);
  Claw::initializeBase(&servoBase);
  Claw::initializeJoint(&servoJoint);
  Sonar::initializeSonar(&sonar);

  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.display();

    Claw::clawSetup();

  
  pwm_start(MOTOR_L_F, PWMFREQ, FWD_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_F, PWMFREQ, FWD_SPEED, RESOLUTION_10B_COMPARE_FORMAT);

<<<<<<< HEAD
=======
  Serial2.println("Serial2: 2");


>>>>>>> 6cc692e6d404fd4fd398b52a975acba9868fde3a
}

// void loop(){
//   int countR = 0;
//   int value = 0;
//   display_handler.clearDisplay();
//   display_handler.setCursor(0,0);

//   countR = encoders1.countR;

//   display_handler.println("countR:");
//   display_handler.println(countR,DEC);

//   display_handler.display();
//   delay(200);
  
//   }

// void loop() {
//   Claw::baseRotate(150,90);
//   Claw::baseRotate(30,150);
//   Claw::ForwardStep(9);
//   Claw::clawPickUp(30);

// }

void loop() {
  // float distance = Sonar::detecting(soundcm, LEFTMOST);
  // Serial2.println(distance);
  Serial2.println(analogRead(HALL));
  delay(200);
}

void handle_R_interrupt()
{
  encoders1.handle_R_interrupt();
}
