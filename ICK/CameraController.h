#pragma once

class CameraController
{
public:
	static float cameraX;
	static float cameraY;
	static float cameraZ;

	static float cameraDirX;
	static float cameraDirY;
	static float cameraDirZ;

	static float cameraUpVectx;
	static float cameraUpVecty;
	static float cameraUpVectz;

	static float cameraRotationX;
	static float cameraRotationY;

	float speedX;
	float speedY;
	float speedZ;

	int currentX = 0;
	int currentY = 0;
	int referencePointX;
	int referencePointY;

	void ManageKeyboardCallback(unsigned char key, bool keyDown);
	void UpdateKeyboardInput();

	CameraController();
	~CameraController();

private:

};