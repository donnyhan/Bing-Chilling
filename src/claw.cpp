#include "const.h"
#include "claw.h"

//servos 
Servo servoClaw;
Servo servoJoint;
Servo servoBase;
const int CLAWMAX = 150;
const int BASEMAXDISP = 60;
const int JOINTMAX = 130;

void clawSetup() {
  servoJoint.write(180);
  servoClaw.attach(SERVOCLAW);
  servoJoint.attach(SERVOJOINT);
  servoBase.attach(SERVOBASE);
  servoClaw.write(CLAWMAX);
  servoBase.write(90);
  delay(1000);

};

void rotateZero(int base_current_pos){
    
    if(base_current_pos<90){
        while(base_current_pos<90){
            servoBase.write(base_current_pos);
            base_current_pos++;
        }
        delay(30);
    }
    else if(base_current_pos>90){
        while(base_current_pos>90){
            servoBase.write(base_current_pos);
            base_current_pos--;
        }
        delay(30);
    }
    else{}
}


//returns current position
int baseRotate(int base_target_pos, int base_current_pos){
    if (base_current_pos< base_target_pos){
        while(base_current_pos < base_target_pos){
            servoBase.write(base_current_pos);
            base_current_pos++;
            delay(20);
        }
    }
    else if(base_current_pos>base_target_pos){
        while(base_current_pos>base_target_pos){
            servoBase.write(base_current_pos);
            base_current_pos--;
            delay(20);
        }
    }
    else{}
    return base_current_pos;
}

void clawJoint(int state){ //only 3 states: raised = 1, lowered = 0, zipline2 = 2
    int joint_pos;
    if(state == 1){
        for(joint_pos = 0; joint_pos < JOINTMAX; joint_pos +=1){
            servoJoint.write(180-joint_pos);
            delay(20);
        }
    }
    else if (state ==0){
        for (joint_pos = JOINTMAX; joint_pos > 0; joint_pos -= 1) { 
            servoJoint.write(180-joint_pos);        
            delay(10);  
        }  
    }
    else{
        for(joint_pos = 0; joint_pos < 90; joint_pos+= 1 ){
            servoJoint.write(180-joint_pos);
            delay(10);
        }
    }
}

//pinion
void ForwardStep(float distancecm) 
{
  digitalWrite(dir, HIGH);
  int stepNum = distancecm*320;
  for(int y=0; y<stepNum; y++)
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(2);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
  }
}

void BackwardStep(float distancecm) 
{
  digitalWrite(dir, LOW);
  int stepNum = distancecm*320;
  for(int y=0; y<stepNum; y++)
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(2);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
  }
}

// returns safe = 1 to pick up treasure; if its bomb, claw won't pick up
int bomb(){
  int state = analogRead(HALL);
  int safe = 1;
  if (state < bombThreshold) { //bomb
    safe = 0;
  }
  else { // treasure
  }

  return safe;
}

void clawPickUp(int current_base_pos){ //sonar successfully detects treasure

    //close claw
    for (int claw_pos = CLAWMAX; claw_pos > 0; claw_pos -= 1) { 
        servoClaw.write(claw_pos);
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
        servoClaw.write(claw_pos);
        delay(10);         
    }

    //lower joint
    clawJoint(0);
    
    //return to rack original position
    BackwardStep(7.5);
}