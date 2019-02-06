//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef TANDENENGINE_INPUT_H
#define TANDENENGINE_INPUT_H

#include "Keyboard.h"

namespace TandenEngine {

    enum KeyCode {
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        Alpha_0 = 48,
        Alpha_1 = 49,
        Alpha_2 = 50,
        Alpha_3 = 51,
        Alpha_4 = 52,
        Alpha_5 = 53,
        Alpha_6 = 54,
        Alpha_7 = 55,
        Alpha_8 = 56,
        Alpha_9 = 57,
        Shift = 16,
        Control = 17,
        Alt = 18,
        ESC = 27
    };

    class Input {
     private:
        static Keyboard mKeyboard;
     public:
        static void GetInput();  // Update keyboard
        static bool GetKeyDown(KeyCode key);  // Check for input keycode pressed this frame
        static bool GetKey(KeyCode key);  // Check if input keycode is down
        static bool GetKeyUp(KeyCode key);  // Check if input key code released this frame
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_INPUT_H
