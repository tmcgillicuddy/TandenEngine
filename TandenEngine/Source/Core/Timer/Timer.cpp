//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "Timer.h"
#include <iostream>

namespace TandenEngine {

    float Timer::mCurrentTime = 0.0f;

    float Timer::GetFrameTime() {
        return FRAMETIME;
    }

    void Timer::WaitForFrameTime() {
        mCurrentTime += 0.0166f;
        clock_t startTime = clock();
        bool wait = true;
        double secondsPassed;
        while (wait) {
            secondsPassed = (clock() - startTime) / (double) CLOCKS_PER_SEC;

            if (secondsPassed >= FRAMETIME) {
                wait = false;
            }
        }
    }
}  // namespace TandenEngine
