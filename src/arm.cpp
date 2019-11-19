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

  float posX = 0.0f;
  float posY = 0.0f;
  float posZ = 0.0f;
  for(int i=0;i<int(_armParts.size());i++){
    _armParts[i] = new ArmPart();
    _armParts[i]->setPos(vector<float>() = {posX,posY,posZ});
    _armParts[i]->setRot(vector<float>() = {jointAngles[i][0],jointAngles[i][1],jointAngles[i][2]});
    _armParts[i]->setSize(PART_SIZE,PART_SIZE/32);
    posX+=PART_SIZE*sin(jointAngles[i][0]*M_PI/180.f);
    posY+=PART_SIZE*cos(jointAngles[i][1]*M_PI/180.f);
    posZ+=PART_SIZE*cos(jointAngles[i][2]*M_PI/180.f);
  }
}

Arm::~Arm(){
  for(auto armPart : _armParts){
    delete armPart;
  }
}

void Arm::updateJoints(){
  float posX = 0.0f;
  float posY = 0.0f;
  float posZ = 0.0f;
  for(int i=0;i<int(_armParts.size());i++){
    _armParts[i]->setPos(vector<float>() = {posX,posY,posZ});
    _armParts[i]->setRot(vector<float>() = {jointAngles[i][0],jointAngles[i][1],jointAngles[i][2]});
    _armParts[i]->setSize(PART_SIZE,PART_SIZE/32);
    posX+=PART_SIZE*sin(jointAngles[i][0]*M_PI/180.f);
    posY+=PART_SIZE*cos(jointAngles[i][1]*M_PI/180.f);
    posZ+=PART_SIZE*cos(jointAngles[i][2]*M_PI/180.f);
  }
}

void Arm::draw(){
  for(int i=0 ; i<int(_armParts.size()) ; i++){
    _armParts[i]->setRot(jointAngles[i]);
    _armParts[i]->draw();
  }
}

//--------- Getters and Setters ---------//
float Arm::getFitness(){
    return _fitness;
}
void Arm::setFitness(float fitness){
  _fitness = fitness;
}
