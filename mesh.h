


#ifndef MESH_H
#define MESH_H


#include "vertex.h"
#include "triangle.h"
#include "wing.h"
#include "ofVec3f.h"
#include <vector>
#include <set>
#include <stack>
#include <map>

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

using namespace std;


#ifndef TWO_PI
    #define TWO_PI   6.28318530717958647693
    #endif

typedef ofVec3f BoundingBox3f;




class Mesh{

public:

    Mesh(int s, vector<Vertex*> v, vector<Triangle*> f);
    Mesh(int, Mesh* old);
    map<int, Triangle*> getFaces();
    vector<Vertex*> getVList();
    void subdivide();
    void addNewFaces(Triangle*, int, int, int, int, int, int);
    void deleteOldFaces();
    void subdivideNeighbor(Triangle*);
    int  getVertexOnEdgeId(int , int );
    void connectEdgeFaces(Triangle* , Triangle* , int , int , int );
    Vertex* getOrMakeVertex(Triangle*, Wing* , Wing* );
    void udpateMeshData();
    ofVec3f loopEdgeValue(Triangle* f, Wing* A, Wing* B, Vertex* v);
    ofVec3f computeFaceNormal(Triangle* f);

    void resetVariables();
    ofVec3f getBoxMin();
    ofVec3f getBoxMax();
    double getBoxSize();
    void updateMins(ofVec3f& m, ofVec3f c);
    void updateMaxs(ofVec3f& m, ofVec3f c);
    void applyScaling(ofVec3f);
    void createWing();
    void addSubMesh(int child, int p1, int p2);
    void linkChildren();
    void updateMeshData();
    vector<Vertex*> vList; //all vertexes from
    map<int, Triangle*> faces;

private:


    int stage;

    map<int, Triangle*> new_faces;
    stack<Triangle*> to_check;
    float weight;
    ofVec3f box_min;
    ofVec3f box_max;
    map<int, int> twin_vertices; //<a map from the orignial vertex to it's mirror vertex >>
    map< int, map <int, int> > lineage;

};

#endif
