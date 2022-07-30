#include "const.h"

class claw
{
public:
void clawSetup();
void rotateZero(int base_current_pos);
void baseRotate(int base_target_pos, int base_current_pos);
void clawJoint(int state);
void clawPickUp(int base_pos);
void ForwardStep(float distancecm);
void BackwardStep(float distancecm);
int getBasePos(int base_pos);
int bomb();

};