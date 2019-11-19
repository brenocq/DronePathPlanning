#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include "geneticAlg.h"

GeneticAlg::GeneticAlg(){
  // Create population
  for (int i = 0; i < SIZE_POP; i++) {
    _arms.push_back(new Arm());
  }
  initializePop();
  srand(42);
}

GeneticAlg::~GeneticAlg(){
  for (auto arm : _arms) {
    delete arm;
  }
}

void GeneticAlg::initializePop(){
  //int cont=0;
  for (auto arm : _arms) {
    //cout<<"Arm("<<cont++<<")";
    for (int i = 0; i < QTY_JOINTS; i++) {
      //cout<<"(";
      for (int j=0; j<3; j++) {
        arm->jointAngles[i][j] = rand()%18000/100.0f-90.f;
        cout<<arm->jointAngles[i][j]<< (j!=2?",":"");
      }
      //cout<<")";
    }
    //cout<<"\n";
  }
}

void GeneticAlg::genNewPop(){
  vector<pair<float, Arm*> > bestArms;
  Arm* bestArm = NULL;

  // Get best arm
  bestArms.resize(SIZE_POP);
  for (int i = 0; i < SIZE_POP; i++) {
    bestArms[i] = make_pair(_arms[0]->getFitness(), _arms[0]);
  }
  sort(bestArms.begin(), bestArms.end());
  bestArm = bestArms[0].second;

  // Crossing
  for (auto arm : _arms) {
    if(arm==bestArm)continue;
    for (int i = 0; i < QTY_JOINTS; i++) {
      for (int j = 0; j < 3; j++) {
        arm->jointAngles[i][j] = 0.99f*arm->jointAngles[i][j] + 0.01f*bestArm->jointAngles[i][j];
      }
    }
  }

  // Mutation

}

void GeneticAlg::run(){

  // Calculate fitness
  genNewPop();
}


void GeneticAlg::draw(){
  for(auto arm : _arms){
    glPushMatrix();
    arm->draw();
    glPopMatrix();
  }
  glPushMatrix();
  for (int j = 0; j < 3; j++) {

  }
  glPopMatrix();
}
