#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include "parameters.h"
#include "arm.h"

Arm::Arm(){
  _armParts.resize(QTY_JOINTS);
  _jointAngles.resize(QTY_JOINTS);
  for(int i=0;i<int(_jointAngles.size());i++){
    _jointAngles[i].resize(3);
  }

  _jointAngles[1][1]=30;
  _jointAngles[3][0]=60;

  for(int i=0;i<int(_armParts.size());i++){
    _armParts[i] = new ArmPart();
    _armParts[i]->setPos(vector<float>() = {0,0,PART_SIZE});
    _armParts[i]->setRot(vector<float>() = {_jointAngles[i][0],_jointAngles[i][1],_jointAngles[i][2]});
    _armParts[i]->setSize(PART_SIZE,PART_SIZE/6);
  }
}

Arm::~Arm(){
  for(auto armPart : _armParts){
    delete armPart;
  }
}

void Arm::draw(){
  for(auto armPart : _armParts){
    armPart->draw();
  }
}
