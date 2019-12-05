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
  _goal.resize(3);
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
        //cout<<arm->jointAngles[i][j]<< (j!=2?",":"");
      }
      //cout<<")";
    }
    //cout<<"\n";
    arm->updateJoints();
  }
}

void GeneticAlg::genNewPop(){
  vector<pair<float, Arm*> > bestArms;
  Arm* bestArm = NULL;

  // Get best arm
  bestArms.resize(SIZE_POP);
  for (int i = 0; i < SIZE_POP; i++) {
    bestArms[i] = make_pair(_arms[i]->getFitness(), _arms[i]);
  }
  sort(bestArms.begin(), bestArms.end());
  bestArm = bestArms[0].second;

  // Crossing
  for (auto arm : _arms) {
    if(arm==bestArm)continue;
    for (int i = 0; i < QTY_JOINTS; i++) {
      for (int j = 0; j < 3; j++) {
        arm->jointAngles[i][j] = 0.5f*arm->jointAngles[i][j] + 0.5f*bestArm->jointAngles[i][j];
      }
    }
    arm->updateJoints();
  }

  // Mutation
  for (auto arm : _arms) {
    if(arm==bestArm)continue;
    for (int i = 0; i < QTY_JOINTS; i++) {
      for (int j = 0; j < 3; j++) {
        arm->jointAngles[i][j] += (rand()%200/100.f)-1.0f;
      }
    }
    arm->updateJoints();
  }

}

void GeneticAlg::run(){
  float goalX = _goal[0];
  float goalY = _goal[1];
  float goalZ = _goal[2];

  // Calculate fitness
  int cont=0;
  for (auto arm : _arms) {
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    for(int j=0;j<QTY_JOINTS;j++){
      posX+=PART_SIZE*sin(arm->jointAngles[j][0]*M_PI/180.f);
      posY+=PART_SIZE*cos(arm->jointAngles[j][1]*M_PI/180.f);
      posZ+=PART_SIZE*cos(arm->jointAngles[j][2]*M_PI/180.f);
    }

    float dx = posX-goalX;
    float dy = posY-goalY;
    float dz = posZ-goalZ;
    float dist = sqrt(dx*dx + dy*dy + dz*dz);
    arm->setFitness(dist);
  }

  genNewPop();
}


void GeneticAlg::draw(){
  // Print only best arm
  vector<pair<float, int> > bestArms;

  bestArms.resize(SIZE_POP);
  for (int i = 0; i < SIZE_POP; i++) {
    bestArms[i] = make_pair(_arms[i]->getFitness(), i);
  }
  sort(bestArms.begin(), bestArms.end());

  _arms[bestArms[0].second]->draw();

  // Uncomment to see all arms
  /*for(auto arm : _arms){
    glPushMatrix();
    arm->draw();
    glPopMatrix();
  }*/

  // Draw goal position
  glPushMatrix();

  glTranslatef(_goal[0], _goal[1], _goal[2]);
  glColor4f(0.1f, 0.7f,0.1f, 1.0f);
  glutSolidSphere(0.07f,32, 32);

  glPopMatrix();
}

//-------- Getters and Setters --------//
void GeneticAlg::setGoal(vector<float> goal){
  _goal = goal;
}
vector<float> GeneticAlg::getGoal() const{
  return _goal;
}
