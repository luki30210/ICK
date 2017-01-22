/*
FPS Control

SPACEBAR - toogle FPS control
W, A, S, D - to move
mouse - look around
left/right mouse button - fly down/up

*/


#define _USE_MATH_DEFINES
#include <iostream>
#include "FiguresController.h"
#include "CameraController.h"
#include "AntTweakBar/include/AntTweakBar.h"

FiguresController figuresController;
FiguresController backgroundController;
CameraController cameraController;

void Display();
void Reshape(int w, int h);
void KeyboardCallback(unsigned char key, int x, int y);
void KeyboardUpCallback(unsigned char key, int x, int y);
void MouseCallback(int button, int state, int x, int y);
void MouseMotionCallback(int x, int y);
void Idle();
void Timer(int value);
void TW_CALL set2dMode(void *);

float dirx, diry, dirz;
int windowH, windowW;
float focalLength = 200.0f;


float viewportWidth = 0.0f;
float viewportHeight = 0.0f;
bool keyTable[256];
bool fpsMode = false;
bool mouseLeftDown = false;
bool mouseRightDown = false;

const float translationSpeed = 0.1f;
const float rotationSpeed = M_PI / 180.0f * 0.08f;



int main(int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("OpenGL Figures");

	/*
	ANT TWEAK BAR
	*/
	TwInit(TW_OPENGL, NULL);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
	TwGLUTModifiersFunc(glutGetModifiers);

	TwWindowSize(200, 400);
	TwBar *bar = TwNewBar("Camera");
	TwAddVarRW(bar, "x", TW_TYPE_FLOAT, &cameraController.posX, "step=0.1 keyDecr='DOWN' keyIncr='UP'");
	TwAddVarRW(bar, "y", TW_TYPE_FLOAT, &cameraController.posY, "");
	TwAddVarRW(bar, "z", TW_TYPE_FLOAT, &cameraController.posZ, "step=0.1 keyDecr='LEFT' keyIncr='RIGHT'");
	TwAddVarRW(bar, "pitch", TW_TYPE_FLOAT, &cameraController.rotPitch, "");
	TwAddVarRW(bar, "yaw", TW_TYPE_FLOAT, &cameraController.rotYaw, "step=0.01");
	TwAddVarRW(bar, "focal length", TW_TYPE_FLOAT, &focalLength, "step=1 keyIncr='C' keyDecr='c'");
	TwAddButton(bar, "2D", set2dMode, NULL, " label='2D' ");



	glutIgnoreKeyRepeat(1);
	// register callbacks
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyboardCallback);
	glutKeyboardUpFunc(KeyboardUpCallback);
	glutMotionFunc(MouseMotionCallback);
	glutPassiveMotionFunc(MouseMotionCallback);
	glutMouseFunc(MouseCallback);

	Timer(0);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// Init figures
	figuresController.loadFiguresFromFile("Resources/data/example.xml");
	backgroundController.loadFiguresFromFile("Resources/data/background.xml");

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

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
	gluPerspective(CameraController::getFOVy(120, focalLength), windowW * 1.0f / windowH, 0.1f, 100.0f);		// getFOVy(wysokoœæ_widoku, ogniskowa)
	glMatrixMode(GL_MODELVIEW);

	/* ----------------------------------------------------------------------- */
	
	/* ------------------------------ TUTAJ KOD ------------------------------ */
	figuresController.paintFigures();
	backgroundController.paintBackground();
	TwDraw();
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
	TwWindowSize(w, h);
}

void Idle()
{
	glutPostRedisplay();
}
void TW_CALL set2dMode(void *)
{
	cameraController.set2dView();
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
		
		else if (keyTable['a'])
		{
			cameraController.Strafe(translationSpeed);
		}
		else if (keyTable['d'])
		{
			cameraController.Strafe(-translationSpeed);
		}
		else if (mouseLeftDown)
		{
			cameraController.Fly(-translationSpeed);
		}
		else if (mouseRightDown)
		{
			cameraController.Fly(translationSpeed);
		}
	}
	glutTimerFunc(1000 / 60, Timer, 0);
}
