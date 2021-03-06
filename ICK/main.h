#pragma once

#define _USE_MATH_DEFINES
#include <iostream>
#include "FiguresController.h"
#include "CameraController.h"
#include "AntTweakBar/include/AntTweakBar.h"

float dirx, diry, dirz;
int windowH, windowW;
float focalLength = 200.0f;

float viewportWidth = 0.0f;
float viewportHeight = 0.0f;
bool keyTable[256];		//tablica 256 znak�w do obs�ugi klawiatury
bool fpsMode = false;	//zmienna za��czaj�ca tryb poruszania kamer� za pomoc� klawiatury i myszki
bool mouseLeftDown = false;
bool mouseRightDown = false;

const float translationSpeed = 0.1f;		//pr�dko�� poruszania si� kamery
const float rotationSpeed = M_PI * 0.04f;	//pr�dko�� rotacji kamery

//Wczytywanie figur
FiguresController figuresController;

//Wczytywanie t�a
FiguresController backgroundController;

//Sterowanie kamer�
CameraController cameraController;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Color and Depth Buffers
	glLoadIdentity();

	cameraController.Refresh();

	/* ------------------------------ OGNISKOWA ------------------------------ */
	glMatrixMode(GL_PROJECTION);	// Use the Projection Matrix
	glLoadIdentity();
	windowH = glutGet(GLUT_WINDOW_HEIGHT);
	windowW = glutGet(GLUT_WINDOW_WIDTH);
	glViewport(0, 0, windowW, windowH);
	gluPerspective(CameraController::getFOVy(120, focalLength), windowW * 1.0f / windowH, 0.1f, 100.0f);		// getFOVy(wysoko��_widoku, ogniskowa)
	glMatrixMode(GL_MODELVIEW);

	/* ----------------------------------------------------------------------- */

	/* ------------------------------ TUTAJ KOD ------------------------------ */
	figuresController.paintFigures();
	backgroundController.paintBackground();
	/*
	############## ANTTWEAKBAR ############
	*/
	TwDraw();
	/*
	#######################################
	*/
	/* ----------------------------------------------------------------------- */

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	if (h == 0) h = 1;	// Prevent a divide by zero, when window is too short (you cant make a window of zero width)
	float ratio = w * 1.0f / h;

	viewportWidth = w;
	viewportHeight = h;

	glViewport(0, 0, w, h);	// Set the viewport to be the entire window
	glMatrixMode(GL_PROJECTION);	// Use the Projection Matrix
	glLoadIdentity();		// Reset Matrix
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);	// Set the correct perspective.
	glMatrixMode(GL_MODELVIEW);	// Get Back to the Modelview
								/*
								### ANTTWEAKBAR ###
								*/
	TwWindowSize(w, h);
	/*
	###################
	*/
}

void KeyboardCallback(unsigned char key, int x, int y)
{
	if (!TwEventKeyboardGLUT(key, x, y)) {
		{
			if (key == ' ')
			{
				fpsMode = !fpsMode;
				if (fpsMode)
				{
					glutSetCursor(GLUT_CURSOR_NONE);
					glutWarpPointer(viewportWidth / 2, viewportHeight / 2);
				}
				else
				{
					glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
				}
			}

			keyTable[key] = true;
		}
	}
}

void KeyboardUpCallback(unsigned char key, int x, int y)
{
	keyTable[key] = false;
}

void MouseCallback(int button, int state, int x, int y)
{
	if (!TwEventMouseButtonGLUT(button, state, x, y)) {
		if (state == GLUT_DOWN)
		{
			if (button == GLUT_LEFT_BUTTON)
			{
				mouseLeftDown = true;
			}
			else if (button == GLUT_RIGHT_BUTTON)
			{
				mouseRightDown = true;
			}
		}
		else if (state == GLUT_UP)
		{
			if (button == GLUT_LEFT_BUTTON)
			{
				mouseLeftDown = false;
			}
			else if (button == GLUT_RIGHT_BUTTON)
			{
				mouseRightDown = false;
			}
		}
	}
}

void MouseMotionCallback(int x, int y)
{
	if (!TwEventMouseMotionGLUT(x, y))
	{
		static bool justWarped = false;

		if (justWarped)
		{
			justWarped = false;
			return;
		}

		if (fpsMode)
		{
			int dx = x - viewportWidth / 2;
			int dy = y - viewportHeight / 2;

			if (dx) {
				cameraController.RotateYaw(rotationSpeed * dx);
			}

			if (dy) {
				cameraController.RotatePitch(-rotationSpeed * dy);
			}

			glutWarpPointer(viewportWidth / 2, viewportHeight / 2);

			justWarped = true;

		}
	}
}

void Idle()
{
	glutPostRedisplay();
}

void TW_CALL set2dMode(void *)
{
	cameraController.set2dView();
}

void Timer(int value)
{
	if (fpsMode)
	{
		if (keyTable['w'])
		{
			cameraController.Move(translationSpeed);
		}
		else if (keyTable['s'])
		{
			cameraController.Move(-translationSpeed);
		}
		if (keyTable['a'])
		{
			cameraController.Strafe(translationSpeed);
		}
		else if (keyTable['d'])
		{
			cameraController.Strafe(-translationSpeed);
		}
		if (mouseLeftDown)
		{
			cameraController.Fly(-translationSpeed);
		}
		else if (mouseRightDown)
		{
			cameraController.Fly(translationSpeed);
		}
	}
	if (keyTable['+'])
	{
		focalLength += 0.5f;
	}
	else if (keyTable['-'])
	{
		focalLength -= 0.5f;
	}
	glutTimerFunc(1000 / 60, Timer, 0);
}

void antTweakBar()
{
	/*
	ANT TWEAK BAR
	###########################################################################################################################
	*/
	TwInit(TW_OPENGL, NULL);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
	TwGLUTModifiersFunc(glutGetModifiers);

	TwWindowSize(200, 400);
	TwBar *bar = TwNewBar("Camera");
	TwAddVarRW(bar, "x", TW_TYPE_FLOAT, &cameraController.posX, "step=0.1 keyDecr='LEFT' keyIncr='RIGHT'");
	TwAddVarRW(bar, "y", TW_TYPE_FLOAT, &cameraController.posY, "");
	TwAddVarRW(bar, "z", TW_TYPE_FLOAT, &cameraController.posZ, "step=0.1 keyDecr='DOWN' keyIncr='UP'");
	//TwAddVarRW(bar, "dirx", TW_TYPE_FLOAT, &cameraController.dirX, "");
	//TwAddVarRW(bar, "diry", TW_TYPE_FLOAT, &cameraController.dirY, ""); ## DO DEBUGOWANIA ##
	//TwAddVarRW(bar, "dirz", TW_TYPE_FLOAT, &cameraController.dirZ, "");
	TwAddVarRW(bar, "pitch", TW_TYPE_FLOAT, &cameraController.rotPitch, "min=-90 max=0");
	TwAddVarRW(bar, "yaw", TW_TYPE_FLOAT, &cameraController.rotYaw, "step=1 min=0 max=360");
	TwAddVarRW(bar, "focal length", TW_TYPE_FLOAT, &focalLength, "step=1 keyIncr='C' keyDecr='c'");
	TwAddButton(bar, "2D", set2dMode, NULL, " label='2D' ");
	/*
	Aby usun�� bibliotek� AntTweakBar z kodu, nale�y zakomentowa� wszystko pomi�dzy poziomymi liniami stworzynymi przez znaki #####,
	dodtkowo, w funkcji Display, zakomentowa� lub usun�� instrukcj� TWDraw();, w funkcji Reshape() zakomentowa� lub usun�� instrukcj�
	TwWindowSize(w, h);, oraz w funkcjach  KeyboardCallback(), MouseMotionCallback(), MouseCallback(), pozby� si� instrukcji warunkowych if(),
	if (!TwEventKeyboardGLUT(key, x, y)), if (!TwEventMouseMotionGLUT(x, y)),if (!TwEventMouseButtonGLUT(button, state, x, y)).
	(Tylko instrukcja, wraz z klamr� otwieraj�c� i zamykaj�c�. Blok instrukcji wewn�trz instrukcji warunkwej if, musi zosta� nienaruszony.
	###############################################################################################################################
	*/
}

void registerCallbacks()
{
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutMotionFunc(MouseMotionCallback);
	glutPassiveMotionFunc(MouseMotionCallback);
	glutMouseFunc(MouseCallback);
}