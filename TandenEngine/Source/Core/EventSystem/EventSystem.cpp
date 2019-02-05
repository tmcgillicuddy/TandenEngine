//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "EventSystem.h"

namespace TandenEngine {

    std::queue<Event *> EventSystem::mEvents;
    std::vector<EventListener *> EventSystem::mListeners;

    EventSystem::EventSystem() {
    }

    bool EventSystem::RegisterListener(EventListener *newListener) {
        mListeners.emplace_back(newListener);
        return false;
    }

    bool EventSystem::DeregisterListener(EventListener *) {
        return false;
    }

    void EventSystem::ProcessEvents() {
        Event *thisEvent = nullptr;
        while (!mEvents.empty()) {
            thisEvent = mEvents.front();  // point to the next event
            for (auto &listener : mListeners) {  // Tell all listeners that this event happened
                listener->ProcessEvent(thisEvent);
            }

            mEvents.pop();  // Remove the processed Event
        }
    }

    void EventSystem::AddEvent(Event *newEvent) {
        mEvents.push(newEvent);
    }

}  // namespace TandenEngine
