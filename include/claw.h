#ifndef CLAW_H
#define CLAW_H

#include <Servo.h>
class Claw
{
public:
    Claw();
    void clawSetup();
    void rotateZero(int base_current_pos);
    int baseRotate(int base_target_pos, int base_current_pos);
    void clawJoint(int state);
    void clawPickUp(int base_pos);
    void ForwardStep(float distancecm);
    void BackwardStep(float distancecm);
    int getBasePos(int base_pos); //???
    int bomb();
    Servo servoClaw;
    Servo servoJoint;
    Servo servoBase;
};

#endif