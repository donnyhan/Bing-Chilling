#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <const.h>
#include <pinSetup.h>
#include <Encoders.h>
#include <claw.h>
#include <sonar.h>
#include <linkage.h>
#include <tapeFollowing.h>
#include <IRFollowing.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void handle_L_interrupt();
void handle_interrupt();
void Tape_following();
void IR_following();

//Encoders encoders1 = Encoders();

Servo servoClaw;
Servo servoJoint;
Servo servoBase;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing backSonar(BACK_TRIG_PIN,BACK_ECHO_PIN,MAX_DISTANCE);

Servo servoLinkL;
Servo servoLinkR;
Tape Tape_follow (4,1);

enum IR_SENSOR {LEFT_IR, RIGHT_IR};

const float soundc = 331.4 + (0.606 * TEMP) + (0.0124 * HUM);
const float soundcm = soundc / 100;
volatile int stage = 1;

HardwareSerial Serial2(USART2);   // PA3  (RX)  PA2  (TX)

void setup() {
  pinSetup();
  // Serial2.begin(9600);  // PA3  (RX)  PA2  (TX)
  // attachInterrupt(digitalPinToInterrupt(enc_L), handle_L_interrupt, FALLING);

  // Claw::initializeClaw(&servoClaw);
  // Claw::initializeBase(&servoBase);
  // Claw::initializeJoint(&servoJoint);
  // Sonar::initializeSonar(&sonar, &backSonar);
  Linkage::initializeLink(&servoLinkL, &servoLinkR);

  // display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display_handler.clearDisplay();
  // display_handler.setTextSize(1);
  // display_handler.setTextColor(SSD1306_WHITE);
  // display_handler.setCursor(0,0);
  // display_handler.display();

  // Claw::clawSetup();
  Linkage::linkageSetup();


  attachInterrupt(digitalPinToInterrupt(enc_L), handle_interrupt, RISING);

  
  //pwm_start(MOTOR_L_F, PWMFREQ, FWD_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  //pwm_start(MOTOR_R_F, PWMFREQ, FWD_SPEED, RESOLUTION_10B_COMPARE_FORMAT);

  //Serial2.println("Serial2: 2");



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
  // Serial2.println(analogRead(HALL));
  // delay(200);
  // Linkage::liftBox();
  // delay(2000);
  // Linkage::dropRamp();
  // delay(2000);

  while (stage == 1) {
    Tape_following();
    Sonar::detecting(soundcm, LEFTMOST);
  }

  while(stage == 2) {
    IR_following();
    Sonar::detecting(soundcm, LEFTMOST);
  }

  while(stage == 3) {
    //rampSection();
  }

}

void handle_interrupt() {
  //Tape.handle_interrupt();
  
}



// void rampSection() {
//   int distFromBeacon = 1000;
//   const int countFor90 = 999;
//   const int idealDist = 20;

//   //while further than we want, keep moving
//   while (distFromBeacon>idealDist) {
//     distFromBeacon = Sonar::getDist(soundcm);
//   }

//   encoders1.rightPivotCount(countFor90);
//   encoders1.rightPivotCount(countFor90);
//   encoders1.rightPivotCount(countFor90);

//   Linkage::dropRamp();

//   encoders1.rightPivotCount(countFor90);
//   encoders1.rightPivotCount(countFor90);


//   //rotate left by 180 and drop ramp
//   //rotate left by 180 and move forward
// }


void Tape_following() {
  uint32_t P_value = Tape_follow.P_value;
  uint32_t D_value = Tape_follow.D_value;
  int reflectanceL = 0;
  int reflectanceR = 0;
  int reflectanceLL = 0;
  int reflectanceRR = 0;
  int Left_RFSensor = 0;
  int Right_RFSensor = 0;
  int error = 0;
  int lasterr = 0;
  int G = 0;
  int RL_error = 0;
  int RR_error = 0;
    
    reflectanceL = analogRead(R_L_Sensor);
    reflectanceR = analogRead(R_R_Sensor);
    reflectanceLL = analogRead(R_L_Sensor_2);
    reflectanceRR = analogRead(R_R_Sensor_2);
    while(reflectanceL > CW_Threshold && reflectanceR > CW_Threshold) {
    Tape_follow.tp_motor_right(40);
    reflectanceL = analogRead(R_L_Sensor);
    reflectanceR = analogRead(R_R_Sensor);
    error = 0;
    delay(180);
    Tape_follow.tp_motor_straight();
    delay(500);
    Tape_follow.tp_motor_stop();
  }

  while (reflectanceL <= OffTape_Threshold_X && reflectanceR <= OffTape_Threshold_X && reflectanceLL <= Side_Threshold_L && reflectanceRR <= Side_Threshold_R) {
    Tape_follow.tp_motor_offtape();
    delay(50);
    Tape_follow.tp_motor_stop();
    reflectanceL = analogRead(R_L_Sensor);
    reflectanceR = analogRead(R_R_Sensor);
    reflectanceLL = analogRead(R_L_Sensor_2);
    reflectanceRR = analogRead(R_R_Sensor_2);
    delay(20);
  
  }

  RL_error = reflectanceL - PID_Threshold_L;
  RR_error = reflectanceR - PID_Threshold_R;

    
  if (RL_error > 0 && RR_error > 0) {
    //**archway//
    error = 0;
    G = 0;
    Tape_follow.tp_motor_straight();
    // display_handler.setCursor(70,20);
    // display_handler.print("straight");
  }
  else if (RL_error < 0 && RR_error > 0) {
    error = RL_error;
    G=Tape_follow.PID(P_value,D_value,error);
    Tape_follow.tp_motor_right(G);
    
    // display_handler.setCursor(70,20);
    // display_handler.print("right");
  }
  else if (RR_error < 0 && RL_error > 0) {
    error = abs(RR_error);
    G=Tape_follow.PID(P_value,D_value,error);
    Tape_follow.tp_motor_left(G);
    
    // display_handler.setCursor(70,20);
    // display_handler.print("left");
  }
  else {
    if (reflectanceRR > Side_Threshold_R) {
      error = -160;
      G=Tape_follow.PID(P_value,D_value,error);
      Tape_follow.tp_motor_right(G);
      // display_handler.setCursor(70,20);
      // display_handler.print("right");
    }
    else if (reflectanceLL > Side_Threshold_L) {
      error = 130;
      G=Tape_follow.PID(P_value,D_value,error);
      Tape_follow.tp_motor_left(G);
      // display_handler.setCursor(70,20);
      // display_handler.print("left");
      if (reflectanceL > Archway_Threshold && reflectanceLL > Archway_Threshold) {
        while (reflectanceRR < Archway_Threshold) {
          Tape_follow.tp_motor_stop();
          delay(100);
          Tape_follow.left_turn(300);
          delay(100);
          Tape_follow.tp_motor_stop();
          delay(50);
          reflectanceRR = analogRead(R_R_Sensor_2);
        }
        Tape_follow.tp_motor_straight();
        delay(300);
        if (stage == 1) {
          stage++;
        }
      }
    }
  }
  
  // display_handler.setCursor(70,0);
  // display_handler.print("G ");
  // display_handler.println(G);
  // display_handler.setCursor(70,40);
  // display_handler.print("error");
  // display_handler.println(error);

  // display_handler.display();
  delay(50);

 
}

void IR_following() {
i = 0;

  while(i < 2) { //reads left and right IR sensor almost simulataneously
      
    if(i % 2 == 0) {
    read_IR(LEFT_IR);
    Left_IR = analogRead(IR_Sensor);

    } else {
    read_IR(RIGHT_IR);
    Right_IR = analogRead(IR_Sensor);

    }

    i++;

  }

  if(Left_IR != 0 && Right_IR != 0) { //checks to see if both are 0. (proceeds to next stage if so)
  IR_error = Left_IR - Right_IR;

    if(IR_error >= -IR_Threshold && IR_error <= IR_Threshold) { //if both sensors 
      IR_error = 0;
      G = 0;
      Tape::tp_motor_straight();

    } else if(IR_error > IR_Threshold) {
      G=PID(IR_P_value,IR_D_value,IR_error);
      Tape::tp_motor_left(G);
  
    } else if (IR_error < -IR_Threshold) {
      IR_error = abs(IR_error);
      G=PID(IR_P_value,IR_D_value,IR_error);
      Tape::tp_motor_right(G);

    }

  } else {

      if(stage == 2){
      stage++;
    }

  }

}