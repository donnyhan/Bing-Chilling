#include "pinSetup.h"

void pinSetup()
{
    // Wheels
    pinMode(MOTOR_R_F, OUTPUT);
    pinMode(MOTOR_R_B, OUTPUT);
    pinMode(MOTOR_L_F, OUTPUT);
    pinMode(MOTOR_L_B, OUTPUT);

    //claw 
    pinMode(stp, OUTPUT);
    pinMode(dir, OUTPUT);

    //sonar

    //hall effect
     pinMode(HALL, INPUT);   
     



}