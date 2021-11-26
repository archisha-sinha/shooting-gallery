#ifndef PING_H
#define PING_H

#include "Arduino.h"

class Ping
{
    public:
        Ping(int pin);
        void ping_init(void);
        bool is_distance_good(int desired_distance);

    private:
        int trig_echo_pin;
        long duration;
        int distance_inch;
        int prev_distance;
        void send_signal(void);
        void calculate_distance(void);
     
};

#endif
