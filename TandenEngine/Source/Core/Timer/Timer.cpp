//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "Timer.h"
#include <iostream>

void Timer::WaitForFrameTime() {
    clock_t startTime = clock();
    bool wait = true;
    double secondsPassed;
    while(wait)
    {
        secondsPassed = (clock() - startTime) / (double)CLOCKS_PER_SEC;
		
        if(secondsPassed >= FRAMETIME)
        {
            wait = false;
        }
    }
}

