#ifndef TANDENENGINE_KEYBOARD_H
#define TANDENENGINE_KEYBOARD_H

#include <windows.h>

#include "../EventSystem/EventSystem.h"
#include "../EventSystem/Events/KeyboardEvent.h"

namespace TandenEngine {

    struct Key {
        bool state = false;
    };


    class Keyboard {
        friend class Input;

     public:
        void UpdateKeyboard();

     private:
        void FlushKeyboard();

        void DetectKeyChanges();

     protected:
        Key mKeys[101];
        Key mPrevKeys[101];
        Key mKeysDown[101];
        Key mKeysUp[101];
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_KEYBOARD_H
