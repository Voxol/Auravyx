#pragma once
#include <vector>
#include "Auravyx/Physics/PhysicsObject.h"
#include <memory>
class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void addObject(const std::shared_ptr<PhysicsObject>& object);

	void update();

private:

	double xGravity = 0, yGravity = -9.81, zGravity = 0;

	std::vector<std::shared_ptr<PhysicsObject>> objects;
};

