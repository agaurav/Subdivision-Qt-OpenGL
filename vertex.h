#ifndef VERTEX_H
#define VERTEX_H

#include <set>
#include "ofVec3f.h"
#include "triangle.h"

typedef int PICKSTATE;
#define FREE 0
#define LOOSE 1
#define FIXED 2

class Vertex{

public:
    Vertex(int, float, float, float);
    Vertex(Vertex* );
    ofVec3f getColor();
    ofVec3f getPoint();
    void setPoint(ofVec3f);
    void setFace(Triangle* );
    Triangle* getFace();
    void addIncidentEdge();
    int getIncident();
    void setIncidentEdge(int );
    float getX();
    int getId();
    void setState(PICKSTATE s);
    PICKSTATE getState();
    void offset(ofVec3f );
    void setNormal(ofVec3f );
    ofVec3f getNormal();
    ofVec3f getOriginalPoint();
    ofVec3f  getComponentX();
    ofVec3f  getComponentY();
    void setComponents();
    void incrementIncident();
    void addComponentNormal(ofVec3f);
    void makeNormalAverage();




private:
    int id;
    int incident_edges;
    Triangle* face;
    ofVec3f p;
    ofVec3f p_offset;
    ofVec3f c;
    ofVec3f normal;
    ofVec3f comp_x;
    ofVec3f comp_y;
    PICKSTATE ps;


};


#endif

