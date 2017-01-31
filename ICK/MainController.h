#pragma once

/*
FPS Control

SPACEBAR - prze³¹cza tryb pracy kamer¹ - sterowanie kamer¹ za pomoc¹ klawiatury i myszki
W, A, S, D - poruszanie siê kamer¹
mouse - rozgl¹danie siê (rotacja Yaw i Pitch)
left/right mouse button - zwiêkszenie/obni¿enie wysokoœci na której znajduje siê kamera

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
	static FiguresController backgroundController;	//Wczytywanie t³a
	static CameraController cameraController;		//Sterowanie kamer¹
	static float dirx, diry, dirz;
	static int windowH, windowW;
	static float focalLength;
	static float viewportWidth;
	static float viewportHeight;
	static bool keyTable[256];		//tablica 256 znaków do obs³ugi klawiatury
	static bool fpsMode;			//zmienna za³¹czaj¹ca tryb poruszania kamer¹ za pomoc¹ klawiatury i myszki
	static bool mouseLeftDown;
	static bool mouseRightDown;
	static float translationSpeed;		//prêdkoœæ poruszania siê kamery
	static float rotationSpeed;			//prêdkoœæ rotacji kamery
public:
	MainController();
	~MainController();
	static void Init();
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

