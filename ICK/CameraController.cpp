/*
Klasa CameraController odpowiedzialna za pracê i konfiguracjê kamery
Do ustawiania okreœlonej pozycji i rotacji kamery s³u¿¹ funkcje z przedrostkiem "Set": SetPos, SetYaw, SetPitch

U¿ycie innych funkcji do wy¿ej okreœlonego celu jest niedopuszczalne - mo¿e to zepsuæ dzia³anie klasy CameraController

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

//Inicjalizacja wartoœci pocz¹tkowych kamery
void CameraController::Init()
{
	SetPos(0.0f, 10.f, 0.0f);
	SetPitch(-90.0f);
	SetYaw(0.0f);
}

/*	Funkcja Refresh (wywo³ywana po ka¿dej zmianie parametrów kamery) odpowiada za aktualizacjê parametrów wymaganych do poprawnego u¿ycia funkcji gluLookAt
	Czêsto wystêpuj¹ce wyra¿enie 'M_PI / 180.0f' to zamiana stopni na radiany (funkcja cos() i sin() przyjmuje radiany)
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
	Funkcja Move u¿ywana jest do aktualizacji parametrów kamery zwi¹zanych tylko ze zmian¹ jej po³o¿enia
	Wywo³ana zostaje funkcja Refresh() aby funkcj¹ gluLookAt "ustawiæ kamerê na scenie"
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
	Funkcja Strafe odpowiada za poruszanie siê kamery na boki (tylko dla trybu sterowania kamer¹ poprzez klawiaturê i myszkê)
*/
void CameraController::Strafe(float incr)
{
	posX = posX + incr * strafeX;
	posZ = posZ + incr * strafeZ;

	Refresh();
}

/*
	Funkcja Fly odpowiada za zmianê wysokoœci na jakiej znajduje siê kamera (tylko dla trybu sterowania kamer¹ poprzez klawiaturê i myszkê)
*/
void CameraController::Fly(float incr)
{
	posY = posY + incr;

	Refresh();
}

/*
	Funkcja RotateYaw obs³uguje aktualizacjê k¹ta rotacji po osi Y (rozgl¹danie siê na boki)
	!!! NIE s³u¿y do ustawiania okreœlonego k¹ta rotacji - w tym celu u¿yj funkcji SetYaw(float angle) !!!
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
	Funkcja RotatePitch aktualizuje k¹t nachylenia kamery (spogl¹danie do góry i w dó³)
	!!! NIE s³u¿y do ustawiania okreœlonego k¹ta rotacji - w tym celu u¿yj funkcji SetPitch(float angle) !!!
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
	Zwraca pole widzenia obiektywu w stopniach - parametr ten u¿ywany jest przez funkcjê gluPerspective do ustawienia kamery.
	Pierwszym parametrem funkcji (int frameHeight) jest wysokoœæ ramki w pierwszym planie. Drugi parametr (double focalLength) to ogniskowa.
*/
double CameraController::getFOVy(int frameHeight, double focalLength)
{
	return 2 * atan(frameHeight / (2 * focalLength)) * 57.2957795;
}

/*
	Ustawiaj¹c tryb wyœwietlania 2D, ta funkcja ustawia k¹ty rotacji kamery, tak aby skierowana by³a pionowo w dó³
*/
void CameraController::set2dView() {
	SetPitch(-90.f);
	SetYaw(0.f);
}

/*
	S³u¿y do ustawienia okreœlonej pozycji kamery
*/
void CameraController::SetPos(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;

	Refresh();
}

/*
	S³u¿y do ustawienia okreœlonego k¹ta rotacji Yaw (rozgl¹danie na boki)
*/
void CameraController::SetYaw(float angle)
{
	rotYaw = angle;

	Refresh();
}

/*
	S³u¿y do ustawienia okreœlonego k¹ta rotacji Pitch (spogl¹danie w górê i w dó³)
*/
void CameraController::SetPitch(float angle)
{
	rotPitch = angle;

	Refresh();
}
