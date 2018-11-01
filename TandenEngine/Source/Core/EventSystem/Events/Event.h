//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_EVENT_H
#define HWENGINE_EVENT_H


class Event {
public:
    enum EventType
    {
        INPUT
    };

    EventType mType;

    Event(EventType);


};


#endif //HWENGINE_EVENT_H
