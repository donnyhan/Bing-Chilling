#ifndef LINKAGE_H
#define LINKAGE_H

#include <Servo.h>

class Linkage
{
public:
    static Servo* linkage_servo_ptr_1;
    static Servo* linkage_servo_ptr_2;
    static void initializeLink1(Servo* linkage_servo1);
    static void initializeLink2(Servo* linkage_servo2);
    static void linkageSetup();
    static void liftBox(); //lift the box up
    // static void returnBox();
};

#endif