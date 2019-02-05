//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef TANDENENGINE_EVENT_H
#define TANDENENGINE_EVENT_H

namespace TandenEngine {

    class Event {
     public:
        enum EventType {
            INPUT
        };

        EventType mType;

        Event(EventType);
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_EVENT_H
