#include "speed.h"

unsigned char caclculateSpeed(float deltaTime){
    //like this can't show more than 95km/h
    float speed = (WHEEL_2RPI * 3.6f) / deltaTime; // (2rPI * 3600 / 1000) / delta time    
    return (unsigned char)speed;
}
