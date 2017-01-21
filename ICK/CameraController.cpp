#include "CameraController.h"
#include <stdio.h>
#include <math.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

CameraController::CameraController() 
{
	Init();	
};

CameraController::~CameraController() {};

void CameraController::Init()
{
	rotYaw = 0.0f;
	rotPitch = 0.0f;

	SetPos(0.0f, 3.5f, 5.0f);
	SetPitch(-0.5f);
	SetYaw(-1.5f);
}

void CameraController::Refresh()
{
	dirX = cos(rotYaw) * cos(rotPitch);
	dirY = sin(rotPitch);
	dirZ = sin(rotYaw) * cos(rotPitch);

	strafeX = cos(rotYaw - M_PI_2);
	strafeZ = sin(rotYaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, posX + dirX, posY + dirY, posZ + dirZ, 0.0f, 1.0f, 0.0f);
}

void CameraController::SetPos(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;

	Refresh();
}

void CameraController::GetPos(float &x, float &y, float &z)
{
	x = posX;
	y = posY;
	z = posZ;
}

void CameraController::GetDirectionVector(float &x, float &y, float &z)
{
	x = dirX;
	y = dirY;
	z = dirZ;
}

void CameraController::Move(float incr)
{
	float lx = cos(rotYaw)*cos(rotPitch);
	float ly = sin(rotPitch);
	float lz = sin(rotYaw)*cos(rotPitch);

	posX = posX + incr * lx;
	posY = posY + incr * ly;
	posZ = posZ + incr * lz;

	Refresh();
}

void CameraController::Strafe(float incr)
{
	posX = posX + incr * strafeX;
	posZ = posZ + incr * strafeZ;

	Refresh();
}

void CameraController::Fly(float incr)
{
	posY = posY + incr;

	Refresh();
}

void CameraController::RotateYaw(float angle)
{
	rotYaw += angle;

	Refresh();
}

void CameraController::RotatePitch(float angle)
{
	const float limit = 89.0 * M_PI / 180.0;

	rotPitch += angle;

	if (rotPitch < -limit)
		rotPitch = -limit;

	if (rotPitch > limit)
		rotPitch = limit;

	Refresh();
}

void CameraController::SetYaw(float angle)
{
	rotYaw = angle;

	Refresh();
}

void CameraController::SetPitch(float angle)
{
	rotPitch = angle;

	Refresh();
}
