#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "block.h"

Block::Block(){
  _size = 0.05f/2.f;
  _pos.resize(3);
  _color.resize(3);
}

Block::~Block(){

}

void Block::draw(){
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(_color[0],_color[1],_color[2]);    // Color Blue
    glVertex3f( _size+_pos[0], _size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0], _size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0], _size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0], _size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0],-_size+_pos[1], _size+_pos[2]);
    glVertex3f(-_size+_pos[0],-_size+_pos[1], _size+_pos[2]);
    glVertex3f(-_size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
    glVertex3f( _size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
    glVertex3f( _size+_pos[0], _size+_pos[1], _size+_pos[2]);
    glVertex3f(-_size+_pos[0], _size+_pos[1], _size+_pos[2]);
    glVertex3f(-_size+_pos[0],-_size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0],-_size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0], _size+_pos[1],-_size+_pos[2]);
    glVertex3f( _size+_pos[0], _size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0], _size+_pos[1], _size+_pos[2]);
    glVertex3f(-_size+_pos[0], _size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
    glVertex3f(-_size+_pos[0],-_size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0], _size+_pos[1],-_size+_pos[2]);
    glVertex3f( _size+_pos[0], _size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0],-_size+_pos[1], _size+_pos[2]);
    glVertex3f( _size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glEnd();

  /*glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  glVertex3f( _size+_pos[0], _size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0], _size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0], _size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0], _size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0],-_size+_pos[1], _size+_pos[2]);
  glVertex3f(-_size+_pos[0],-_size+_pos[1], _size+_pos[2]);
  glVertex3f(-_size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glVertex3f( _size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0], _size+_pos[1], _size+_pos[2]);
  glVertex3f(-_size+_pos[0], _size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0],-_size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0], _size+_pos[1],-_size+_pos[2]);
  glVertex3f( _size+_pos[0], _size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0],-_size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0],-_size+_pos[1], _size+_pos[2]);
  glVertex3f(-_size+_pos[0], _size+_pos[1], _size+_pos[2]);
  glVertex3f(-_size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glVertex3f(-_size+_pos[0], _size+_pos[1],-_size+_pos[2]);
  glVertex3f( _size+_pos[0],-_size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0], _size+_pos[1], _size+_pos[2]);
  glVertex3f( _size+_pos[0],-_size+_pos[1],-_size+_pos[2]);
  glVertex3f( _size+_pos[0], _size+_pos[1],-_size+_pos[2]);
  glEnd();*/
}

void Block::setSize(float size){
  _size = size/2.f;
}
void Block::setPos(vector<float> pos){
  _pos = pos;
}
void Block::setColor(vector<float> color){
  _color = color;
}
