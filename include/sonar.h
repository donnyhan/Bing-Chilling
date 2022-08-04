#ifndef SONAR_H
#define SONAR_H

#include "const.h"
#include "claw.h"

class Sonar
{
public:
    static NewPing* sonar_ptr;
    static void initializeSonar(NewPing* _sonar);
    static float getDist(float soundcm);
    static float getSoundSpeed();
    static void detecting(float soundcm, int targ_base_pos);
};

#endif
