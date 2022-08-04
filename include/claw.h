#ifndef CLAW_H
#define CLAW_H

#include <Servo.h>
class Claw
{
public:
    Servo* claw_servo_ptr;
    Servo* joint_servo_ptr;
    Servo* base_servo_ptr;
    Claw();
    void clawSetup();
    void initializeClaw(Servo* _claw_servo);
    void initializeJoint(Servo* _joint_servo);
    void initializeBase(Servo* _base_servo);
    void rotateZero(int base_current_pos);
    int baseRotate(int base_target_pos, int base_current_pos);
    void clawJoint(int state);
    void clawPickUp(int base_pos);
    void ForwardStep(float distancecm);
    void BackwardStep(float distancecm);
    int getBasePos(int base_pos); //???
    int bomb();
};

#endif