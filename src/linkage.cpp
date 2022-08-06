#ifndef LINKAGE_C
#define LINKAGE_C

#include "const.h"
#include <linkage.h>

Servo* linkage::linkage_servo_ptr_1;
Servo* linkage::linkage_servo_ptr_2;

void linkage::initializeLink1(Servo* linkage_servo1){
    linkage::linkage_servo_ptr_1 = linkage_servo1;
}

void linkage::initializeLink2(Servo* linkage_servo2){
    linkage::linkage_servo_ptr_2 = linkage_servo2;
}

void linkage::liftBox(){
    linkage_servo_ptr_1->attach(linkL);
    linkage_servo_ptr_2->attach(linkR);
    
    //servo turns to lift box
}



#endif