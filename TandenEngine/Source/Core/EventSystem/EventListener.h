//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef TANDENENGINE_EVENTLISTENER_H
#define TANDENENGINE_EVENTLISTENER_H

#include "Events/Event.h"

namespace TandenEngine {

    class EventListener {
        friend class EventSystem;

     private:
        virtual void ProcessEvent(Event *) = 0;
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_EVENTLISTENER_H
