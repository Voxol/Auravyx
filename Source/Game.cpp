#include "stdafx.h"
#include "WindowManager.h"
#include "Log.h"
#include "Sound.h"
#include "Resource.h"
#include "GFX.h"
#include "Shaders.h"
#include "Clock.h"
#include <thread>
#include "Mouse.h"
#include "Settings.h"
#include <Profiler.h>
#include <GameState.h>
#include <iostream>
#include <GameManager.h>
double UPS = 60;
double thisFrame = 0;
double nextFrame = 0;

std::chrono::duration<long, std::milli> timeStep = std::chrono::milliseconds(1);

GameManager gameManager;
WindowManager window;

void glfwErrorCallback(int error, const char* description)
{
	std::string errorCodeString;
	errorCodeString.append("[");
	errorCodeString.append(std::to_string(error));
	errorCodeString.append("] ");
	errorCodeString.append(description);
	Log::out("OpenGL", "GLFW Error : " + errorCodeString + " " + description, LBLUE);
}

auto start = std::chrono::high_resolution_clock::now();

bool end = false;
bool updateEnd = false;

void updater()
{
	double lerp = 0;
	double updatesPerSecond = 1 / UPS;
	double lastTimeUPS = -1;
	double thisTimeUPS = 0;
	Mouse m;
	int time;
	double deltaUpdate;
	double lastTimeUPSOld = 0;
	
	while (!end)
	{
		//double lerp = delta * UPS;
		thisTimeUPS = glfwGetTime();
		deltaUpdate = thisTimeUPS - lastTimeUPS;
		lastTimeUPSOld = lastTimeUPS;
		lerp = deltaUpdate;
		if (lerp >= 1)
			lerp = fmod(lerp, 1.0);
		if (deltaUpdate >= updatesPerSecond)
		{
			lastTimeUPS = thisTimeUPS;
			gameManager.getCurrentState()->update();
			m.update(&(GameManager::world));
		}
		else
		{
			time = (updatesPerSecond - (glfwGetTime() - lastTimeUPSOld)) * 1000;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
		}
		Clock::lerp = lerp;
	}
	updateEnd = true;
}


int frameCount = 0;
double deltaRender = 0;
void loop()
{
	GameState gs;
	gameManager.setCurrentState(std::make_shared<GameState>(gs));

	gameManager.getCurrentState()->start();

	double lastTimeFPS = -1;
	double thisTimeFPS = 0;

	float volume = 1;
	
	std::thread updater(updater);
	Profiler p;
	p.init();

	double now = 0;
	double last = 0;
	float fpsCounter = 0;
	float lastFpsCounter = 0;
	int time;

	double lastTimeFPSOld = 0;
	Sound s;
	//s.play(Assets::getAudio("song"));
	
	while (!window.closeRequested())
	{
		double framesPerSecond = 1.0 / GFX::FPS;
		thisTimeFPS = glfwGetTime();
		deltaRender = thisTimeFPS - lastTimeFPS;
		lastTimeFPSOld = lastTimeFPS;
		if (GFX::FPS == GFX::UNLIMITED_FPS || deltaRender >= framesPerSecond)
		{
			window.update();
			gameManager.getCurrentState()->render();
			lastTimeFPS = thisTimeFPS;
		}
		else
		{
			time = (framesPerSecond - (glfwGetTime() - lastTimeFPSOld)) * 1000;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
		}
	}
	
	end = true;
	gameManager.getCurrentState()->stop();
	updater.join();
}

void printInfo()
{
	std::string glVersion = (char*)glGetString(GL_VERSION);
	std::string glVendor = (char*)glGetString(GL_VENDOR);
	std::string glRenderer = (char*)glGetString(GL_RENDERER);
	Log::out("[OpenGL]", "Version: " + glVersion + ", Vendor: " + glVendor + ", GPU: " + glRenderer, LBLUE);
	std::cout << "\n";
}

void loadAssetsAsync()
{
	Resource::loadAllAsyncAssets();
}

int main(int argc, char* argv[])
{
	std::cout << "LOL";
	Resource::DIR = std::string(argv[0]) + "\\..";
	Log::out("Game", "Loading...    UPS : " + std::to_string(UPS) + "  FPS : " + std::to_string(GFX::FPS), GREEN);
	
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
		printf("[Error] %s\n", glewGetErrorString(err));
		system("PAUSE");
	}

	Resource::loadBootAssets();
	
	GFX::init();

	printInfo();
	
	std::thread asyncLoader(loadAssetsAsync);

	double last = 0;
	double now = 0;

	while (!Resource::loadAllResources())
	{
		now = glfwGetTime();
		if (now - last > 1.0 / 144.0)
		{
			last = now;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 1);
			Resource::renderProgress();
			window.update();
		}
		std::this_thread::sleep_for(timeStep);
	}
	
	Resource::clearPreloadedResources();
	Shaders::lineShader->init();
	asyncLoader.join();
	WindowManager::hideMouse();

	loop();
	glfwTerminate();
	return 0;
}
