#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <const.h>
#include <pinSetup.h>
#include <Encoders.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void handle_R_interrupt();

Encoders encoders1 = Encoders();
int countR = 0;
int value = 0;
volatile int interrupt_counter = 0;

void interrupt_handler_main();

void setup() {

pinMode(PB4,INPUT);

  attachInterrupt(digitalPinToInterrupt(PB4), handle_R_interrupt, RISING);

  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Starting up...");
  display_handler.display();

  delay(1000);
  
  // pwm_start(MOTOR_L_F, PWMFREQ, FWD_SPEED, RESOLUTION_10B_COMPARE_FORMAT);
  // pwm_start(MOTOR_R_F, PWMFREQ, FWD_SPEED, RESOLUTION_10B_COMPARE_FORMAT);

}

void loop(){
 
  display_handler.clearDisplay();
  display_handler.setCursor(0,0);

  // countR = encoders1.countR;

  display_handler.print("Counter:");
  display_handler.println(interrupt_counter);

  display_handler.print("CountR:");
  display_handler.println(encoders1.countR);

  // value++;
  // if (value > 1000) {
  //   value = 0;
  // }
  // display_handler.println(value);
  display_handler.display();
  delay(20);
  
  }

  void interrupt_handler_main()
  {
    
  }

void handle_R_interrupt()
{
  interrupt_counter++;
encoders1.handle_R_interrupt();
}
