
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGui>
#include <QGLWidget>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "triangle.h"
#include "wing.h"
#include "vertex.h"
#include "mesh.h"
#include "model.h"
#include "ofVec3f.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <set>
#include <map>



class QGLShaderProgram;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0, QGLWidget *shareWidget = 0);
    ~GLWidget();
    bool isWireframe;
    bool showVertices = true;
    bool showEdges = true;
    bool showVID =true;
    bool reverseNormal =false;
    float lineWidth = 2.0;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void rotateBy(int xAngle, int yAngle, int zAngle);
    void setClearColor(const QColor &color);
    void setSubDivLvl(int s);
    Model* mm;
    unsigned int draw_subdivision;
    GLfloat g_fViewDistance= 550.0;
    GLfloat g_fFarPlane = 1.0;
    GLfloat g_fNearPlane = 10000.0;
    ofVec3f eye;
    GLfloat g_xz_theta = 0;
    GLfloat g_yz_theta = 0;
    int vCount;
    int fCount;
    QColor clearColor;
    QPoint lastPos;
    float pickTargetSize;
    void toggleWireFrame();
    void toggleShowVertices();
    void setReverseNormal(bool val);
    void toggleShowEdges();
    void setLineWidth(int val);
    void setMeshScale(float scale);
    void setRotate(float x,float y,float z);
    void setTranslate(float x,float y,float z);

    void loadNewMesh(const char* filename,int objFlag);
    void setVertexState(int vID,int state);
    int getVertexState(int vID);
    void showVertexId(int vid);
    ofVec3f rotate;
    ofVec3f translate;

signals:
    void clicked();


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void render_current_mesh();
    void enable_lights();
    void pick(int x, int y, PICKSTATE state);
    void change_pick_vertices(GLint hits, GLuint *names, PICKSTATE state);
    void render_pick_vertices();
    void render_vertex_selections();
    void select_twins(int i, PICKSTATE ps);
    void render_crease(int vid, float lineLen);
    void highlightCurrentVertex();
    ofVec3f min;
    double size;
    int currentVertex ;
private:
    void makeObject();

    int xRot;
    int yRot;
    int zRot;
    GLuint textures[6];
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
#ifdef QT_OPENGL_ES_2
    QGLShaderProgram *program;
#endif
};

#endif
