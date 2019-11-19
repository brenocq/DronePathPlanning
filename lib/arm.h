#ifndef ARM_H
#define ARM_H
#include <vector>
#include "armPart.h"

using namespace std;

class Arm{
public:
  Arm();
  ~Arm();

  void draw();
  void updateJoints();

  //--------- Getters and Setters ---------//
  float getFitness();
  void setFitness(float fitness);
private:
  float _fitness;
  vector<ArmPart*> _armParts;

public:
  vector<vector<float> >jointAngles;
};


#endif// ARM_H
