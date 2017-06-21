//
//  Event.h
//
//  Created by Morten Nobel-Jørgensen on 8/18/13.
//  Copyright (c) 2013 morten. All rights reserved.
//  Open Source under New BSD License (http://opensource.org/licenses/BSD-3-Clause)

#pragma once

#include <iostream>
#include <functional>
#include "EventListener.h"
#include <vector>
#include <utility>

class AbstractEvent{
public:
    virtual bool removeListener(int id) = 0;
};

template <typename E>
class Event : public AbstractEvent{
public:
    EventListener<E> createListener(std::function<void (E)> listener){
        listeners.emplace_back(listener, eventListenerId);
        eventListenerId++;
        return EventListener<E>(this, eventListenerId-1);
    }

    SyncValue<E> createSyncValue(){
        SyncValue<E> syncValue;
        std::function<void (E)> updateFunction = [&](E e){
            syncValue.value = e;
        };
        listeners.emplace_back(updateFunction, eventListenerId);
        syncValue.listenerId = eventListenerId;
        syncValue.ae = this;
        eventListenerId++;
        return syncValue;
    }

    void notifyListeners(E e){
        for (auto & l : listeners){
            l.first(e);
        }
    }

    bool removeListener(int id){
        auto iter = listeners.begin();
        while (iter != listeners.end()){
            if (iter->second == id){
                listeners.erase(iter);
                return true;
            }
            iter++;
        }
        return false;
    }
protected:
    std::vector<std::pair<std::function<void (E)>, int>> listeners;
    friend class EventListener<E>;
    int eventListenerId = 0;
};
