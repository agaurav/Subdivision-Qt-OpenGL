#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include "mesh.h"
#include <sstream>
#include <fstream>
#include <string>



class Model{

public:
    Model();
    Model(ofVec3f, int, int, const char*);
    void updateMeshes(unsigned int );
    void updateMeshScaling(ofVec3f );
    void setCurrentMesh(unsigned int i);
    Mesh* getStateMesh(int );
    Mesh* getCurrentMesh( );
    Mesh* getAndSetCurrentMesh();
    Mesh* getOriginalMesh();
    Mesh* getLimitMesh();
    Mesh* loadObj();
    Mesh* loadMesh();
    Mesh* loadMeshOpenCube();
    Mesh* loadMeshCube();
    Mesh* loadMeshPyramid();
    Mesh* loadMeshStar();
    void adjustVertex(int , int , ofVec3f );
    //void printChanges();
    int getCurrentMeshLevel();
    double getBoxSize();
    bool hasFile();
    ofVec3f getMinPoint();
    void setScaleX(float f);
    void setScaleY(float f);
    void setScaleZ(float f);
    void applyMirroring(vector<int> );
    void changeVeretexState(int state);
private:
    int getStageFace(int stage, vector<int> faces);

    vector<Mesh*> meshes;
    map<int, map<int, int> > face_changes; //map: stage_id -> ( map : face_id -> delta_id) //this is just used for searching
    map<int, map<int, int> > vertex_changes; //map: stage_id -> ( map : vertex_id -> delta_id) //this is just used for searching

    map<int, vector<int> > changed_order; //map: stage_id -> (vector < delta ids> )

    ofVec3f scale;

    int current;
    int depth;
    int limit_depth;
    const char* filename;
    int hasfile;
};


#endif

