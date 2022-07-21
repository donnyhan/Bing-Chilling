#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Motor enc output pulse per rotation (change as req; motors diff: check spec sheet)
#define ENC_COUNT_REV 3000

//enc output to BP interrupt pin
#define ENC_IN PB3

//hbridge
#define MOTOR_A PA1 // analog out pin
#define MOTORA PA_1 //pwm
#define MOTOR_B PA2   // analog out pin
#define MOTORFREQ 500

//Analog pin for potentiometer
int speedcontrol = 0;

//Pulse count from encoder
volatile long encValue = 0;

//One-second interval for measurements (bcs measure pulse form 1s intervals)
int interval = 1000;

//Counters for milliseconds during interval
long prevMillis = 0;
long currentMillis = 0;

//Var for RPM measurement
int rpm = 0;

//Var for PWM motor speed output
int motorPWM = 0;

void updateEncoder();

void setup(){

    // put your setup code here, to run once:

    display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    delay(1000);
    display_handler.clearDisplay();
  
    display_handler.setTextSize(1);
    display_handler.setTextColor(SSD1306_WHITE);
    display_handler.setCursor(0,0);
    display_handler.println("Hello world!");
    display_handler.display();

  //set encoder as input with internal pullup
    pinMode(ENC_IN, INPUT_PULLUP);
  
  //hbridge
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(MOTORA,OUTPUT);
    pinMode(MOTOR_B,OUTPUT);

  //Attach interrupt
    attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);

  //set up initial values for timer
    prevMillis = millis();
    delay(500);
    display_handler.clearDisplay();

}

void loop(){
    display_handler.clearDisplay();
    display_handler.setTextSize(1);
    display_handler.setTextColor(SSD1306_WHITE);
    display_handler.setCursor(0,0);
    display_handler.println("start");
    display_handler.display();
    //control motor with potentiometer: map 1-1023 to 0-255
    motorPWM = map(analogRead(PA0), 0 ,1023, 0, 3800);

    //Write PWM to controller
    pwm_start(MOTORA, MOTORFREQ, motorPWM, RESOLUTION_12B_COMPARE_FORMAT);

    //update RPM value every second
    currentMillis = millis();

    if(currentMillis - prevMillis > interval){ //if yes, a second elapsed
        prevMillis = currentMillis; //reset

        //calc RPM
        rpm = (float)( encValue * 60/ ENC_COUNT_REV);

        //only update display when there's a reading
        if(motorPWM > 0 || rpm > 0 ){
            display_handler.println("PWM value : ");
            display_handler.println(motorPWM);
            display_handler.println("Pulses : ");
            display_handler.println(encValue);
            display_handler.println("Speed : ");
            display_handler.println(rpm);
            display_handler.display();
        }

        encValue = 0;
    }

}

void updateEncoder(){
    // Increment value for each pulse from encoder
    encValue++;
}
