#include "scene.h"
#include "parameters.h"

Scene::Scene(){
  float sizeFloor = 11;
  _blocks.resize(sizeFloor*sizeFloor);
  for (int i = 0; i < sizeFloor; i++) {
    for (int j = 0; j < sizeFloor; j++) {
      _blocks[i*sizeFloor+j] = new Block();
      _blocks[i*sizeFloor+j]->setSize(0.3f);
      _blocks[i*sizeFloor+j]->setPos({0.3f*(i-sizeFloor/2),0.3f*(j-sizeFloor/2),-(PART_SIZE)/2+0.10f});
      _blocks[i*sizeFloor+j]->setColor(vector<float>{0.7,0.7,0.7});
    }
  }
}

Scene::~Scene(){
  for (int i = 0; i < int(_blocks.size()); i++) {
    delete _blocks[i];
  }
}

void Scene::draw(){
  for (auto block : _blocks) {
    block->draw();
  }
}
