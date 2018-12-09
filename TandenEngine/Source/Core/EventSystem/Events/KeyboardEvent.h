//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_KEYBOARDEVENT_H
#define HWENGINE_KEYBOARDEVENT_H

#include "Event.h"

namespace TandenEngine {

    class KeyboardEvent : public Event {
    public:
        int mVal;

        KeyboardEvent(int val);
    };
}

#endif //HWENGINE_KEYBOARDEVENT_H
