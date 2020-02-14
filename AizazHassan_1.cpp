/*********
   CTIS164 - Template Source Program
----------
STUDENT : Aizaz Hassan	
SECTION : 3
HOMEWORK: 1
----------
PROBLEMS: Only one character moves, characters can overlap
----------
ADDITIONAL FEATURES:
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define MAX 10 //maximum character that can be drawn
int mx, my; //position of mouse

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int maxCnt = 0; //counter of characters on screen
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

void drawBackground() //displays the background
{
	//sun
	glColor3f(1, 1, 0);
	circle(340, 240, 50);
	int x = 0;

	//road
	glColor3f(0.6, 0.6, 0);
	glRectf(-400, 150, 400, -300);
	glColor3f(0, 0, 0);
	for (int k = 0; k < 5; k++)
	{
		glRectf(-380 + x, 100, -270 + x, 70);
		x += 150;
	}
	x = 0;
	for (int k = 0; k < 5; k++)
	{
		glRectf(-380 + x, -100, -270 + x, -130);
		x += 150;
	}

	glColor3ub(8, 56, 246);
	x = 0;
	for (int k = 0; k < 5; k++) {
		circle(-300 + x, 200, 30);
		circle(-275 + x, 200, 30);
		circle(-240 + x, 200, 30);
		x += 150;
	}
}
void drawCharacter(int cx, int cy) //character information
{

	//face
	glColor3ub(219, 183, 64);
	circle(0 + cx, 0 + cy, 30);
	glColor3f(1, 1, 1);
	circle(13 + cx, 15 + cy, 5);
	circle(-13 + cx, 15 + cy, 5);
	glColor3f(0, 0, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(13 + cx, 14 + cy);
	glVertex2f(-13 + cx, 14 + cy);
	glEnd();
	glPointSize(1);
	glColor3ub(148, 116, 22);
	glBegin(GL_TRIANGLES);
	glVertex2f(-10 + cx, 5 + cy);
	glVertex2f(10 + cx, 5 + cy);
	glVertex2f(0 + cx, -8 + cy);
	glEnd();
	glColor3ub(213, 82, 17);
	glRectf(-20 + cx, -20 + cy, 20 + cx, -10 + cy);

	//body
	glColor3f(1, 0, 0);
	glRectf(-12 + cx, -30 + cy, 12 + cx, -70 + cy);

	//legs
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-12 + cx, -70 + cy);
	glVertex2f(-18 + cx, -110 + cy);
	glVertex2f(-10 + cx, -110 + cy);
	glVertex2f(1 + cx, -85 + cy);
	glVertex2f(8 + cx, -110 + cy);
	glVertex2f(16 + cx, -110 + cy);
	glVertex2f(11 + cx, -70 + cy);
	glEnd();

	//boots
	glColor3f(1, 0, 0);
	glRectf(-5 + cx, -110 + cy, -25 + cx, -115 + cy);
	glRectf(21 + cx, -110 + cy, 3 + cx, -115 + cy);

	//hands
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-12 + cx, -40 + cy);
	glVertex2f(-20 + cx, -65 + cy);
	glVertex2f(-18 + cx, -70 + cy);
	glVertex2f(-12 + cx, -50 + cy);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(12 + cx, -40 + cy);
	glVertex2f(20 + cx, -65 + cy);
	glVertex2f(18 + cx, -70 + cy);
	glVertex2f(12 + cx, -50 + cy);
	glEnd();

	//wrists
	glColor3ub(219, 183, 64);
	glRectf(-20 + cx, -65 + cy, -18 + cx, -70 + cy);
	glRectf(20 + cx, -65 + cy, 18 + cx, -70 + cy);

}
bool checkShape(int x1, int y1, int x2, int y2, int x, int y)
{
	if (x <= x1 && x >= x2 && y <= y1 && y >= y2)
		return true;
	else
		return false;
}
typedef struct {
	int x, y; //center of character
	bool move; //if the character is moving
}shape_t;


shape_t *shape; //for dynamic memory allocation

void writeName() //displays the name and ID
{
	glColor3ub(175, 185, 82);
	glRectf(-100, 300, 100, 250);
	glColor3f(0, 0, 0);
	vprint(-50, 285, GLUT_BITMAP_8_BY_13, "Aizaz Hassan");
	vprint(-35, 265, GLUT_BITMAP_8_BY_13, "21801429");
}

//
// To display onto window using OpenGL commands
//
void display() {
	//
	// clear window to black
	//
	glClearColor(0.267, 0.412, 0.98, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBackground(); //displays background on screen
	writeName();//writes the name and ID
	for (int k = 0; k < 10; k++)
	{
		drawCharacter((shape + k)->x, (shape + k)->y);
		glColor3f(0, 0, 0);
		vprint(((shape + k)->x - 5), ((shape + k)->y) - 55, GLUT_BITMAP_8_BY_13, "%d", k + 1); //to show the number of character
	}
	glColor3f(0, 0, 0);
	vprint(295, -280, GLUT_BITMAP_8_BY_13, "(%d %d)", mx, my);
	glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.


	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) //when left click is done on mouse, new character forms
	{


		((shape + maxCnt)->x) = x - winWidth / 2;
		((shape + maxCnt)->y) = winHeight / 2 - y;
		(shape + maxCnt)->move = false;
		maxCnt++;


	}
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) //when right click is done on mouse, character moves
	{

		if ((shape)->move == false)
			(shape)->move = true;
		else
			(shape)->move = false;


	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.

	mx = x - winWidth / 2; //the x coordinate of mouse
	my = winHeight / 2 - y; //the y coordinate of mouse

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.
	int k = 0;
	if (((shape + k)->move) == true) //to check if right click is done on mouse
	{
		((shape + k)->x)++; //moves the character horizontally
		if (((shape + k)->x) == 430) 
			((shape + k)->x) = -400; //to make the character reappear on disapperance on the other side
		k++;
	}
	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("CTIS 164 HomeWork 1");
	shape = (shape_t *)malloc(sizeof(shape_t) * 15);
	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}