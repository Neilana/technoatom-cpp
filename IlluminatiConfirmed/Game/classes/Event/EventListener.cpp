//
//  EventListener.cpp
//
//  Created by Morten Nobel-Jørgensen on 8/18/13.
//  Copyright (c) 2013 morten. All rights reserved.
//  Open Source under New BSD License (http://opensource.org/licenses/BSD-3-Clause)

#include "EventListener.h"
#include "Event.h"

AbstractEventListener::AbstractEventListener(AbstractEvent *ae, int listenerId)
:ae(ae), listenerId(listenerId){

}

AbstractEventListener::~AbstractEventListener(){
    destroyListener();
}

void AbstractEventListener::destroyListener(){
    if (ae){
        ae->removeListener(listenerId);
    }
}
