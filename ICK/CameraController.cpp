#include "CameraController.h"

float CameraController::cameraX = 0.0f;
float CameraController::cameraY = 10.0f;
float CameraController::cameraZ = 0.0f;

float CameraController::cameraDirX = 0.0f;
float CameraController::cameraDirY = 0.0010f;
float CameraController::cameraDirZ = 0.0f;

float CameraController::cameraUpVectx = 0.0f;
float CameraController::cameraUpVecty = 0.0f;
float CameraController::cameraUpVectz = 1.0f;

float CameraController::cameraRotationX = 0.0f;
float CameraController::cameraRotationY = 45.0f;

CameraController::CameraController()
{

}

CameraController::~CameraController()
{

}

void CameraController::ManageKeyboardCallback(unsigned char key, bool keyDown)
{
	if (key == 'w')
	{
		if (keyDown)
		{
			speedZ = -0.1f;
		}
		else
		{
			speedZ = 0.0f;
		}
	}
	if (key == 's')
	{
		if (keyDown)
		{
			speedZ = 0.1f;
		}
		else
		{
			speedZ = 0.0f;
		}
	}
	if (key == 'd')
	{
		if (keyDown)
		{
			speedX = 0.1f;
		}
		else
		{
			speedX = 0.0f;
		}
	}
	if (key == 'a')
	{
		if (keyDown)
		{
			speedX = -0.1f;
		}
		else
		{
			speedX = 0.0f;
		}
	}
}

void CameraController::UpdateKeyboardInput()
{
	if (speedZ < 1.0f && speedZ > 0.0f)
	{
		speedZ += 0.1f;
	}
	if (speedZ > -1.0f && speedZ < 0.0f)
	{
		speedZ += -0.1f;
	}
	if (speedX < 1.0f && speedX > 0.0f)
	{
		speedX += 0.1f;
	}
	if (speedX > -1.0f && speedX < 0.0f)
	{
		speedX += -0.1f;
	}

	cameraZ += speedZ * 0.05f;
	cameraX += speedX * 0.05f;
	
}