#ifndef IRFOLLOWING_C
#define IRFOLLOWING_C

#include <const.h>
#include <IRFollowing.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IR_Left_Switch, OUTPUT);
  pinMode(IR_Right_Switch, OUTPUT);
  pinMode(IR_Sensor, INPUT);
  pinMode(IR_Discharge, OUTPUT);

  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.display();
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);

  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:
  int G;
  int IRL_error;
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  // digitalWrite(LED_BUILTIN, HIGH);

  display_handler.println("G:");
  display_handler.println(G);

  //display_handler.println("D:");
  //display_handler.println(D_value);

  i++;

  if(i % 2 == 0) {
    read_Left_IR();

  } else {
    read_Right_IR();

  }

    display_handler.println(Left_IR);
    display_handler.setCursor(0,25);
    display_handler.println(Right_IR);

  // display_handler.println(i);

  display_handler.display();

  IRL_error = Left_IR - Right_IR;

  if(IRL_error >= 0 && IRL_error <= IR_Threshold) {
    error = 0;
    G = 0;
    tp_motor_straight();
    display_handler.setCursor(70,20);
    display_handler.println("straight");
  
  } else if(IRL_error > IR_Threshold) {
    error = IRL_error;
    G=PID(P_value,D_value,error);
    tp_motor_left(G);
    
    display_handler.setCursor(70,20);
    display_handler.println("go left");
  
  } else if (IRL_error < 0) {
    error = abs(IRL_error);
    G=PID(P_value,D_value,error);
    tp_motor_right(G);
    
    display_handler.setCursor(70,20);
    display_handler.println("go right");

  }

  
  }

