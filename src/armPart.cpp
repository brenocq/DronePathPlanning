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
  glTranslatef(_pos[0], _pos[1], _pos[2]);
  glRotatef(_rot[0], 1.0f, 0.0f, 0.0f);
  glRotatef(_rot[1], 0.0f, 1.0f, 0.0f);
  glRotatef(_rot[2], 0.0f, 0.0f, 1.0f);


  // Cylinder Bottom
  glBegin(GL_POLYGON);
  glColor4f(1.0, 0.0, 1.0, 1.0);
  for(int i = 0; i <= 360 ; i += (360 / _numSides)) {
    float a = i * M_PI / 180; // degrees to radians
    glVertex3f(_radius * cos(a), _radius * sin(a), 0.0);
  }
  glEnd();

  // Cylinder Top
  glBegin(GL_POLYGON);
  glColor4f(1.0, 0.0, 1.0, 1.0);
  for(int i = 0; i <= 360; i += (360 / _numSides)) {
    float a = i * M_PI / 180; // degrees to radians
    glVertex3f(_radius * cos(a), _radius * sin(a), _height);
  }
  glEnd();

  // Cylinder "Cover"
  glBegin(GL_QUAD_STRIP);
  glColor4f(1.0, 0.0, 1.0, 1.0);
  for(int i = 0; i < 480; i += (360 / _numSides)) {
    float a = i * M_PI / 180; // degrees to radians
    glVertex3f(_radius * cos(a), _radius * sin(a), 0.0);
    glVertex3f(_radius * cos(a), _radius * sin(a), _height);
  }
  glEnd();
}
