//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_TIMER_H
#define HWENGINE_TIMER_H

#include <ctime>
#include <cstdlib>

namespace TandenEngine {

    class Timer {
    private:
        static constexpr double FRAMETIME = 0.0166;

    public:
        static float mCurrentTime;

        static void WaitForFrameTime();
    };

}
#endif //HWENGINE_TIMER_H
