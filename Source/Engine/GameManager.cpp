#include "GameManager.h"
#include "M.h"
World GameManager::world;

std::shared_ptr<State> GameManager::currentState;

double GameManager::UPS = 60;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

std::shared_ptr<State> GameManager::getCurrentState()
{
	return currentState;
}

void GameManager::setCurrentState(std::shared_ptr<State> s)
{
	currentState = s;
}

double GameManager::getUPS()
{
	return UPS;
}
