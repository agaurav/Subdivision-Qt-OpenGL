#ifndef WING_H
#define WING_H
#include "triangle.h"

class Triangle;

class Wing{

public:
    Wing(int);
    int getId();
    Triangle* getNext();
    void setNext(Triangle*);
    bool hasNext();
    void resetHasNext();
    Triangle* getFace();
    void setFace(Triangle*);
    void reset();


    int id;
private:

    bool hasnext;
    Triangle* next;
    Triangle* face;
};




#endif
