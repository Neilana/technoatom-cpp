//
//  EventListener.h
//
//  Created by Morten Nobel-Jørgensen on 8/18/13.
//  Copyright (c) 2013 morten. All rights reserved.
//  Open Source under New BSD License (http://opensource.org/licenses/BSD-3-Clause)

#pragma once

#include <iostream>

class AbstractEvent;

class AbstractEventListener{
public:
    AbstractEventListener(){};
    AbstractEventListener(AbstractEvent *ae, int listenerId);
    AbstractEventListener(const AbstractEventListener&) = delete;
    AbstractEventListener& operator=( const AbstractEventListener& rhs ) = delete;

    virtual ~AbstractEventListener();
    friend class AbstractEvent;
protected:
    void destroyListener();
    int listenerId;
    AbstractEvent *ae = nullptr;
};

template <typename E>
class Event;

template <typename E>
class EventListener : public AbstractEventListener {
public:
    EventListener(){
    }
    EventListener(Event<E> *e, int listenerId)
    :AbstractEventListener(e, listenerId)
    {
    }

    EventListener(const EventListener&) = delete;
    EventListener& operator=( const EventListener& rhs ) = delete;
    EventListener(EventListener&& other){
        listenerId = other.listenerId;
        ae = other.ae;
        other.ae = nullptr;
    }
    EventListener& operator=( EventListener&& rhs ) {
        if (this != &rhs){
            destroyListener();
            listenerId = rhs.listenerId;
            ae = rhs.ae;
            rhs.ae = nullptr;
        }
        return *this;
    };
    friend class Event<E>;
};

template <typename E>
class SyncValue : public AbstractEventListener {
public:
    SyncValue(){

    }

    E& getValue(){
        return value;
    }

    SyncValue(const SyncValue&) = delete;
    SyncValue& operator=( const SyncValue& rhs ) = delete;

    SyncValue(SyncValue&& other){
        listenerId = other.listenerId;
        ae = other.ae;
        value = std::move(other.value);
        other.ae = nullptr;
    }
    SyncValue& operator=( SyncValue&& rhs ) {
        if (this != &rhs){
            destroyListener();
            listenerId = rhs.listenerId;
            ae = rhs.ae;
            value = std::move(rhs.value);
            rhs.ae = nullptr;
        }
        return *this;
    };

    friend class Event<E>;
private:
    E value;
};
