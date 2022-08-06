#ifndef LINKAGE_C
#define LINKAGE_C

#include "const.h"
#include <linkage.h>

Servo* Linkage::linkage_servo_ptr_1;
Servo* Linkage::linkage_servo_ptr_2;

void Linkage::initializeLink1(Servo* linkage_servo1){
    Linkage::linkage_servo_ptr_1 = linkage_servo1;
}

void Linkage::initializeLink2(Servo* linkage_servo2){
    Linkage::linkage_servo_ptr_2 = linkage_servo2;
}

void Linkage::linkageSetup(){
    linkage_servo_ptr_1->attach(linkL);
    linkage_servo_ptr_2->attach(linkR);
    linkage_servo_ptr_1->write(0);
    linkage_servo_ptr_2->write(0);
    delay(3000);
}

void Linkage::liftBox(){

    int val = 135;
    //servo turns to lift box
    for (int pos = 0; pos <= val; pos += 1) { 
        // in steps of 1 degree
        linkage_servo_ptr_1->write(pos);
        linkage_servo_ptr_2->write(pos);
        delay(40);
    }
    delay(5000);
     for (int pos = val; pos >= 0; pos -= 1) { 
        linkage_servo_ptr_1->write(pos);
        linkage_servo_ptr_2->write(pos);
        delay(40);                       // waits 15ms for the servo to reach the position
    }
    delay(5000);
}



#endif