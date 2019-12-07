#ifndef GENETICALG_H
#define GENETICALG_H
#include <vector>
#include "parameters.h"
#include "arm.h"

using namespace std;

class GeneticAlg{
public:
  GeneticAlg();
  ~GeneticAlg();

  void initializePop();
  void genNewPop();

  void run();
  void draw();

  //-------- Getters and Setters --------//
  void setGoal(vector<float> goal);
  vector<float> getGoal() const;

private:
  vector<Arm*> _arms;
  vector<float> _goal;
};


#endif// GENETICALG_H
