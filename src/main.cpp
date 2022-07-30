#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <const.h>
#include <pinSetup.h>
#include <Encoders.h>
#include <sonar.h>
#include <claw.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float soundcm;

void setup() {

  pinSetup();
  soundcm = getSoundSpeed();

  //claw setup
  servoJoint.write(180);
  servoClaw.attach(SERVOCLAW);
  servoJoint.attach(SERVOJOINT);
  servoBase.attach(SERVOBASE);
  servoClaw.write(CLAWMAX);
  servoBase.write(90);
  delay(1000);
  
  // put your setup code here, to run once:
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.display();
  delay(500);

}

void loop(){
  detecting(soundcm, 30);
}
