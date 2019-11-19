#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "block.h"

using namespace std;

class Scene{
public:
  Scene();
  ~Scene();

  void draw();
private:
  vector<Block*> _blocks;
};


#endif// SCENE_H
