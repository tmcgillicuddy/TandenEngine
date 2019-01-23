//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "Keyboard.h"

namespace TandenEngine {

    void Keyboard::UpdateKeyboard() {
        FlushKeyboard();
        DetectKeyChanges();
    }

    void Keyboard::FlushKeyboard() {
        int i;
        for (i = 0; i < 101; ++i) {
            mPrevKeys[i].state = mKeys[i].state;
        }

        for (i = 0; i < 101; ++i) {
            mKeys[i].state = GetAsyncKeyState(i);
        }
    }

    void Keyboard::DetectKeyChanges() {
        Key changes[101];

        for (int i = 0; i < 101; ++i) {
            changes[i].state =
                    mKeys[i].state ^ mPrevKeys[i].state; //If the current state and previous state are different

            if (changes[i].state) { //If there WAS a change
                mKeysDown[i].state = changes[i].state & mKeys[i].state; //Set the down keys
                mKeysUp[i].state = changes[i].state & !mKeys[i].state; //SEt the up keys

                //auto *newEvent = new KeyboardEvent(i);
                //Send Event
                //EventSystem::AddEvent(newEvent);
            }
        }
    }
}