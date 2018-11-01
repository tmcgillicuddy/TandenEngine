//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_EVENTLISTENER_H
#define HWENGINE_EVENTLISTENER_H

#include "Events/Event.h"

class EventListener {
    friend class EventSystem;
private:
    virtual void ProcessEvent(Event*)=0;
};


#endif //HWENGINE_EVENTLISTENER_H
