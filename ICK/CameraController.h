#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class CameraController
{
public:
	CameraController();
	~CameraController();

	void Init();
	void Refresh();
	void SetPos(float x, float y, float z);
	void GetPos(float &x, float &y, float &z);
	void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);

	// Navigation
	void Move(float incr);
	void Strafe(float incr);
	void Fly(float incr);
	void RotateYaw(float angle);
	void RotatePitch(float angle);


	static double getFOVy(int frameHeight, double focalLength);

	//View
	void set2dView();

	float posX, posY, posZ;  // Positions
	float dirX, dirY, dirZ; // Direction vector of where we are looking at
	float rotYaw, rotPitch; // Various rotation angles
	float strafeX, strafeZ; // Always 90 degree to direction vector

private:
};