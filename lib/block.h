#ifndef BLOCK_H
#define BLOCK_H
#include <vector>

using namespace std;

class Block{
public:
  Block();
  ~Block();

  void draw();

  //--------- Getters and Setters ---------//
  void setSize(float size);
  void setPos(vector<float> pos);
  void setColor(vector<float> color);
private:
  vector<float> _pos;
  vector<float> _color;
  float _size;
};


#endif// SCENE_H
