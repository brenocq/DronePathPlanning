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

private:
  vector<Arm*> _arms;
};


#endif// GENETICALG_H
