#ifndef IRFOLLOWING_H
#define IRFOLLOWING_H

#define LED_BUILTIN PB2
#define MOTOR_FREQ 200

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BASE_SPEED 500
#define IR_Threshold 50

volatile uint32_t P_value = 9;
volatile uint32_t D_value = 2;
volatile int Left_IR = 0;
volatile int Right_IR = 0;
volatile int error = 0;
volatile int lasterr = 0;
volatile int i = 0;

int PID (int P_gain, int D_gain, int R);
void read_Left_IR();
void read_Right_IR();
void tp_motor_left(int gain);
void tp_motor_right(int gain);
void tp_motor_straight();
void tp_motor_offIR();
void tp_motor_stop();

void read_Left_IR() {
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

void read_Right_IR() {
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

int PID (int P_gain, int D_gain, int R) {
  int P;
  int D;
  int G;
  
  P=P_gain*abs(R);
  D=D_gain*(abs(R)-abs(lasterr));

  G=P+D;
  lasterr=R;
  return G;
}

void tp_motor_straight() {
  pwm_start(MOTOR_R_F, MOTOR_FREQ, BASE_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
  pwm_start(MOTOR_L_F, MOTOR_FREQ, BASE_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void tp_motor_left(int gain) {
  pwm_start(MOTOR_R_F, MOTOR_FREQ, BASE_SPEED+gain, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
  pwm_start(MOTOR_L_F, MOTOR_FREQ, 90, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void tp_motor_right(int gain) {
  pwm_start(MOTOR_R_F, MOTOR_FREQ, 90, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
  pwm_start(MOTOR_L_F, MOTOR_FREQ, BASE_SPEED+gain, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void tp_motor_offIR() {
  int G;
  G=110;
  display_handler.setCursor(70,20);
  if (error > 0) {
    tp_motor_left(G);
   //display_handler.println("left");
  }
  else if (error < 0) {
    tp_motor_right(G);
    //display_handler.println("right");
  }
  else {
    tp_motor_straight();
    //display_handler.println("straight");
  }

  //display_handler.println(G);
  display_handler.display();
  
}
void tp_motor_stop() {
pwm_start(MOTOR_R_F, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
pwm_start(MOTOR_L_F, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}