
#include <QtGui>
#include <QtOpenGL>
#include <QString>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, QGLWidget *shareWidget)
    : QGLWidget(parent, shareWidget)
{


    ofVec3f scale(1,1,1);
    mm = new Model(scale, 5, 1, "torus_tri.obj");
    min = mm->getMinPoint();
    size = mm->getBoxSize();
    clearColor = Qt::black;
    this->setClearColor(clearColor);
    xRot = 0;
    yRot = 0;
    zRot = 0;
    vCount = mm->getCurrentMesh()->vList.size();
    fCount = mm->getCurrentMesh()->faces.size();
    //    g_xz_theta = 3*PI/2.;
    //    g_yz_theta = PI/2.;
    g_xz_theta = 0;
    g_yz_theta = PI/2.;
    rotate.set(0.0,0.0,0.0);
    translate.set(0.0,0.0,0.0);
    min = mm->getMinPoint();
    size = mm->getBoxSize();
    if(min.z > 0 )
        g_fViewDistance = size*2 + min.z;
    else
        g_fViewDistance = size*2 +(0-min.z);
    g_fNearPlane = 0.1;
    g_fFarPlane = 10*size*size;
    pickTargetSize = size / 100;
    eye.set(g_fViewDistance*cos(g_xz_theta), g_fViewDistance*sin(g_yz_theta), g_fViewDistance*sin(g_xz_theta));
    currentVertex =0;

}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(1200, 950);
}

QSize GLWidget::sizeHint() const
{
    return QSize(1200, 950);
}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    updateGL();
}

void GLWidget::setClearColor(const QColor &color)
{
    clearColor = Qt::black;
    updateGL();
}

void GLWidget::initializeGL()
{
    //makeObject();

    glEnable(GL_DEPTH_TEST);
    //  glEnable(GL_CULL_FACE);

    glEnable( GL_POLYGON_SMOOTH );
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

}

void GLWidget::paintGL()
{

    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    glOrtho(-1.0, +1.0, +1.0, -1.0, 0.10, 1000.0);
    //    qglClearColor(clearColor);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glMatrixMode(GL_MODELVIEW);
    //    glClearColor (1.0, 1.0, 1.0, 0.0);
    //    glLineWidth(2.);
    //    glEnable (GL_BLEND);
    //    glLoadIdentity();
    //    glPushMatrix();
    //    glScalef(0.005f,0.005f,0.005f);
    //    glTranslatef(0.0f, 0.0f, -400.0f);
    //    glRotatef(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    //    glRotatef(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    //    glRotatef(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
    //    render_current_mesh();
    //    glPopMatrix();

    vCount = mm->getCurrentMesh()->vList.size();
    fCount = mm->getCurrentMesh()->faces.size();
    eye.set(g_fViewDistance*cos(g_xz_theta), g_fViewDistance*sin(g_yz_theta), g_fViewDistance*sin(g_xz_theta));
    GLint view[4];
    glGetIntegerv(GL_VIEWPORT, view);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)view[2]/(float)view[3], g_fNearPlane, g_fFarPlane);
    glMatrixMode(GL_MODELVIEW);
    //    double size = mm->getBoxSize();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set up viewing transformation, looking down -Z axis
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glClearColor (0.0,0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glLineWidth(lineWidth);

    gluLookAt(eye.x, eye.y, eye.z, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
    glRotatef(rotate.x,1.0,0.0,0.0);
    glRotatef(rotate.y,0.0,1.0,0.0);
    glRotatef(rotate.z,0.0,0.0,1.0);
    glTranslatef(translate.x,translate.y,translate.z);
//enable_lights();
    //enable_lights();
    render_current_mesh();
    if(showVertices && vCount < 100)render_vertex_selections();
    else highlightCurrentVertex();
    // render_pick_vertices();
    glPopMatrix();

}

void GLWidget::render_current_mesh()
{
    map<int, Triangle*> faces = mm->getCurrentMesh()->getFaces();
    vector<Vertex*> vList = mm->getCurrentMesh()->getVList();
    map<int, Triangle*> :: iterator it;

    for(it = faces.begin(); it != faces.end(); it++){
        Triangle* x = (*it).second;
        ofVec3f c = x->getColor();

        ofVec3f A = vList[x->getA()->id]->getPoint();
        ofVec3f B = vList[x->getB()->id]->getPoint();
        ofVec3f C = vList[x->getC()->id]->getPoint();
        ofVec3f n = x->getFaceNormal();
        if(reverseNormal) n = -n;
  //      enable_lights();

        glColor4f(1., 0.647, 0.2, 0.0);
        enable_lights();
        if(!isWireframe){

            glBegin(GL_TRIANGLES);

            glNormal3f(-n.x,-n.y, -n.z);
            glVertex3f(C.x, C.y, C.z);
            glNormal3f(-n.x,-n.y, -n.z);
            glVertex3f(A.x, A.y, A.z);

            glNormal3f(-n.x,-n.y, -n.z);
            glVertex3f(B.x, B.y, B.z);
            glEnd();
        }



        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.2, 0.8, 0.0, .5);
        if(showEdges){

            glBegin(GL_LINE_LOOP);
            glVertex3f(A.x, A.y, A.z);
            glVertex3f(B.x, B.y, B.z);
            glVertex3f(C.x, C.y, C.z);
            glEnd();}
        glDisable(GL_BLEND);

    }
}
/*
void GLWidget::enable_lights(){
    glEnable(GL_LIGHTING);

    //glEnable(GL_COLOR_MATERIAL);
    GLfloat mat_specular[] = { 0.6, 0.4, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.5, 0.1, 1.0 };
    GLfloat mat_diff[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_shininess[] = { 32.0 };
    GLfloat light_position1[] = { 0.8, 0.4, 0.2, 1.0 };
    GLfloat light_position2[] = { 0.8, 0.4, 0.1, 1.0 };
    GLfloat light_position3[] = { 1.0, 0.6, 0.3, 1.0 };
    GLfloat light_position4[] = { 1.0, 0.6, 0.7, 1.0 };
    GLfloat light_position[] = { eye.x,eye.y, eye.z, 1.0 };
    GLfloat light_positionN[] = { -eye.x,-eye.y, -eye.z, 1.0 };
    GLfloat light_positionY[] = { .0,1.0, 0.0, 0.0 };
    GLfloat light_positionXY[] = { -1.0,0.0, 0.0, 0.0 };

    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_BACK ,GL_AMBIENT, mat_ambient);
   //glMaterialfv(GL_BACK, GL_DIFFUSE, mat_diff);
     glMaterialfv(GL_BACK, GL_SHININESS, mat_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_position3);
     glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    //glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_position4);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_position3);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_position1);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_position1);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_positionN);
    glLightfv(GL_LIGHT4, GL_SPECULAR, light_position2);
    glLightfv(GL_LIGHT4, GL_POSITION, light_positionN);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light_positionXY);
    glLightfv(GL_LIGHT5, GL_SPECULAR, light_position4);
    //glLightfv(GL_LIGHT5, GL_POSITION, light_positionY);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light_positionY);


    //glLightfv();


glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_DEPTH_TEST);
  //  glEnable(GL_BLEND);

}
*/



void GLWidget::enable_lights(){
    glEnable(GL_LIGHTING);

    //glEnable(GL_COLOR_MATERIAL);
    GLfloat mat_specular[] = { 0.6, 0.4, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.5, 0.1, 1.0 };
    GLfloat mat_diff[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_shininess[] = { 32.0 };
    GLfloat light_position1[] = { 0.8, 0.4, 0.2, 1.0 };
    GLfloat light_position2[] = { 0.8, 0.4, 0.1, 1.0 };
    GLfloat light_position3[] = { 1.0, 0.6, 0.3, 1.0 };
    GLfloat light_position4[] = { 1.0, 0.6, 0.7, 1.0 };
    GLfloat light_position[] = { eye.x,eye.y, eye.z, 1.0 };
    GLfloat light_positionN[] = { -eye.x,-eye.y, -eye.z, 1.0 };
    GLfloat light_positionY[] = { .0,1.0, 0.0, 0.0 };
    GLfloat light_positionXY[] = { -1.0,0.0, 0.0, 0.0 };

    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);

    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_position3);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_position4);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_position3);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_position1);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_position1);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_positionN);
    glLightfv(GL_LIGHT4, GL_SPECULAR, light_position2);
    glLightfv(GL_LIGHT4, GL_POSITION, light_positionN);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light_positionXY);
    glLightfv(GL_LIGHT5, GL_SPECULAR, light_position4);
    glLightfv(GL_LIGHT5, GL_POSITION, light_position);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light_positionY);


    //glLightfv();


    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

}
void GLWidget::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
    glViewport(0,0 ,width, height);
    eye.set(g_fViewDistance*cos(g_xz_theta), g_fViewDistance*sin(g_yz_theta), g_fViewDistance*sin(g_xz_theta));
    GLint view[4];

    glGetIntegerv(GL_VIEWPORT, view);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)view[2]/(float)view[3], g_fNearPlane, g_fFarPlane);
    glMatrixMode(GL_MODELVIEW);

}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        //rotateBy(8 * dy, 8 * dx, 0);
        g_xz_theta += dx * 0.1;
        g_yz_theta += dy * 0.1;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        //rotateBy(8 * dy, 0, 8 * dx);
        g_fViewDistance += dy;
        updateGL();
    }

    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void GLWidget::setSubDivLvl(int s)
{
    mm->setCurrentMesh(s);
    updateGL();
}

void GLWidget::makeObject()
{
    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

    for (int j=0; j < 6; ++j) {
        textures[j] = bindTexture
                (QPixmap(QString(":/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);
    }

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            texCoords.append
                    (QVector2D(j == 0 || j == 3, j == 0 || j == 1));
            vertices.append
                    (QVector3D(0.2 * coords[i][j][0], 0.2 * coords[i][j][1],
                    0.2 * coords[i][j][2]));
        }
    }
}




void GLWidget::render_pick_vertices(){

    vector<Vertex*> vList = mm->getCurrentMesh()->getVList();

    for(vector<Vertex*> :: iterator it = vList.begin(); it != vList.end(); it++){
        ofVec3f A = (*it)->getPoint();
        ofVec3f n = (*it)->getNormal();
        glLoadName((*it)->getId());
        glPushMatrix();
        glTranslatef(A.x, A.y, A.z);
        glutSolidCube(pickTargetSize);
        glPopMatrix();
    }
}
void GLWidget::render_vertex_selections(){
    vector<Vertex*> vList = mm->getCurrentMesh()->getVList();
    glDisable(GL_BLEND);
    for(vector<Vertex*> :: iterator it = vList.begin(); it != vList.end(); it++){
        Vertex* v = *it;

        ofVec3f A = v->getPoint();
        ofVec3f z(0.0,0.0,1.0);
        ofVec3f n = v->getNormal();
        ofVec3f axis = n.getPerpendicular(z);

        GLfloat rot = n.angle(z);
        QString id = QString::number(v->getId());
        char c;

        glPushMatrix();


        glTranslatef(A.x, A.y, A.z);
        glRotatef(-rot,axis.x, axis.y,axis.z);
        //glTranslatef(n.x, n.y, n.z);


        glEnable (GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        switch (v->getState()) {
        case FREE:
            glColor4f(1., 1., 1., 1.);
            break;
        case LOOSE:
            glColor4f( 0.0,0.0, 1.0, 1.0);
            break;
        case FIXED:
            glColor4f(1.0, 0.0, 0., 1.0);
            break;
        default:
            break;
        }
        //glColor4f(1.0, .0, 0., 1.);

        if(v->getId() != currentVertex){
            glutSolidCube(pickTargetSize);
            glScalef(pickTargetSize/16,pickTargetSize/16,pickTargetSize/16);



            for (int offset = 0; offset < id.length(); offset++) {
                c = id.at(offset).toAscii();

                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c);
            }
            //            glutStrokeCharacter(GLUT_STROKE_ROMAN,'b');
            //            glutStrokeCharacter(GLUT_STROKE_ROMAN,'c');
        }
        else {
            glDisable(GL_BLEND);
            glLineWidth(4);
            glutSolidCube(4*pickTargetSize);
            glScalef(pickTargetSize/8,pickTargetSize/8,pickTargetSize/8);



            for (int offset = 0; offset < id.length(); offset++) {
                c = id.at(offset).toAscii();

                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            //            glutStrokeCharacter(GLUT_STROKE_ROMAN,'b');
            //            glutStrokeCharacter(GLUT_STROKE_ROMAN,'c');
            glLineWidth(2.0);
            glEnable(GL_BLEND);
        }

        glDisable(GL_BLEND);
        glPopMatrix();
    }
}

void GLWidget::render_crease(int vid, float lineLen){
    vector<Vertex*> vList = mm->getCurrentMesh()->getVList();


    glPushMatrix();
    //draw the frenet frame around the selected point
    //glLineWidth(2.);

    ofVec3f vec;



    if(vid > -1 ){
        Vertex* v = vList[vid];
        glColor3f(0., 0., 0.);
        glBegin(GL_LINES);
        glVertex3f(0., 0., 0.);
        vec = v->getNormal();
        vec *= lineLen;
        glVertex3f(vec.x, vec.y, vec.z);
        glEnd();
    }


    //glLineWidth(1.);
    glPopMatrix();

}

void GLWidget::toggleWireFrame()
{
    isWireframe = !isWireframe;
    updateGL();
}
void GLWidget::setMeshScale(float scale)
{
    mm->setScaleX(scale);
    mm->setScaleY(scale);
    mm->setScaleZ(scale);
    updateGL();
}

void GLWidget::toggleShowVertices(){
    showVertices = !showVertices;
    updateGL();
}
void GLWidget::toggleShowEdges(){
    showEdges = !showEdges;
    updateGL();
}
void GLWidget::setLineWidth(int val)
{
    lineWidth = (float) val;
    updateGL();
}
void GLWidget::loadNewMesh(const char *filename, int objFlag)
{
    ofVec3f scale(1,1,1);
    mm = new Model(scale, 5, objFlag, filename);
    min = mm->getMinPoint();
    size = mm->getBoxSize();
    g_xz_theta = 0;
    g_yz_theta = PI/2.;
    min = mm->getMinPoint();
    size = mm->getBoxSize();
    if(min.z > 0 )
        g_fViewDistance = size*2 + min.z;
    else
        g_fViewDistance = size*2 + (0-min.z);
    g_fNearPlane = 0.1;
    g_fFarPlane = 10*size*size+g_fViewDistance;
    pickTargetSize = size / 100;
    eye.set(g_fViewDistance*cos(g_xz_theta), g_fViewDistance*sin(g_yz_theta), g_fViewDistance*sin(g_xz_theta));


    updateGL();
}


void GLWidget::setReverseNormal(bool val){
    reverseNormal = val;
    updateGL();
}

int GLWidget::getVertexState(int vID){
    currentVertex = vID;
    updateGL();
    return mm->getCurrentMesh()->vList[vID]->getState();


}
void GLWidget::setVertexState(int vID, int state)
{

    mm->getCurrentMesh()->vList[vID]->setState(state);
    mm->updateMeshes(mm->getCurrentMeshLevel());
    updateGL();

}


void GLWidget::highlightCurrentVertex(){
    Vertex* v = mm->getCurrentMesh()->vList[currentVertex];

    ofVec3f A = v->getPoint();
    ofVec3f z(0.0,0.0,1.0);
    ofVec3f n = v->getNormal();
    ofVec3f axis = n.getPerpendicular(z);

    GLfloat rot = n.angle(z);
    QString id = QString::number(v->getId());
    char c;

    glPushMatrix();


    glTranslatef(A.x, A.y, A.z);
    glRotatef(-rot,axis.x, axis.y,axis.z);
    //glTranslatef(n.x, n.y, n.z);


    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    switch (v->getState()) {
    case FREE:
        glColor4f(0., 1., 0., 1.);
        break;
    case LOOSE:
        glColor4f( 0.0,0.0, 1.0, 1.0);
        break;
    case FIXED:
        glColor4f(1.0, 0.0, 0., 1.0);
        break;
    default:
        break;
    }




        glDisable(GL_BLEND);
        //enable_lights();
        glLineWidth(4);
        glutSolidCube(4*pickTargetSize);
        glScalef(pickTargetSize/8,pickTargetSize/8,pickTargetSize/8);



        for (int offset = 0; offset < id.length(); offset++) {
            c = id.at(offset).toAscii();

            glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
        }
        //            glutStrokeCharacter(GLUT_STROKE_ROMAN,'b');
        //            glutStrokeCharacter(GLUT_STROKE_ROMAN,'c');
        glLineWidth(2.0);
        glEnable(GL_BLEND);

}
void GLWidget::setRotate(float x, float y, float z)
{
    rotate.set(x,y,z);
    updateGL();
}

void GLWidget::setTranslate(float x, float y, float z){
    translate.set(x,y,z);
    updateGL();
}
