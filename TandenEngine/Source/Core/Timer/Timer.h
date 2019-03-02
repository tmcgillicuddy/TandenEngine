//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef TANDENENGINE_TIMER_H
#define TANDENENGINE_TIMER_H

#include <ctime>
#include <cstdlib>

namespace TandenEngine {

    class Timer {
     private:
        static constexpr double FRAMETIME = 0.0166;

     public:
        static float mCurrentTime;
        static float GetFrameTime();
        static void WaitForFrameTime();
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_TIMER_H
