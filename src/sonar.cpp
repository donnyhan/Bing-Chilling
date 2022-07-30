#include "const.h"
#include "sonar.h"
#include "claw.h"
#include "claw.cpp"
#include <NewPing.h>

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

float getDist(float soundcm){
    float dur = sonar.ping_median(ITERATIONS);
    float dist = (dur/200)*soundcm;
    return dist;
}

float getSoundSpeed(){
    //sound speed in m/s
    float soundc = 331.4 + (0.606 * TEMP) + (0.0124 * HUM);
    //convert to cm/ms
    float soundcm = soundc / 100;
    return soundcm;
}

void detecting(float soundcm, int targ_base_pos) { //target base position is the estimated position
// the arm should be in to get the treasure

     int distance, distanceL, distanceR, distanceL2, distanceR2;
     int treasure = 0;
     int curr_base_pos= getBasePos();
     int targL = targ_base_pos - ANGLE;
     int targR = targ_base_pos + ANGLE;

     while(treasure ==0){

        baseRotate(targ_base_pos, curr_base_pos);

        distance = getDist(soundcm);

        if (distance < 20){
            //Robot stops moving (wheel speed zero) 
            baseRotate(targL, base_pos);
            distanceL = getDist(soundcm);

            baseRotate(targ_base_pos-10, base_pos);
            distanceL2 = getDist(soundcm);

            baseRotate(targ_base_pos+10, base_pos);
            distanceR2 = getDist(soundcm);

            baseRotate(targR, base_pos);
            distanceR = getDist(soundcm);

            if((distance-distanceL)>= 6 && (distance-distanceR >= 6)){ // it's a potential treasure
                if( abs(distance-distanceL2)<=7 && abs(distance-distanceR2)<=7){ //it's a treasure
                // rack extends until the IR sensor no longer detects a signal as the idle is between the claw
                // check the hall effect sensor
                int treasure_pos = getBasePos();
                if( bomb() ==1 ){// trasure, claw picks up
                    ForwardStep(9);
                    clawPickUp(treasure_pos);
                }
                else{
                    //claw don't pick up
                }

                treasure == 1;
                }
                else{}
            }
            else{

            }
        }

    }

   if(treasure==1){
    //robot continues to move
    delay(1000);
   }
}