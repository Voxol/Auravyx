#pragma once
#include "Auravyx/Utility/Math/Matrix4f.h"
class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	double x, y, z;
	double xPos, yPos, zPos;
	double xVel = 0, yVel = 0, zVel = 0;
	int cX, cY, cZ;
	double zoom = 1;
	double speed = 4;
	double speedMultiplier = 1;
	double fov = 110;
	Matrix4f projectionMatrix;

	void getPlayerInput();

	double xRot = 0, yRot = 0, zRot = 0;

	void set(double x, double y, double z, double xRot, double yRot, double zRot);

	double getXRot();

	double getYRot();

	double getZRot();

	double getX();

	double getY();

	double getZ();

	Matrix4f getViewMatrix() const;

	void setSpeedMultiplier(double x);

	void setFOV(double fov);
};

