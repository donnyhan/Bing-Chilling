#ifndef IRFOLLOWING_C
#define IRFOLLOWING_C

#include <const.h>
#include <IRFollowing.h>
#include <tapeFollowing.h>

void IR::read_IR(IR_SENSOR sensor)
  {
    int low_switch, high_switch;
    switch (sensor)
    {
    case LEFT_IR:
      low_switch = IR_Right_Switch;
      high_switch = IR_Left_Switch;
      break;
    case RIGHT_IR:
      low_switch = IR_Left_Switch;
      high_switch = IR_Right_Switch;
      break;
    }

    digitalWrite(low_switch, LOW);
    delay(50);
    digitalWrite(high_switch, HIGH);

    digitalWrite(IR_Discharge, HIGH);
    delay(3);
    digitalWrite(IR_Discharge, LOW);
    delay(3);

  }

void IR::read_Left_IR() {
    digitalWrite(IR_Right_Switch, LOW);
    delayMicroseconds(1);
    digitalWrite(IR_Left_Switch, HIGH);
    delay(100);

    digitalWrite(IR_Discharge, HIGH);
    delay(1);
    digitalWrite(IR_Discharge, LOW);
    delay(1);

    Left_IR = analogRead(IR_Sensor);
}

void IR::read_Right_IR() {
    digitalWrite(IR_Left_Switch, LOW);
    delayMicroseconds(1);
    digitalWrite(IR_Right_Switch, HIGH);
    delay(100);

    digitalWrite(IR_Discharge, HIGH);
    delay(1);
    digitalWrite(IR_Discharge, LOW);
    delay(1);

    Right_IR = analogRead(IR_Sensor);
}


void IR::IR_Run() {
  // put your main code here, to run repeatedly:
  int G;
  int i=0;
  int IRL_error;
  // display_handler.clearDisplay();
  // display_handler.setCursor(0,0);
  // digitalWrite(LED_BUILTIN, HIGH);

  // display_handler.println("G:");
  // display_handler.println(G);

  //display_handler.println("D:");
  //display_handler.println(D_value);

  i++;

  if(i % 2 == 0) {
    read_Left_IR();

  } else {
    read_Right_IR();

  }

    // display_handler.println(Left_IR);
    // display_handler.setCursor(0,25);
    // display_handler.println(Right_IR);

  // display_handler.println(i);

  // display_handler.display();

  IRL_error = Left_IR - Right_IR;

  if(IRL_error >= 0 && IRL_error <= IR_Threshold) {
    IR_error = 0;
    G = 0;
    Tape::tp_motor_straight();
    // display_handler.setCursor(70,20);
    // display_handler.println("straight");

  } else if(IRL_error > IR_Threshold) {
    IR_error = IRL_error;
    G=PID(IR_P_value,IR_D_value,IR_error);
    Tape::tp_motor_left(G);

    // display_handler.setCursor(70,20);
    // display_handler.println("go left");

  } else if (IRL_error < 0) {
    IR_error = abs(IRL_error);
    G=PID(IR_P_value,IR_D_value,IR_error);
    Tape::tp_motor_right(G);

    // display_handler.setCursor(70,20);
    // display_handler.println("go right");

  }


  }

  #endif
