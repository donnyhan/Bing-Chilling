#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//pins
//enc output to BP interrupt pin
#define ENC_IN PB3
//hbridge
#define MOTOR_A PA1 // analog out pin
#define MOTORA PA_1 //pwm
#define MOTOR_B PA2   // analog out pin

void updateEncoder();

int pos = 0;    
long prevT = 0;
float eprevT = 0;
float eintegral = 0;
int encValue;

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);


void setup(){

    //set encoder as input with internal pullup
    pinMode(ENC_IN, INPUT_PULLUP);
  
    //hbridge
    pinMode(MOTORA,OUTPUT);
    pinMode(MOTOR_B,OUTPUT);

    //Attach interrupt
    attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);

    display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display_handler.clearDisplay();
    display_handler.setTextSize(2);
    display_handler.setTextColor(SSD1306_WHITE);
    display_handler.setCursor(0,0);
    display_handler.println("Setup done");
    display_handler.display();
    delay(1000);

}

void loop(){

     display_handler.clearDisplay();
     display_handler.setCursor(0,0);

     //set target position
     int target = 1200;

     //PID constants
     float kp = 1;
     float kd = 0;
     float ki = 0;

     //time difference
     long currentT = millis();

     float deltaT = ((float)(currentT - prevT))/1.0e3;
     prevT = currentT;

     //error
     int e = pos - target;

     //derivative 
     float dedt = (e-eprevT)/(deltaT);

     //integral 
     eintegral = eintegral + e*deltaT;

     //control signal
     float u = kp*e + kd*dedt + ki*eintegral;

     //motor power 
     float pwr = fabs(u);
     if(pwr > 255){
        pwr = 255;
     }

     //motor direction
     int dir = 1;
     if(u<0){
        dir = -1;
     }

     //signal the motor
     setMotor(dir,pwr,MOTORA,MOTOR_A,MOTOR_B);
     
     //store prev error
     eprevT = e;

    

}


void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}
