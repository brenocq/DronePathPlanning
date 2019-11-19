#ifndef ARM
#define ARM
#include <vector>
#include "armPart.h"

using namespace std;

class Arm{
public:
  Arm();
  ~Arm();

  void draw();

  //--------- Getters and Setters ---------//
  float getFitness();
  void setFitness(float fitness);
private:
  float _fitness;
  vector<ArmPart*> _armParts;

public:
  vector<vector<float> >jointAngles;
};


#endif// ARM
