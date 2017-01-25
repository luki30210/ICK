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

	SetPos(0.0f, 17.f, 1.0f);
	SetPitch(-1.5709f);
	SetYaw(3.1416f);
}

void CameraController::Refresh()
{
	dirX = cos((rotYaw + 90.0f) * M_PI / 180.0f) * cos(rotPitch * M_PI / 180.0f);
	dirY = sin(rotPitch * M_PI / 180.0f);
	dirZ = sin((rotYaw + 90.0f) * M_PI / 180.0f) * cos(rotPitch * M_PI / 180.0f);

	strafeX = cos((rotYaw) * M_PI / 180.0f);
	strafeZ = sin((rotYaw) * M_PI / 180.0f);

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
	float lx = cos((rotYaw + 90.0f) * M_PI / 180.0f) * cos(rotPitch * M_PI / 180.0f);
	float ly = sin(rotPitch * M_PI / 180.0f);
	float lz = sin((rotYaw + 90.0f) * M_PI / 180.0f) * cos(rotPitch * M_PI / 180.0f);

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
	if (rotYaw > 360.0f)
	{
		rotYaw -= 360.0f;
	}
	if (rotYaw < 0.0f)
	{
		rotYaw = 360.0f + (rotYaw);
	}

	Refresh();
}

void CameraController::RotatePitch(float angle)
{
	const float limit = 89.0;

	rotPitch += angle;

	if (rotPitch < -limit)
		rotPitch = -limit;

	if (rotPitch > limit)
		rotPitch = limit;

	Refresh();
}

double CameraController::getFOVy(int frameHeight, double focalLength)
{
	return 2 * atan(frameHeight / (2 * focalLength)) * 57.2957795;
}

void CameraController::set2dView() {
	SetPitch(-1.5709f);
	SetYaw(3.1416f);
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
