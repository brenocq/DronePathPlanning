#include "scene.h"
#include "parameters.h"

Scene::Scene(){
  float sizeFloor = 11;
  float wallSize = 20;
	float wallHeight = 15;
	
	_blocks.resize(sizeFloor*sizeFloor + wallSize*wallHeight);
  for (int i = 0; i < sizeFloor; i++) {
    for (int j = 0; j < sizeFloor; j++) {
      _blocks[i*sizeFloor+j] = new Block();
      _blocks[i*sizeFloor+j]->setSize(0.3f);
      _blocks[i*sizeFloor+j]->setPos({0.3f*(i-sizeFloor/2),0.3f*(j-sizeFloor/2),-(PART_SIZE)/2+0.10f});
      _blocks[i*sizeFloor+j]->setColor(vector<float>{0.7,0.7,0.7});
    }
  }

  for (int i = 0; i < wallHeight; i++) {
    for (int j = 0; j < wallSize; j++) {
      _blocks[sizeFloor*sizeFloor+i*wallSize+j] = new Block();
      _blocks[sizeFloor*sizeFloor+i*wallSize+j]->setSize(0.05f);
      _blocks[sizeFloor*sizeFloor+i*wallSize+j]->setPos({0.5f,0.1f*j-0.1f*wallSize/2,0.1f*(i+1)-(PART_SIZE)/2+0.10f});
      _blocks[sizeFloor*sizeFloor+i*wallSize+j]->setColor(vector<float>{0.7,0.0,0.0});
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
