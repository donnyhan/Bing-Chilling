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

void Linkage::dropRamp(){
    int turn = 100;

    for (int posi = 0; posi <= turn; posi += 1) { 
        // in steps of 1 degree
        linkage_servo_ptr_1->write(posi);
        linkage_servo_ptr_2->write(posi);
        delay(30);
    }
    delay(2000);
     for (int posi = turn; posi >= 0; posi -= 1) { 
        linkage_servo_ptr_1->write(posi);
        linkage_servo_ptr_2->write(posi);
        delay(30);                      
    }


}



#endif