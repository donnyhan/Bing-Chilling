#ifndef CLAW_C
#define CLAW_C

#include "const.h"
#include <claw.h>

Servo* Claw::claw_servo_ptr;
Servo* Claw::joint_servo_ptr;
Servo* Claw::base_servo_ptr;

void Claw::initializeClaw(Servo* _claw_servo){
    Claw::claw_servo_ptr = _claw_servo;
}

void Claw::initializeJoint(Servo* _joint_servo){
    Claw::joint_servo_ptr = _joint_servo;
}

void Claw::initializeBase(Servo* _base_servo){
    Claw::base_servo_ptr = _base_servo;
}





void Claw::clawSetup() {
  claw_servo_ptr->attach(SERVOCLAW);
  claw_servo_ptr->write(CLAWMAX);
  joint_servo_ptr->attach(SERVOJOINT);
  joint_servo_ptr->write(180);
  base_servo_ptr->attach(SERVOBASE);
  base_servo_ptr->write(90);
  delay(4000);

}

void Claw::rotateZero(int base_current_pos){
    
    if(base_current_pos<90){
        while(base_current_pos<90){
            base_servo_ptr->write(base_current_pos);
            base_current_pos++;
            delay(20);
        }
        
    }
    else if(base_current_pos>90){
        while(base_current_pos>90){
            base_servo_ptr->write(base_current_pos);
            base_current_pos--;
            delay(20);
        }
        
    }
    else{}
}


//returns current position
int Claw::baseRotate(int base_target_pos, int base_current_pos){
    if (base_current_pos< base_target_pos){
        while(base_current_pos < base_target_pos){
            base_servo_ptr->write(base_current_pos);
            base_current_pos++;
            delay(20);
        }
    }
    else if(base_current_pos>base_target_pos){
        while(base_current_pos>base_target_pos){
            base_servo_ptr->write(base_current_pos);
            base_current_pos--;
            delay(20);
        }
    }
    else{}
    return base_current_pos;
}

void Claw::clawJoint(int state){ //only 3 states: raised = 1, lowered = 0, zipline2 = 2
    int joint_pos;
    if(state == 1){
        for(joint_pos = 0; joint_pos < JOINTMAX; joint_pos +=1){
            joint_servo_ptr->write(180-joint_pos);
            delay(20);
        }
    }
    else if (state ==0){
        for (joint_pos = JOINTMAX; joint_pos > 0; joint_pos -= 1) { 
            joint_servo_ptr->write(180-joint_pos);        
            delay(10);  
        }  
    }
    else{
        for(joint_pos = 0; joint_pos < 90; joint_pos+= 1 ){
            joint_servo_ptr->write(180-joint_pos);
            delay(10);
        }
    }
}

//pinion
void Claw::ForwardStep(float distancecm) 
{
  digitalWrite(dir, HIGH);
  int stepNum = distancecm*340;
  for(int y=0; y<stepNum; y++)
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
  }
}

void Claw::BackwardStep(float distancecm) 
{
  digitalWrite(dir, LOW);
  int stepNum = distancecm*340;
  for(int y=0; y<stepNum; y++)
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
  }
}

// returns safe = 1 to pick up treasure; if its bomb, claw won't pick up
int Claw::bomb(){
  int state = analogRead(HALL);
  int safe = 1;
  if (state < bombThreshold) { //bomb
    safe = 0;
  }
  else { // treasure
  }

  return safe;
}

void Claw::clawPickUp(int current_base_pos){ //sonar successfully detects treasure

    //close claw
    for (int claw_pos = CLAWMAX; claw_pos > 0; claw_pos -= 1) { 
        claw_servo_ptr->write(claw_pos);
        delay(10);
    } 

    //centre the base
    rotateZero(current_base_pos);

    //rack to depositing position
    BackwardStep(1.5);

    //raise joint
    clawJoint(1);

    //open claw
    for (int claw_pos = 0; claw_pos <= CLAWMAX; claw_pos += 1) { 
        claw_servo_ptr->write(claw_pos);
        delay(10);         
    }

    //lower joint
    clawJoint(0);
    
    //return to rack original position
    BackwardStep(7.5);
}

#endif