#ifndef TAPEFOLLOWING_C
#define TAPEFOLLOWING_C

#include <const.h>
#include <tapeFollowing.h>

//get gain
int Tape::PID(int P_gain, int D_gain, int R) {
    
  int P=P_gain*abs(R);
  int D=D_gain*(abs(R)-lasterr);

  int G=P+D;
  lasterr=R;
  return G;
}

void Tape::tp_motor_straight() {
  pwm_start(MOTOR_R_F, MOTOR_FREQ, BASE_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
  pwm_start(MOTOR_L_F, MOTOR_FREQ, BASE_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void Tape::tp_motor_left(int gain) {
  pwm_start(MOTOR_R_F, MOTOR_FREQ, BASE_SPEED+gain, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
  pwm_start(MOTOR_L_F, MOTOR_FREQ, 90, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void Tape::tp_motor_right(int gain) {
  pwm_start(MOTOR_R_F, MOTOR_FREQ, 90, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
  pwm_start(MOTOR_L_F, MOTOR_FREQ, BASE_SPEED+gain, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void Tape::tp_motor_offtape() {
  int Gain;
  Gain=110;
  //display_handler.setCursor(70,20);
  if (error > 0) {
    tp_motor_left(Gain);
   //display_handler.println("left");
  }
  else if (error < 0) {
    tp_motor_right(Gain);
    //display_handler.println("right");
  }
  else {
    tp_motor_straight();
    //display_handler.println("straight");
  }

  //display_handler.println(G);
  //display_handler.display();
  
}
void Tape::tp_motor_stop() {
pwm_start(MOTOR_R_F, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
pwm_start(MOTOR_R_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
 
pwm_start(MOTOR_L_F, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
pwm_start(MOTOR_L_B, MOTOR_FREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void Tape::edges(){
  int leftEdge, rightEdge;

  leftEdge = digitalRead(edgeL);
  rightEdge = digitalRead(edgeR);

  if(leftEdge == 0 && rightEdge ==1 ){
    //motor moves back a bit and to the right
  }

  if (rightEdge ==0 && leftEdge ==1){
    //motor moves back a bit and to the left
  }

  if(rightEdge ==1 && leftEdge ==1){
    //robot moves straight 
  }

  if(rightEdge == 0 && leftEdge ==0){
    //moves back
  }

}

#endif