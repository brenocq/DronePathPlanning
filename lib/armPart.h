#ifndef ARMPART_H
#define ARMPART_H

#include <vector>

using namespace std;

class ArmPart{
public:
  ArmPart();
  ~ArmPart();

  //--------- Getters and Setters ---------//
  void setPos(vector<float> pos);
  void setRot(vector<float> rot);
  void setSize(float h, float r);
  void setNumSides(float numSides);
  void setColor(vector<float> color);
  void draw();
private:
  vector<float> _pos;
  vector<float> _rot;
  vector<float> _color;
  float _height;
  float _radius;
  int _numSides;
};


#endif// ARMPART_H
