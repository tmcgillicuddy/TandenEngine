//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "KeyboardEvent.h"

namespace TandenEngine {

    KeyboardEvent::KeyboardEvent(int val) : Event(Event::INPUT) {
        mVal = val;
    }
}