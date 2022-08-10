#ifndef IRFOLLOWING_H
#define IRFOLLOWING_H

#define IR_Threshold 50

// Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


class IR
{
public: 
  int PID (int P_gain, int D_gain, int R);
  void read_Left_IR();
  void read_Right_IR();
  void IR_Run();

  volatile uint32_t IR_P_value = 9;
  volatile uint32_t IR_D_value = 2;
  volatile int Left_IR = 0;
  volatile int Right_IR = 0;
  volatile int IR_error = 0;
  volatile int IR_lasterr = 0;

  enum IR_SENSOR {LEFT_IR, RIGHT_IR};

};

#endif

