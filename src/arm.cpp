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
  _fitness = 0;
  _armParts.resize(QTY_JOINTS);
  jointAngles.resize(QTY_JOINTS);
  for(int i=0;i<int(jointAngles.size());i++){
    jointAngles[i].resize(3);
  }

  for(int i=0;i<int(_armParts.size());i++){
    _armParts[i] = new ArmPart();
    _armParts[i]->setPos(vector<float>() = {0,0,PART_SIZE});
    _armParts[i]->setRot(vector<float>() = {jointAngles[i][0],jointAngles[i][1],jointAngles[i][2]});
    _armParts[i]->setSize(PART_SIZE,PART_SIZE/32);
  }
}

Arm::~Arm(){
  for(auto armPart : _armParts){
    delete armPart;
  }
}

void Arm::draw(){
  for(int i=0 ; i<int(_armParts.size()) ; i++){
    _armParts[i]->setRot(jointAngles[i]);
    _armParts[i]->draw();
    glColor4f(0.7f, 0.7f,0.7f, 0.5f);
    glutSolidSphere(PART_SIZE/10,32, 32);
  }
}

//--------- Getters and Setters ---------//
float Arm::getFitness(){
    return _fitness;
}
void Arm::setFitness(float fitness){
  _fitness = fitness;
}
