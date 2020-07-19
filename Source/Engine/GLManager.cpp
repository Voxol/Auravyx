#include "GLManager.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Log.h"
GLManager::GLManager()
{
}

GLManager::~GLManager()
{
}

WindowManager GLManager::window;

void glfwErrorCallback(int error, const char* description)
{
	std::string errorCodeString;
	errorCodeString.append("[");
	errorCodeString.append(std::to_string(error));
	errorCodeString.append("] ");
	errorCodeString.append(description);
	Log::out("OpenGL", "GLFW Error : " + errorCodeString + " " + description, LBLUE);
}
void GLManager::start()
{
	if (!glfwInit())
	{
		Log::out("OpenGL", "GLFW Init() failed.", RED);
	}

	glfwSetErrorCallback(glfwErrorCallback);

	window.create();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		Log::out("OpenGL", "GLEW Error : '" + std::to_string((long) glewGetErrorString(err)) + "'", RED);
		system("PAUSE");
	}
}

WindowManager GLManager::getWindowManager()
{
	return window;
}
