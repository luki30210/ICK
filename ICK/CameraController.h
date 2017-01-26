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

	float posX, posY, posZ;	//Zmienne dotycz�ce pozycji kamery
	float dirX, dirY, dirZ;	//Zmienne pomocnicze, tworz�ce wektor kierunku w kt�rym "patrzy" kamera - obliczane w funkcji Refresh
	float rotYaw, rotPitch; //K�ty rotacji
	float strafeX, strafeZ; //Zmienne tworz�ce wektor prostopad�y do kierunku "patrzenia" kamery - wykorzystywane przy poruszani si� kmaery na boki

private:
};