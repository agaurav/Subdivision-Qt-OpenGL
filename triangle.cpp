/*
 *  face.cpp
 *
 *
 */

#include "triangle.h"


//v1, v2, v3 are oriented counter clockwise
Triangle :: Triangle(int i, int v1, int v2, int v3){
    id = i;
    color = ofVec3f((i*344587%255)/255., (i*4573%255)/255., (i*2937584%255)/255);
    a = new Wing(v1);
    b = new Wing(v2);
    c = new Wing(v3);

    divided = false;
    ps = OFF;

}

void Triangle::setId(int i){
    id = i;
}

void Triangle::printData(){

    cout << "Face Id: " << id << " is [" << a->id << ", " << b->id << ", " << c->id << "] divided? = " << divided << endl;
    if(!divided){
        cout << "A.next =  " << a->getNext()->getId() << endl;
        cout << "B.next =  " << b->getNext()->getId() << endl;
        cout << "C.next =  " << c->getNext()->getId() << endl;
    }else {
        cout << "A.next =  " << a->getNext()->getId() << " A.face = " << a->getFace()->getId() << endl;
        cout << "B.next =  " << b->getNext()->getId() << " B.face = " << b->getFace()->getId() << endl;
        cout << "C.next =  " << c->getNext()->getId() << " C.face = " << c->getFace()->getId() << endl;

    }

}


ofVec3f Triangle::getColor(){
    return color;
}

Wing* Triangle::getA(){
    return a;
}

Wing* Triangle::getB(){
    return b;
}

Wing* Triangle::getC(){
    return c;
}


void Triangle::setA(Wing* fv){
    a = fv;
}

void Triangle::setB(Wing* fv){
    b = fv;
}

void Triangle::setC(Wing* fv){
    c = fv;
}

void Triangle::resetFaceVertexNexts(){
    a->resetHasNext();
    b->resetHasNext();
    c->resetHasNext();
}

void Triangle::setANext(Triangle* f){
    a->setNext(f);
}

void Triangle::setBNext(Triangle* f){
    b->setNext(f);
}

void Triangle::setCNext(Triangle* f){
    c->setNext(f);
}

Wing* Triangle::getFaceVertexId(int id){

    if(a->id == id) return a;
    if(b->id == id) return b;
    if(c->id == id) return c;
    assert(0);
}

//returns the existance of an edge - doesn't check order
bool Triangle::hasEdge(int x, int y){
    int num_found = 0;
    if(a->id == x || b->id == x || c->id == x) num_found++;
    if(a->id == y || b->id == y || c->id == y) num_found++;
    return (num_found == 2);
}

bool Triangle::hasVertex(int x){
    return (a->id == x || b->id == x || c->id == x);
}


int Triangle::getId(){
    return id;
}

bool Triangle::isDivided(){
    return divided;
}

void Triangle::setDivided(bool d){
    divided = d;
}

void Triangle::setNewFaces(Triangle* A, Triangle* B, Triangle* C){
    divided = true;
    a->setFace(A);
    b->setFace(B);
    c->setFace(C);
}

//given two vertices of a triangle, return the third
Wing* Triangle::getOtherVertex(int x, int y){
    if(a->id != x && a->id != y ) return a;
    if(b->id != x && b->id != y ) return b;
    if(c->id != x && c->id != y ) return c;
    assert(0);

}

Wing* Triangle::ccwNeighbor(int x){
    if(a->id == x) return b;
    if(b->id == x) return c;
    if(c->id == x) return a;
    assert(0);

}


Wing* Triangle::cwNeighbor(int x){

    if(a->id == x) return c;
    if(b->id == x) return a;
    if(c->id == x) return b;
    assert(0);

}

//takes two vertexes and returns their common vertex id;
int Triangle::getVertexOnEdgeId(int from, int to){
    vector<Triangle*> fs;

    //get the trianlges on the end vertices
    fs.push_back(getFaceVertexId(from)->getFace());
    fs.push_back(getFaceVertexId(to)->getFace());

    //return the vertex that they have in common
    if(fs[0]->hasVertex(fs[1]->getA()->id)) return fs[1]->getA()->id;
    if(fs[0]->hasVertex(fs[1]->getB()->id)) return fs[1]->getB()->id;
    if(fs[0]->hasVertex(fs[1]->getC()->id)) return fs[1]->getC()->id;

    assert(0);
}

void Triangle::setFaceNormal(ofVec3f normal){
    //normal *= -1;
    n.set(normal);
}

ofVec3f Triangle::getFaceNormal(){
    return n;
}

PICKSTATE Triangle::getState(){
    return ps;
}

void Triangle::setState(PICKSTATE s){
    ps = s;
}


