
#ifndef TRIANGLE_H
#define TRIANGLE_H

using namespace std;

#include "wing.h"
#include "ofVec3f.h"
#include <set>
#include <vector>
#include <assert.h>

class Wing;

typedef int PICKSTATE;
#define OFF 0
#define OVER 1
#define ON 2

class Triangle{

public:
    Triangle(int, int, int, int);
    ofVec3f getColor();
    bool hasEdge(int , int );
    bool hasVertex(int );
    Wing* getA();
    Wing* getB();
    Wing* getC();
    void setA(Wing*);
    void setB(Wing*);
    void setC(Wing*);
    void setANext(Triangle*);
    void setBNext(Triangle*);
    void setCNext(Triangle*);
    Wing* getFaceVertexId(int );
    int getId();
    bool isDivided();
    void markDivided();
    void setDivided(bool);
    vector<Triangle*> getNewFacesOnEdge(int, int);
    void setNewFaces(Triangle*, Triangle*, Triangle*);
    int getVertexOnEdgeId(int , int );
    Wing* getOtherVertex(int, int);
    Wing* cwNeighbor(int);
    Wing* ccwNeighbor(int);
    void setFaceNormal(ofVec3f);
    ofVec3f getFaceNormal();
    void setId(int );
    PICKSTATE getState();
    void setState(PICKSTATE);
    void resetFaceVertexNexts();
    void printData();

private:
    int id;
    Wing* a; //oriented counter clockwise
    Wing* b;
    Wing* c;
    ofVec3f color;
    ofVec3f n;
    bool divided;
    PICKSTATE ps;


};


#endif
