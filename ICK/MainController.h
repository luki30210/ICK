#pragma once

/*
FPS Control

SPACEBAR - prze��cza tryb pracy kamer� - sterowanie kamer� za pomoc� klawiatury i myszki
W, A, S, D - poruszanie si� kamer�
mouse - rozgl�danie si� (rotacja Yaw i Pitch)
left/right mouse button - zwi�kszenie/obni�enie wysoko�ci na kt�rej znajduje si� kamera

*/

#define _USE_MATH_DEFINES
#include <iostream>
#include "FiguresController.h"
#include "CameraController.h"
#include "AntTweakBar/include/AntTweakBar.h"


class MainController
{
private:
	static FiguresController figuresController;		//Wczytywanie figur
	static FiguresController backgroundController;	//Wczytywanie t�a
	static CameraController cameraController;		//Sterowanie kamer�
	static float dirx, diry, dirz;
	static int windowH, windowW;
	static float focalLength;
	static float viewportWidth;
	static float viewportHeight;
	static bool keyTable[256];		//tablica 256 znak�w do obs�ugi klawiatury
	static bool fpsMode;			//zmienna za��czaj�ca tryb poruszania kamer� za pomoc� klawiatury i myszki
	static bool mouseLeftDown;
	static bool mouseRightDown;
	static float translationSpeed;		//pr�dko�� poruszania si� kamery
	static float rotationSpeed;			//pr�dko�� rotacji kamery
public:
	MainController();
	~MainController();
	void Init(int argc, char **argv);
public:
	static void Display();
	static void Reshape(int w, int h);
	static void KeyboardCallback(unsigned char key, int x, int y);
	static void KeyboardUpCallback(unsigned char key, int x, int y);
	static void MouseCallback(int button, int state, int x, int y);
	static void MouseMotionCallback(int x, int y);
	static void Idle();
	static void Timer(int value);
	static void TW_CALL set2dMode(void *);
public:
	static void loadFiguresFromFile(char *filename);
	static void loadBackgroundFromFile(char *filename);
};

