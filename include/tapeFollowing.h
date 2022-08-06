#ifndef TAPEFOLLLOWING_H
#define TAPEFOLLOWING_H

volatile uint32_t P_value = 9;
volatile uint32_t D_value = 2;
volatile int reflectanceL = 0;
volatile int reflectanceR = 0;

volatile int reflectanceL2 = 0;
volatile int reflectanceR2 = 0;

volatile int error = 0;
volatile int lasterr = 0;

class Tape
{
public:
    static int PID (int P_gain, int D_gain, int R);
    static void tp_motor_left(int gain);
    static void tp_motor_right(int gain);
    static void tp_motor_straight();
    static void tp_motor_offtape();
    static void tp_motor_stop();
};

#endif