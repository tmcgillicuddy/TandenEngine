//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_EVENTSYSTEM_H
#define HWENGINE_EVENTSYSTEM_H

#include <queue>
#include <iostream>


#include "Events/Event.h"
#include "EventListener.h"

class EventSystem {
private:
    static std::queue<Event*> mEvents; //Current Events to process
    static std::vector<EventListener*> mListeners; //Current listeners

public:
    EventSystem();
    static bool RegisterListener(EventListener*);
    static bool DeregisterListener(EventListener*);

    static void ProcessEvents(); //Processes events on the queue

    static void AddEvent(Event*);
};

#endif //HWENGINE_EVENTSYSTEM_H
