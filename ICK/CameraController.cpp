/*
Klasa CameraController odpowiedzialna za prac� i konfiguracj� kamery
Do ustawiania okre�lonej pozycji i rotacji kamery s�u�� funkcje z przedrostkiem "Set": SetPos, SetYaw, SetPitch

U�ycie innych funkcji do wy�ej okre�lonego celu jest niedopuszczalne - mo�e to zepsu� dzia�anie klasy CameraController

*/

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

//Inicjalizacja warto�ci pocz�tkowych kamery
void CameraController::Init()
{
	SetPos(0.0f, 10.f, 0.0f);
	SetPitch(-90.0f);
	SetYaw(0.0f);
}

/*	Funkcja Refresh (wywo�ywana po ka�dej zmianie parametr�w kamery) odpowiada za aktualizacj� parametr�w wymaganych do poprawnego u�ycia funkcji gluLookAt
	Cz�sto wyst�puj�ce wyra�enie 'M_PI / 180.0f' to zamiana stopni na radiany (funkcja cos() i sin() przyjmuje radiany)
	'rotYaw + 90.0f' pozwala na zorientowanie osi rotacji w odpowiednich kierunkach
*/
void CameraController::Refresh()
{
	if (rotPitch == -90.f) {
		dirX = cos((rotYaw + 90.0f) * M_PI / 180.0f) * 0.00001;
		dirY = sin(rotPitch * M_PI / 180.0f);
		dirZ = sin((rotYaw + 90.0f) * M_PI / 180.0f) * 0.00001;
	}
	else {
		dirX = cos((rotYaw + 90.0f) * M_PI / 180.0f) * cos(rotPitch * M_PI / 180.0f);
		dirY = sin(rotPitch * M_PI / 180.0f);
		dirZ = sin((rotYaw + 90.0f) * M_PI / 180.0f) * cos(rotPitch * M_PI / 180.0f);
	}


	strafeX = cos((rotYaw) * M_PI / 180.0f);
	strafeZ = sin((rotYaw) * M_PI / 180.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, posX + dirX, posY + dirY, posZ + dirZ, 0.0f, 1.0f, 0.0f);
}

/*
	Funkcja Move u�ywana jest do aktualizacji parametr�w kamery zwi�zanych tylko ze zmian� jej po�o�enia
	Wywo�ana zostaje funkcja Refresh() aby funkcj� gluLookAt "ustawi� kamer� na scenie"
*/
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

/*
	Funkcja Strafe odpowiada za poruszanie si� kamery na boki (tylko dla trybu sterowania kamer� poprzez klawiatur� i myszk�)
*/
void CameraController::Strafe(float incr)
{
	posX = posX + incr * strafeX;
	posZ = posZ + incr * strafeZ;

	Refresh();
}

/*
	Funkcja Fly odpowiada za zmian� wysoko�ci na jakiej znajduje si� kamera (tylko dla trybu sterowania kamer� poprzez klawiatur� i myszk�)
*/
void CameraController::Fly(float incr)
{
	posY = posY + incr;

	Refresh();
}

/*
	Funkcja RotateYaw obs�uguje aktualizacj� k�ta rotacji po osi Y (rozgl�danie si� na boki)
	!!! NIE s�u�y do ustawiania okre�lonego k�ta rotacji - w tym celu u�yj funkcji SetYaw(float angle) !!!
*/
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

/*
	Funkcja RotatePitch aktualizuje k�t nachylenia kamery (spogl�danie do g�ry i w d�)
	!!! NIE s�u�y do ustawiania okre�lonego k�ta rotacji - w tym celu u�yj funkcji SetPitch(float angle) !!!
*/
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

/*
	�UKASZ - DODAJ KOMENTARZ
*/
double CameraController::getFOVy(int frameHeight, double focalLength)
{
	return 2 * atan(frameHeight / (2 * focalLength)) * 57.2957795;
}

/*
	Ustawiaj�c tryb wy�wietlania 2D, ta funkcja ustawia k�ty rotacji kamery, tak aby skierowana by�a pionowo w d�
*/
void CameraController::set2dView() {
	SetPitch(-90.f);
	SetYaw(0.f);
}

/*
	S�u�y do ustawienia okre�lonej pozycji kamery
*/
void CameraController::SetPos(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;

	Refresh();
}

/*
	S�u�y do ustawienia okre�lonego k�ta rotacji Yaw (rozgl�danie na boki)
*/
void CameraController::SetYaw(float angle)
{
	rotYaw = angle;

	Refresh();
}

/*
	S�u�y do ustawienia okre�lonego k�ta rotacji Pitch (spogl�danie w g�r� i w d�)
*/
void CameraController::SetPitch(float angle)
{
	rotPitch = angle;

	Refresh();
}
