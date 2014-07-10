#ifndef WING
#define WING

#include "wing.h"


Wing :: Wing(int i){
    id = i;
    hasnext = false;
}

void Wing::resetHasNext(){
    hasnext = false;
}

Triangle* Wing::getNext(){
    return next;
}

void Wing::setNext(Triangle* f){
    next = f;
    hasnext = true;
}

int Wing::getId(){
    return id;
}

void Wing::reset(){
    hasnext = false;
}

bool Wing::hasNext(){
    return hasnext;
}

Triangle* Wing::getFace(){
    return face;
}

void Wing::setFace(Triangle* f){
    face = f;
}



#endif
