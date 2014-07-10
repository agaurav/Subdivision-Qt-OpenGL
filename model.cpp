
#include "model.h"

/*this class is in charge of handling all of the different meshes, scaling and updating them as needed */

Model::Model(){
    //cout << "I SHOULDN'T BE CALLED!" << endl;
}

Model :: Model(ofVec3f s, int d, int hf, const char* fname){
    hasfile = 0;
    if(hf == 4)
    {hasfile = 1;}

    current = 0;
    depth = d;
    limit_depth = 5;
    filename = fname;
    scale.set(1.,1.,1.);



    switch (hf) {
    case 0:
        meshes.push_back(loadMeshCube());
        break;
    case 1:
        meshes.push_back(loadMeshOpenCube());
        break;
    case 2:
        meshes.push_back(loadMeshPyramid());
        break;
    case 3:
        meshes.push_back(loadMeshStar());
        break;
    case 4:
        meshes.push_back(loadObj());
        break;
    default:
        break;
    }


    for(int i = 1; i < depth; i++) meshes.push_back(new Mesh(i, meshes.back()));



}

Mesh* Model::loadMeshCube(){

    //read in each vertex into a list
    vector<Vertex*> vlist;
    vlist.push_back(new Vertex(0, -50, -50, 50));
    vlist.push_back(new Vertex(1, 50, -50, 50));
    vlist.push_back(new Vertex(2, 50, -50, -50));
    vlist.push_back(new Vertex(3, -50, -50, -50));
    vlist.push_back(new Vertex(4, -50, 50, 50));
    vlist.push_back(new Vertex(5, 50, 50, 50));
    vlist.push_back(new Vertex(6, 50, 50, -50));
    vlist.push_back(new Vertex(7, -50, 50, -50));
    vlist[0]->setState(LOOSE);
    vlist[1]->setState(LOOSE);
    vlist[2]->setState(FIXED);
    vlist[3]->setState(FIXED);
    vector<Triangle*> faces;
    //the faces are always going to be one index higher when they are first entered
    faces.push_back(new Triangle(0, 0, 2, 3));
    faces.push_back(new Triangle(1, 1, 2, 0));
    faces.push_back(new Triangle(2, 3, 7, 0));
    faces.push_back(new Triangle(3, 0, 7, 4));
    faces.push_back(new Triangle(4, 3, 6, 7));
    faces.push_back(new Triangle(5, 2, 6, 3));
    faces.push_back(new Triangle(6, 1, 6, 2));
    faces.push_back(new Triangle(7, 1, 5, 6));
    faces.push_back(new Triangle(8, 6, 4, 7));
    faces.push_back(new Triangle(9,6, 5, 4));
    faces.push_back(new Triangle(10,5, 0, 4));
    faces.push_back(new Triangle(11, 5, 1, 0));


    for(vector<Vertex*> :: iterator it = vlist.begin(); it != vlist.end(); it++){
        ofVec3f p = (*it)->getPoint();
        p *= scale;
        (*it)->setPoint(p);
    }


    return new Mesh(0, vlist, faces);

}


Mesh* Model::loadMeshOpenCube(){

    //read in each vertex into a list
    vector<Vertex*> vlist;
    vlist.push_back(new Vertex(0, -50, -50, 50));
    vlist.push_back(new Vertex(1, 50, -50, 50));
    vlist.push_back(new Vertex(2, 50, -50, -50));
    vlist.push_back(new Vertex(3, -50, -50, -50));
    vlist.push_back(new Vertex(4, -50, 50, 50));
    vlist.push_back(new Vertex(5, 50, 50, 50));
    vlist.push_back(new Vertex(6, 50, 50, -50));
    vlist.push_back(new Vertex(7, -50, 50, -50));

    vector<Triangle*> faces;
    //the faces are always going to be one index higher when they are first entered
    faces.push_back(new Triangle(0, 0, 2, 3));
    faces.push_back(new Triangle(1, 1, 2, 0));
    faces.push_back(new Triangle(2, 3, 7, 0));
    faces.push_back(new Triangle(3, 0, 7, 4));
    faces.push_back(new Triangle(4, 3, 6, 7));
    faces.push_back(new Triangle(5, 2, 6, 3));
    faces.push_back(new Triangle(6, 1, 6, 2));
    faces.push_back(new Triangle(7, 1, 5, 6));
    //faces.push_back(new Face(8, 6, 4, 7));
    //faces.push_back(new Face(9,6, 5, 4));
    faces.push_back(new Triangle(10,5, 0, 4));
    faces.push_back(new Triangle(11, 5, 1, 0));


    for(vector<Vertex*> :: iterator it = vlist.begin(); it != vlist.end(); it++){
        ofVec3f p = (*it)->getPoint();
        p *= scale;
        (*it)->setPoint(p);
    }


    return new Mesh(0, vlist, faces);

}



Mesh* Model::loadMeshPyramid(){

    //read in each vertex into a list
    vector<Vertex*> vlist;
    vlist.push_back(new Vertex(0, 0, 30, 0));
    vlist.push_back(new Vertex(1, -50, -50, 50));
    vlist.push_back(new Vertex(2, 50, -50, 50));
    vlist.push_back(new Vertex(3, 50, -50, -50));
    vlist.push_back(new Vertex(4, -50, -50, -50));

    vector<Triangle*> faces;
    //the faces are always going to be one index higher when they are first entered
    faces.push_back(new Triangle(0, 0, 1, 2));
    faces.push_back(new Triangle(1, 2, 3,0));
    faces.push_back(new Triangle(2, 3, 4,0));
    faces.push_back(new Triangle(3, 4, 5,0));
    faces.push_back(new Triangle(4,3, 4,2));
    faces.push_back(new Triangle(5, 4, 5, 2));


    for(vector<Vertex*> :: iterator it = vlist.begin(); it != vlist.end(); it++){
        ofVec3f p = (*it)->getPoint();
        p *= scale;
        (*it)->setPoint(p);
    }


    return new Mesh(0, vlist, faces );

}



Mesh* Model::loadMeshStar(){

    //read in each vertex into a list
    vector<Vertex*> vlist;
    vlist.push_back(new Vertex(0, -50, -50, 50));
    vlist.push_back(new Vertex(1, 50, -50, 50));
    vlist.push_back(new Vertex(2, 50, -50, -50));
    vlist.push_back(new Vertex(3, -50, -50, -50));
    vlist.push_back(new Vertex(4, -50, 50, 50));
    vlist.push_back(new Vertex(5, 50, 50, 50));
    vlist.push_back(new Vertex(6, 50, 50, -50));
    vlist.push_back(new Vertex(7, -50, 50, -50));

    vector<Triangle*> faces;
    //the faces are always going to be one index higher when they are first entered
    //faces.push_back(new Face(0, 0, 2, 3));
    //faces.push_back(new Face(1, 1, 2, 0));
    faces.push_back(new Triangle(2, 3, 7, 0));
    faces.push_back(new Triangle(3, 0, 7, 4));
    faces.push_back(new Triangle(4, 3, 6, 7));
    faces.push_back(new Triangle(5, 2, 6, 3));
    faces.push_back(new Triangle(6, 1, 6, 2));
    faces.push_back(new Triangle(7, 1, 5, 6));
    faces.push_back(new Triangle(8, 6, 4, 7));
    faces.push_back(new Triangle(9,6, 5, 4));
    faces.push_back(new Triangle(10,5, 0, 4));
    faces.push_back(new Triangle(11, 5, 1, 0));


    for(vector<Vertex*> :: iterator it = vlist.begin(); it != vlist.end(); it++){
        ofVec3f p = (*it)->getPoint();
        p *= scale;
        (*it)->setPoint(p);
    }


    return new Mesh(0, vlist, faces );

}

Mesh* Model::loadObj(){
    vector<Vertex*> vlist;
    vector<Triangle*> faces;

    int size;
    string in, type, data, remaining;
    size_t space, slash;


    //cout << "Loading Shape File: " << filename << endl;
    ifstream myfile(filename);

    if(myfile.is_open()){
        //cout << "File is open " << endl;
        while(myfile.good()){
            getline (myfile,in);

            space = in.find(" ");
            type = in.substr(0, space);

            remaining = in.substr(space+1);


            if(type.compare("v") == 0){
                //get the next three int

                space = remaining.find(" ");
                float x = atof((remaining.substr(0, space)).data());
                remaining = remaining.substr(space+1);

                space = remaining.find(" ");
                float y = atof((remaining.substr(0, space)).data());
                remaining = remaining.substr(space+1);

                space = remaining.find(" ");
                float z = atof((remaining.substr(0, space)).data());
                remaining = remaining.substr(space+1);

                vlist.push_back(new Vertex(vlist.size(), x*scale.x, y*1.5*scale.y, z*scale.z));
            }


            if(type.compare("f") == 0){
                //get the next three int

                space = remaining.find(" ");
                data = remaining.substr(0, space); //contains faces and slashes
                slash = remaining.find("/");
                int f1 = atoi((remaining.substr(0, slash)).data());
                remaining = remaining.substr(space+1);

                space = remaining.find(" ");
                data = remaining.substr(0, space); //contains faces and slashes
                slash = remaining.find("/");
                int f2 = atoi((remaining.substr(0, slash)).data());
                remaining = remaining.substr(space+1);

                space = remaining.find(" ");
                data = remaining.substr(0, space); //contains faces and slashes
                slash = remaining.find("/");
                int f3 = atoi((remaining.substr(0, slash)).data());
                remaining = remaining.substr(space+1);

                faces.push_back(new Triangle(faces.size(), f1-1, f2-1, f3-1));
            }

        }
    }

    cout << "Num Vertices " <<vlist.size() << endl;
    cout << "Num Faces" << faces.size() << endl;


    return new Mesh(0,vlist, faces );

}



//this updates and recalculates all meshes - called in scaling
void Model::updateMeshScaling(ofVec3f oldScale){

    for(int i = 0; i < meshes.size(); i++){
        if(i == 0 ){
            meshes[0]->applyScaling(scale/oldScale);


        }else{
            Mesh* prev = meshes[i-1];
            prev->resetVariables();
            meshes[i] = new Mesh(i, prev);
        }

    }


}


//does not recalculate any mesh before or at the current stage
void Model::updateMeshes(unsigned int stage){

    int num_meshes = meshes.size();
    vector<Vertex*> cVlist;
    cVlist= getCurrentMesh()->getVList();
    vector<Vertex*> vtxList;

    for (int m = 0; m < current; ++m) {
    vtxList = getStateMesh(m)->getVList();
    int j = 0;
    for(vector<Vertex*> :: iterator it = vtxList.begin(); it != vtxList.end(); it++){
        vtxList[j]->setState(cVlist[j]->getState());
        j++;
    }

    }

    for(int i = stage+1; i < num_meshes; i++){
        Mesh* prev = meshes[i-1];
        prev->resetVariables();
        meshes[i] = new Mesh(i, prev);
    }




}

void Model::setCurrentMesh(unsigned int i){
    current = i;


    if(current == meshes.size()){
        meshes.push_back(new Mesh(meshes.size()+1, meshes.back()));
    }else if(current > limit_depth && current <= meshes.size()){
        meshes.erase(meshes.begin()+current, meshes.end());
    }

    depth = meshes.size();
}

Mesh* Model::getStateMesh(int i){
    return meshes[i];
}

Mesh* Model::getCurrentMesh(){
    return meshes[current];
}

int Model::getCurrentMeshLevel(){
    return current;
}

Mesh* Model::getLimitMesh(){
    return meshes.back();
}

Mesh* Model::getOriginalMesh(){
    return meshes.front();
}



//returns the face from this set of faces that the delta change is indexed to
//returns -1 if none of those faces were indexed
int Model::getStageFace(int stage, vector<int> faces){
    for(vector<int> :: iterator it = faces.begin(); it != faces.end(); it++){
        if(face_changes[stage].count(*it)) return *it;
    }
    return -1;
}






double Model::getBoxSize(){
    return meshes[0]->getBoxSize();
}


bool Model::hasFile(){
    return hasfile;
}

ofVec3f Model::getMinPoint(){
    return meshes[0]->getBoxMin();
}


void Model::setScaleX(float f){
    ofVec3f oldScale;
    oldScale.set(scale);
    scale.x = f;

    cout << "Old Scale " << oldScale.x << " " << oldScale.y << " " << oldScale.z <<  endl;
    cout << "New Scale " << scale.x << " " << scale.y << " " << scale.z <<  endl;
    updateMeshScaling(oldScale);
}

void Model::setScaleY(float f){

    ofVec3f oldScale;
    oldScale.set(scale);
    scale.y = f;
    updateMeshScaling(oldScale);

}

void Model::setScaleZ(float f){

    ofVec3f oldScale;
    oldScale.set(scale);
    scale.z = f;
    updateMeshScaling(oldScale);
}






