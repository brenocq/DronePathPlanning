#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>

#include "geneticAlg.h"
#include "scene.h"

using namespace std;

//---------- Objects ----------//
GeneticAlg *geneticAlg = new GeneticAlg();
Scene *scene = new Scene();
//---------- Definitions ----------//
float viewAngleH = 0;
float viewAngleV = 0;
float viewDist = 3;

//---------- Functions ----------//
void closeProgram(int signum);// Free memory
void configure();// Configure glut scene

//---------- Callbacks ----------//
void displayCallback();
void reshapeCallback(GLsizei width, GLsizei height);
void keyboardCallback(unsigned char key, int x, int y);
void timerCallback(int value);

int main(int argc, char** argv){
  signal(SIGINT, closeProgram);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Drone Path Planning");

  configure();

  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutKeyboardFunc(keyboardCallback);
  glutTimerFunc(0, timerCallback, 0);

  glutMainLoop();

  return 0;
}

void configure(){
	glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

void timerCallback(int value){
  glutPostRedisplay();
  geneticAlg->run();
  glutTimerFunc(1000/60, timerCallback, 0);
}

void displayCallback(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glLoadIdentity();

	float posX = cos(viewAngleH*M_PI/180.0f)*viewDist;
	float posY = sin(viewAngleH*M_PI/180.0f)*viewDist;
	float posZ = viewAngleV;

	gluLookAt(
	posX, posY, posZ+1.0f,
	0.0f, 0.0f, 0.0f+1.0f,
	0.0f, 0.0f, 1.0f);

  geneticAlg->draw();
  scene->draw();

	glFlush();
  glutSwapBuffers();
}

void reshapeCallback(GLsizei width, GLsizei height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);

	float resize_f = 1.0f;
	float grow_shrink = 70.0f;
	gluPerspective(grow_shrink, resize_f * width / height, resize_f, 100 * resize_f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardCallback(unsigned char key, int x, int y){
  switch( key ){
    case 27: // ESCAPE key
      closeProgram(2);
    break;

    case 'a':
      viewAngleH-=5;
      viewAngleH = viewAngleH<0 ? 360+viewAngleH : viewAngleH;
    break;

    case 'd':
      viewAngleH+=5;
      viewAngleH = viewAngleH>360 ? viewAngleH-360 : viewAngleH;
    break;

		case 'w':
      viewAngleV+=viewAngleV<3 ? 0.1f : 0;
    break;

    case 's':
      viewAngleV-=viewAngleV>-3 ? 0.1f : 0;
    break;

    case 'e':
      viewDist-=viewDist>0.5f ? 0.1f : 0;
    break;

    case 'q':
      viewDist+=viewDist<10.0f ? 0.1f : 0;
    break;
  }

  glutPostRedisplay();
}


void closeProgram(int signum){
  cout<<"\nClosing the program...\n";
	delete geneticAlg;
  exit(signum);
}
