#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	~Window();

	int initialize();

	GLfloat getBufferWidth(){return bufferWidth;}
	GLfloat getBufferHeight(){return bufferHeight;}
	bool getShouldClose(){return glfwWindowShouldClose(mainWindow);}

	bool* getKeys(){return keys;}
	GLfloat getXChange();
	GLfloat getYChange();	

	void swapBuffers(){glfwSwapBuffers(mainWindow);}

private:
	GLFWwindow *mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
#endif// WINDOW_H
