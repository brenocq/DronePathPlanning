#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "armPart.h"
#include "math.h"

ArmPart::ArmPart(){
  _pos.resize(3);
  _rot.resize(3);
  _height = 1;
  _radius = 0.2f;
  _numSides = 32;
  _color = {1.0f, 0.27f, 0.0f};
}

ArmPart::~ArmPart(){

}

void ArmPart::setPos(vector<float> pos){
  _pos = pos;
}

void ArmPart::setRot(vector<float> rot){
  _rot = rot;
}
void ArmPart::setSize(float h, float r){
  _height = h;
  _radius = r;
}
void ArmPart::setNumSides(float numSides){
  _numSides = numSides;
}
void ArmPart::setColor(vector<float> color){
  _color = color;
}

void ArmPart::draw(){
  //---------- Draw line ----------//
  glColor4f(_color[0], _color[1], _color[2], 1.0f);
  glBegin(GL_LINES);
  glVertex3f(_pos[0], _pos[1], _pos[2]);
  glVertex3f(_pos[0]+_height*sin(_rot[0]*M_PI/180.f),
             _pos[1]+_height*cos(_rot[1]*M_PI/180.f),
             _pos[2]+_height*cos(_rot[2]*M_PI/180.f));
  glEnd();
  //---------- Draw Sphere ----------//
  glPushMatrix();
    glTranslatef(_pos[0], _pos[1], _pos[2]);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glutSolidSphere(_height/12,12, 12);
  glPopMatrix();
}
