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

private:
  vector<ArmPart*> _armParts;
  vector<vector<float> >_jointAngles;
};


#endif// ARM
