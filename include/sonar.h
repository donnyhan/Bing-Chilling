#ifndef SONAR_H
#define SONAR_H

#include "const.h"
#include "claw.h"

class Sonar
{
public:
    Sonar(Claw claww);
    float getDist(float soundcm);
    float getSoundSpeed();
    void detecting(float soundcm, int targ_base_pos);
    Claw claw;
    Servo servoClaw;
    Servo servoJoint;
    Servo servoBase;
};

#endif