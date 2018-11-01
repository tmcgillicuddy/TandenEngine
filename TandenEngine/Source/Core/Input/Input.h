//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_INPUT_H
#define HWENGINE_INPUT_H

#include "Keyboard.h"
class Input {
private:
    static Keyboard mKeyboard;
public:
    static void GetInput();
};




#endif //HWENGINE_INPUT_H
