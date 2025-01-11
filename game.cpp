//============================================================================
// Name        : Muhammad Anas Farooq / 21I-0813
// Author      : FAST CS Department
// Version     : My Version
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <fstream> //For File Handling
#include <string>
#include <ctime>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
int width = 1280, height = 940; // i have set my window size to be 800 x 600
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// User Created Functions
void random_passenger();
void passenger_pick(unsigned char key);
void passenger_drop(unsigned char key);
void passenger_collision(int key);
void obstacle_collision(int key);
void moving_car_collision(int key);
void building_collision(int key);
void random_placing();
void obstacle_placing_check(int &x, int &y);
void overwrite(int &x, int &y);
void menu();
void menu_2();
void display_score();
void write_score();

// For Timer
int seconds = 0;
int minutes = 0;
int stored_num = 0; // Using it to check how many persons data is in the leader board file

int xI = 10, yI = 820;
string user_name;
int score = 0; // For Incrementing or Decrementig the Score.
int obs_S_dec; // Different for red and yellow car.
int car_S_dec;
int speed;		   // How many pixels the car move in desire position.
int exit_menu = 0; // A Flag for displaying menu.
int arr[16];

int A = 6;			 // Global Var for random placing of passengers
int *p = new int[A]; // Global pointer for manipulating the number of passengers
int he, ho;			 // 2 variables to randomnly place the passengers desired location.

// For the random cars.
int moving_car_timer = 0;
int a = 336, b = 175;
bool flag_1 = true;
int c = 82, d = 10;
bool flag_2 = true;
int e = 530, f = 10;
bool flag_3 = true;
int g = 980, h = 400;
bool flag_4 = true;

void moving_car1();
void moving_car2();
void moving_car3();
void moving_car4();

int color; // Global Var for the changing of color
void drawCar()
{
	DrawSquare(xI, yI, 30, colors[color]);
	glutPostRedisplay();
}

// void moveCar()
// {

// 	if (xI > 10 && flag)
// 	{
// 		xI -= 10;
// 		cout << "going left";
// 		if (xI < 100)

// 			flag = false;
// 	}
// 	else if (xI < 1010 && !flag)
// 	{
// 		cout << "go right";
// 		xI += 10;
// 		if (xI > 900)
// 			flag = true;
// 	}
// }
/*
 * Canvas drawing function.
 * */

void GameDisplay() /**/
{

	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(255 /*Red Component*/, 255,					 // 148.0/255/*Green Component*/,
				 255 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);								 // Update the colors

	if (exit_menu == 0)
	{
		menu();
	}

	if (exit_menu == 1)
	{
		menu_2();
	}

	if (exit_menu == 2)
	{
		//   Borders
		//   DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		DrawLine(0, 0, 0, 940, 10, colors[BLUE]);
		DrawLine(0, 860, 1280, 860, 10, colors[BLUE]);
		DrawLine(1280, 0, 1280, 940, 10, colors[BLUE]);
		DrawLine(0, 0, 1280, 0, 10, colors[BLUE]);
		DrawLine(0, 936, 1280, 936, 10, colors[BLUE]);

		// Roads
		//  DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		int j = 64;
		for (int i = 0; i < 19; i++)
		{
			DrawLine(j, 0, j, 860, 1, colors[BLACK]);
			j += 64;
		}

		// Buildings
		// DrawRectangle(int x1, int y1, int x2, int y2, float *color)
		DrawRectangle(128, 700, 192, 50, colors[LIGHT_BLUE]);
		DrawRectangle(576, 700, 702, 50, colors[LIGHT_BLUE]);
		DrawRectangle(128, 550, 128, 45, colors[LIGHT_BLUE]);
		DrawRectangle(192, 450, 64, 110, colors[LIGHT_BLUE]);
		DrawRectangle(128, 200, 128, 150, colors[LIGHT_BLUE]);
		DrawRectangle(320, 550, 320, 45, colors[LIGHT_BLUE]);
		DrawRectangle(448, 350, 64, 210, colors[LIGHT_BLUE]);
		DrawRectangle(320, 120, 192, 50, colors[LIGHT_BLUE]);
		DrawRectangle(704, 5, 64, 140, colors[LIGHT_BLUE]);
		DrawRectangle(960, 150, 64, 210, colors[LIGHT_BLUE]);
		DrawRectangle(960, 350, 315, 50, colors[LIGHT_BLUE]);
		DrawRectangle(1152, 500, 64, 150, colors[LIGHT_BLUE]);
		DrawRectangle(768, 400, 64, 250, colors[LIGHT_BLUE]);
		DrawRectangle(832, 500, 128, 50, colors[LIGHT_BLUE]);
		DrawRectangle(640, 250, 192, 50, colors[LIGHT_BLUE]);
		DrawRectangle(1152, 50, 64, 150, colors[LIGHT_BLUE]);

		// Random obstacles
		DrawRectangle(arr[0], arr[1], 32, 40, colors[BLACK]);
		DrawRectangle(arr[2], arr[3], 32, 40, colors[BLACK]);
		DrawRectangle(arr[4], arr[5], 32, 40, colors[BLACK]);
		DrawRectangle(arr[6], arr[7], 32, 40, colors[BLACK]);

		// Random Trees
		DrawCircle(arr[8], arr[9], 15, colors[GREEN]);
		DrawRectangle((arr[8] - 4), (arr[9] - 32), 10, 20, colors[BROWN]);

		DrawCircle(arr[10], arr[11], 15, colors[GREEN]);
		DrawRectangle((arr[10] - 4), (arr[11] - 32), 10, 20, colors[BROWN]);

		DrawCircle(arr[12], arr[13], 15, colors[GREEN]);
		DrawRectangle((arr[12] - 4), (arr[13] - 32), 10, 20, colors[BROWN]);

		DrawCircle(arr[14], arr[15], 15, colors[GREEN]);
		DrawRectangle((arr[14] - 4), (arr[15] - 32), 10, 20, colors[BROWN]);

		// Display Score
		DrawString(10, 890, "Score = " + to_string(score), colors[DARK_BLUE]);

		// Displat Present Coordinates
		DrawString(1130, 890, "X " + to_string(xI) + "  " + "Y " + to_string(yI), colors[BLACK]);

		// Display Timer
		DrawString(520, 890, to_string(minutes) + "   MIN" + "  " + to_string(seconds) + "   SEC", colors[BLACK]);

		// Random Passengers
		DrawCircle(*(p + 0), *(p + 1), 10, colors[MAGENTA]);
		DrawCircle(*(p + 2), *(p + 3), 10, colors[MAGENTA]);
		DrawCircle(*(p + 4), *(p + 5), 10, colors[MAGENTA]);
		if (A == 8)
			DrawCircle(*(p + 6), *(p + 7), 10, colors[MAGENTA]);

		// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		// DrawTriangle(300, 450, 340, 450, 320, 490, colors[MISTY_ROSE]);

		// DrawCircle(50, 670, 10, colors[RED]);
		// DrawCircle(70, 670, 10, colors[RED]);
		// DrawCircle(90, 670, 10, colors[RED]);
		// DrawRoundRect(500, 200, 50, 100, colors[DARK_SEA_GREEN], 70);
		// DrawRoundRect(100, 200, 100, 50, colors[DARK_OLIVE_GREEN], 20);
		// DrawRoundRect(100, 100, 50, 100, colors[DARK_OLIVE_GREEN], 30);
		// DrawRoundRect(200, 100, 100, 50, colors[LIME_GREEN], 40);
		// DrawRoundRect(350, 100, 100, 50, colors[LIME_GREEN], 20);
		drawCar();

		// moving_cars[0] = 328;
		// moving_cars[1] = 175;

		DrawRectangle(a, b, 32, 40, colors[BROWN]);
		if (moving_car_timer >= 2)
			DrawRectangle(c, d, 32, 40, colors[BROWN]);

		if (moving_car_timer >= 4)
			DrawRectangle(e, f, 32, 40, colors[BROWN]);

		if (moving_car_timer >= 6)
			DrawRectangle(g, h, 32, 40, colors[BROWN]);

		// For Random dropping positions
		if ((*(p + 0) == 1500) and (*(p + 1) = 1500))
		{
			DrawRectangle(he, ho, 32, 40, colors[HOT_PINK]);
		}

		if ((*(p + 2) == 1500) and (*(p + 3) = 1500))
		{
			DrawRectangle(he, ho, 32, 40, colors[HOT_PINK]);
		}

		if ((*(p + 4) == 1500) and (*(p + 5) = 1500))
		{
			DrawRectangle(he, ho, 32, 40, colors[HOT_PINK]);
		}

		if (A == 8)
		{
			if ((*(p + 6) == 1500) and (*(p + 7) = 1500))
			{
				DrawRectangle(he, ho, 32, 40, colors[HOT_PINK]);
			}
		}

		glutSwapBuffers();
	}

	// do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{

	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		// what to do when left key is pressed...
		xI -= speed;
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
		xI += speed;
	}
	else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
		yI += speed;
	}

	else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
		yI -= speed;
	}

	// For Not Letting the Car Move Out of the Boundaries.
	if (xI <= 2 and key == GLUT_KEY_LEFT)
	{
		xI += speed;
	}
	else if (xI >= 1250 and key == GLUT_KEY_RIGHT)
	{
		xI -= speed;
	}
	else if (yI >= 830 and key == GLUT_KEY_UP)
	{
		yI -= speed;
	}
	else if (yI <= 7 and key == GLUT_KEY_DOWN)
	{
		yI += speed;
	}
	moving_car_collision(key);
	obstacle_collision(key);
	building_collision(key);
	passenger_collision(key);

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{

	if (key == 27 /* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}

	if (exit_menu == 1)
	{
		if (key == 48) // gets executed when 0 is pressed
		{
			color = ((rand() % 139) + 1); // For Random color ((0-138) + 1)
			obs_S_dec = 2;
			car_S_dec = 2;
			speed = 14;
			exit_menu = 2;
		}

		if (key == 49) // gets executed when 2 is pressed
		{
			color = 5; // For Red Color
			obs_S_dec = 2;
			car_S_dec = 3;
			speed = 12;
			exit_menu = 2;
		}

		if (key == 50) // gets executed when 3 is pressed
		{
			color = 23; // For Yellow Color
			obs_S_dec = 4;
			car_S_dec = 2;
			speed = 16;
			exit_menu = 2;
		}
	}

	if (exit_menu == 0)
	{
		if (key == 49)
		{
			exit_menu = 1;
		}
		if (key == 50)
		{
			exit_menu = 3;
			display_score();
		}
	}

	passenger_pick(key);

	if (key == 'b' || key == 'B') // Key for placing the bomb
	{
		// do something if b is pressed
		cout << "b pressed" << endl;
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{

	// implement your functionality here
	// moveCar();
	moving_car1();
	if (moving_car_timer >= 2)
		moving_car2();
	if (moving_car_timer >= 4)
		moving_car3();
	if (moving_car_timer >= 6)
		moving_car4();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100, Timer, 0);
}
void Timmar(int n)
{

	if (exit_menu == 2)
		seconds++;

	if ((seconds == 60))

	{
		minutes++;
		seconds = 0;
	}

	if ((minutes < 3) and (score >= 100))

		write_score();

	if ((minutes == 3) and (score < 100))

		write_score();

	glutTimerFunc(1000.0, Timmar, 0); // 1000 milliseconds = 1 second
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */

void MousePressedAndMoved(int x, int y)
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

void MouseMoved(int x, int y)
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		cout << "Right Button Pressed" << endl;
	}

	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{
	srand((unsigned int)time(0)); // time(0) returns number of seconds elapsed since January 1, 1970.
	cout << "Enter Your Name:\n";
	getline(cin, user_name);

	int extra = rand() % 2; // A check to generate specific number of passengers on the board.
	if (extra == 0)
	{
		A = 8;
	}
	random_placing();
	random_passenger();

	for (int i = 0, j = 1; i == 16; i += 2, j += 2)
	{
		overwrite(arr[i], arr[j]);
	}

	// InitRandomizer();								  // seed the random number generator...
	glutInit(&argc, argv);						  // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50);				  // set the initial position of our window
	glutInitWindowSize(width, height);			  // set the size of our window
	glutCreateWindow("Rush Hour by Anas Farooq"); // set the title of our game window
	SetCanvasSize(width, height);				  // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	// glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutDisplayFunc(GameDisplay);	   // tell library which function to call for drawing Canvas.
	glutKeyboardFunc(PrintableKeys);   // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(1000.0, Timmar, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);	  // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();

	return 1;
}
#endif /* RushHour_CPP_ */

void random_passenger()
{
	*(p + 0) = (rand() % 1200) + 50; // 50-1250
	*(p + 1) = (rand() % 750) + 50;	 // 50-800
	obstacle_placing_check(*(p + 0), *(p + 1));
	overwrite(*(p + 0), *(p + 1));

	*(p + 2) = (rand() % 1200) + 50;
	*(p + 3) = (rand() % 750) + 50;
	obstacle_placing_check(*(p + 2), *(p + 3));
	overwrite(*(p + 2), *(p + 3));

	*(p + 4) = (rand() % 1200) + 50;
	*(p + 5) = (rand() % 750) + 50;
	obstacle_placing_check(*(p + 4), *(p + 5));
	overwrite(*(p + 4), *(p + 5));

	if (A == 8)
	{
		*(p + 6) = (rand() % 1200) + 50;
		*(p + 7) = (rand() % 750) + 50;
		obstacle_placing_check(*(p + 6), *(p + 7));
		overwrite(*(p + 6), *(p + 7));
	}
}

void passenger_pick(unsigned char key)
{
	if (((xI >= *(p + 0) - 35) and xI <= (*(p + 0) + 8)) and ((yI >= *(p + 1) - 42) and yI <= (*(p + 1) + 8)))
	{
		if (key == 32)
		{
			*(p + 0) = 1500;
			*(p + 1) = 1500;
			he = (rand() % 1200) + 50;
			ho = (rand() % 750) + 50;
			obstacle_placing_check(he, ho);
			overwrite(he, ho);
		}
	}

	if (((xI >= *(p + 2) - 35) and xI <= (*(p + 2) + 8)) and ((yI >= *(p + 3) - 42) and yI <= (*(p + 3) + 8)))
	{
		if (key == 32)
		{
			*(p + 2) = 1500;
			*(p + 3) = 1500;
			he = (rand() % 1200) + 50;
			ho = (rand() % 750) + 50;
			obstacle_placing_check(he, ho);
			overwrite(he, ho);
		}
	}

	if (((xI >= *(p + 4) - 35) and xI <= (*(p + 4) + 8)) and ((yI >= *(p + 5) - 42) and yI <= (*(p + 5) + 8)))
	{
		if (key == 32)
		{
			*(p + 4) = 1500;
			*(p + 5) = 1500;
			he = (rand() % 1200) + 50;
			ho = (rand() % 750) + 50;
			obstacle_placing_check(he, ho);
			overwrite(he, ho);
		}
	}

	if (A == 8)
	{
		if (((xI >= *(p + 6) - 35) and xI <= (*(p + 6) + 8)) and ((yI >= *(p + 7) - 42) and yI <= (*(p + 7) + 8)))
		{
			if (key == 32)
			{
				*(p + 6) = 1500;
				*(p + 7) = 1500;
				he = (rand() % 1200) + 50;
				ho = (rand() % 750) + 50;
				obstacle_placing_check(he, ho);
				overwrite(he, ho);
			}
		}
	}
	passenger_drop(key);
}

void passenger_drop(unsigned char key)
{

	if (((xI >= he - 22) and xI <= (he + 32)) and ((yI >= ho - 18) and yI <= (ho + 38)))
	{
		if (key == 32)
		{
			he = 1500;
			ho = 1500;
			score += 10;

			if ((*(p + 0) == 1500) and (*(p + 1) = 1500))
			{
				*(p + 0) = (rand() % 1200) + 50; // 50-1250
				*(p + 1) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 0), *(p + 1));
				overwrite(*(p + 0), *(p + 1));
			}

			if ((*(p + 2) == 1500) and (*(p + 3) = 1500))
			{
				*(p + 2) = (rand() % 1200) + 50; // 50-1250
				*(p + 3) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 2), *(p + 3));
				overwrite(*(p + 2), *(p + 3));
			}

			if ((*(p + 4) == 1500) and (*(p + 5) = 1500))
			{
				*(p + 4) = (rand() % 1200) + 50; // 50-1250
				*(p + 5) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 4), *(p + 5));
				overwrite(*(p + 4), *(p + 5));
			}

			if (A == 8)
			{
				if ((*(p + 6) == 1500) and (*(p + 7) = 1500))
				{
					*(p + 6) = (rand() % 1200) + 50; // 50-1250
					*(p + 7) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 6), *(p + 7));
					overwrite(*(p + 6), *(p + 7));
				}
			}
			moving_car_timer++;
		}
	}
}

void moving_car1()
{
	if (b >= 175 and flag_1)
	{
		b += 6;
		if (b > 482)

			flag_1 = false;
	}
	else if (b < 490 and !flag_1)
	{
		b -= 6;
		if (b <= 175)
			flag_1 = true;
	}
}

void moving_car2()
{
	if (d >= 10 and flag_2)
	{
		d += 10;
		if (d > 790)

			flag_2 = false;
	}
	else if (d < 810 and !flag_2)
	{
		d -= 10;
		if (d <= 10)
			flag_2 = true;
	}
}

void moving_car3()
{
	if (f >= 10 and flag_3)
	{
		f += 6;
		if (f > 482)

			flag_3 = false;
	}
	else if (f < 490 and !flag_3)
	{
		f -= 6;
		if (f <= 10)
			flag_3 = true;
	}
}

void moving_car4()
{
	if (h >= 400 and flag_4)
	{
		h += 6;
		if (h > 630)

			flag_4 = false;
	}
	else if (h < 640 and !flag_4)
	{
		h -= 6;
		if (h <= 400)
			flag_4 = true;
	}
}

void passenger_collision(int key)
{

	if ((*(p + 0) == 1500) and (*(p + 1) = 1500))
	{ // Ps 1 is picked up and car is in the vicinity of Ps 2
		if (((xI >= *(p + 2) - 35) and xI <= (*(p + 2) + 8)) and ((yI >= *(p + 3) - 42) and yI <= (*(p + 3) + 8)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
			{
				*(p + 2) = (rand() % 1200) + 50; // 50-1250
				*(p + 3) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 2), *(p + 3));
				score = score - 5;
			}
		}

		// Ps 1 is picked up and car is in the vicinity of Ps 3
		if (((xI >= *(p + 4) - 35) and xI <= (*(p + 4) + 8)) and ((yI >= *(p + 5) - 42) and yI <= (*(p + 5) + 8)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
			{
				*(p + 4) = (rand() % 1200) + 50; // 50-1250
				*(p + 5) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 4), *(p + 5));
				score = score - 5;
			}
		}

		// Ps 1 is picked up and car is in the vicinity of Ps 4
		if (A == 8)
		{
			if (((xI >= *(p + 6) - 35) and xI <= (*(p + 6) + 8)) and ((yI >= *(p + 7) - 42) and yI <= (*(p + 7) + 8)))
			{
				if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				{
					*(p + 6) = (rand() % 1200) + 50; // 50-1250
					*(p + 7) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 6), *(p + 7));
					score = score - 5;
				}
			}
		}
	}

	if ((*(p + 2) == 1500) and (*(p + 3) = 1500))
	{
		// Ps 2 is picked up and car is in the vicinity of Ps 1
		if (((xI >= *(p + 0) - 35) and xI <= (*(p + 0) + 8)) and ((yI >= *(p + 1) - 42) and yI <= (*(p + 1) + 8)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
			{
				*(p + 0) = (rand() % 1200) + 50; // 50-1250
				*(p + 1) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 0), *(p + 1));
				score = score - 5;
			}
		}

		// Ps 2 is picked up and car is in the vicinity of Ps 3
		if (((xI >= *(p + 4) - 35) and xI <= (*(p + 4) + 8)) and ((yI >= *(p + 5) - 42) and yI <= (*(p + 5) + 8)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
			{
				*(p + 4) = (rand() % 1200) + 50; // 50-1250
				*(p + 5) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 4), *(p + 5));
				score = score - 5;
			}
		}

		// Ps 2 is picked up and car is in the vicinity of Ps 4
		if (A == 8)
		{
			if (((xI >= *(p + 6) - 35) and xI <= (*(p + 6) + 8)) and ((yI >= *(p + 7) - 42) and yI <= (*(p + 7) + 8)))
			{
				if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				{
					*(p + 6) = (rand() % 1200) + 50; // 50-1250
					*(p + 7) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 6), *(p + 7));
					score = score - 5;
				}
			}
		}
	}

	if ((*(p + 4) == 1500) and (*(p + 5) = 1500))
	{
		// Ps 3 is picked up and car is in the vicinity of Ps 1
		if (((xI >= *(p + 0) - 35) and xI <= (*(p + 0) + 8)) and ((yI >= *(p + 1) - 42) and yI <= (*(p + 1) + 8)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
			{
				*(p + 0) = (rand() % 1200) + 50; // 50-1250
				*(p + 1) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 0), *(p + 1));
				score = score - 5;
			}
		}

		// Ps 3 is picked up and car is in the vicinity of Ps 2
		if (((xI >= *(p + 2) - 35) and xI <= (*(p + 2) + 8)) and ((yI >= *(p + 3) - 42) and yI <= (*(p + 3) + 8)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))

			{
				*(p + 2) = (rand() % 1200) + 50; // 50-1250
				*(p + 3) = (rand() % 750) + 50;	 // 50-800
				obstacle_placing_check(*(p + 2), *(p + 3));
				score = score - 5;
			}
		}

		// Ps 3 is picked up and car is in the vicinity of Ps 4
		if (A == 8)
		{
			if (((xI >= *(p + 6) - 35) and xI <= (*(p + 6) + 8)) and ((yI >= *(p + 7) - 42) and yI <= (*(p + 7) + 8)))
			{
				if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))

				{
					*(p + 6) = (rand() % 1200) + 50; // 50-1250
					*(p + 7) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 6), *(p + 7));
					score = score - 5;
				}
			}
		}
	}

	if (A == 8)
	{
		if ((*(p + 6) == 1500) and (*(p + 7) = 1500))
		{
			// Ps 4 is picked up and car is in the vicinity of Ps 1
			if (((xI >= *(p + 0) - 35) and xI <= (*(p + 0) + 8)) and ((yI >= *(p + 1) - 42) and yI <= (*(p + 1) + 8)))
			{
				if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				{
					*(p + 0) = (rand() % 1200) + 50; // 50-1250
					*(p + 1) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 0), *(p + 1));
					score = score - 5;
				}
			}

			// Ps 4 is picked up and car is in the vicinity of Ps 2
			if (((xI >= *(p + 2) - 35) and xI <= (*(p + 2) + 8)) and ((yI >= *(p + 3) - 42) and yI <= (*(p + 3) + 8)))
			{
				if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))

				{
					*(p + 2) = (rand() % 1200) + 50; // 50-1250
					*(p + 3) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 2), *(p + 3));
					score = score - 5;
				}
			}

			// Ps 4 is picked up and car is in the vicinity of Ps 3
			if (((xI >= *(p + 4) - 35) and xI <= (*(p + 4) + 8)) and ((yI >= *(p + 5) - 42) and yI <= (*(p + 5) + 8)))
			{
				if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				{
					*(p + 4) = (rand() % 1200) + 50; // 50-1250
					*(p + 5) = (rand() % 750) + 50;	 // 50-800
					obstacle_placing_check(*(p + 4), *(p + 5));
					score = score - 5;
				}
			}
		}
	}
}

void obstacle_collision(int key)
{
	// For Obstacles (Boxes)
	if (((xI >= arr[0] - 25) and xI <= (arr[0] + 30)) and ((yI >= arr[1] - 20) and yI <= (arr[1] + 36)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}

	if (((xI >= arr[2] - 20) and xI <= (arr[2] + 25)) and ((yI >= arr[3] - 20) and yI <= (arr[3] + 34)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}

	if (((xI >= arr[4] - 22) and xI <= (arr[4] + 30)) and ((yI >= arr[5] - 20) and yI <= (arr[5] + 36)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}

	if (((xI >= arr[6] - 25) and xI <= (arr[6] + 26)) and ((yI >= arr[7] - 24) and yI <= (arr[7] + 36)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}
	// For Trees
	if (((xI >= arr[8] - 45) and xI <= (arr[8] + 16)) and ((yI >= arr[9] - 52) and yI <= (arr[9] + 12)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}
	if (((xI >= arr[10] - 45) and xI <= (arr[10] + 16)) and ((yI >= arr[11] - 52) and yI <= (arr[11] + 12)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}
	if (((xI >= arr[12] - 45) and xI <= (arr[12] + 16)) and ((yI >= arr[13] - 52) and yI <= (arr[13] + 12)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}
	if (((xI >= arr[14] - 45) and xI <= (arr[14] + 16)) and ((yI >= arr[15] - 52) and yI <= (arr[15] + 12)))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
		score -= obs_S_dec;
	}
}

void moving_car_collision(int key)
{
	if (((xI >= a - 35) and xI <= (a + 50)) and ((yI >= b - 20) and yI <= (b + 36)))
	{
		if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
			score -= car_S_dec;
	}
	if (moving_car_timer >= 2)
	{
		if (((xI >= c - 35) and xI <= (c + 50)) and ((yI >= d - 20) and yI <= (d + 36)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				score -= car_S_dec;
		}
	}
	if (moving_car_timer >= 4)
	{
		if (((xI >= e - 35) and xI <= (e + 50)) and ((yI >= f - 20) and yI <= (f + 36)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				score -= car_S_dec;
		}
	}
	if (moving_car_timer >= 6)
	{
		if (((xI >= g - 35) and xI <= (g + 50)) and ((yI >= h - 20) and yI <= (h + 36)))
		{
			if ((key == GLUT_KEY_UP) or (key == GLUT_KEY_DOWN) or (key == GLUT_KEY_RIGHT) or (key == GLUT_KEY_LEFT))
				score -= car_S_dec;
		}
	}
}

void building_collision(int key)
{

	// Put it into a function name building collision check.
	// For Not Letting the Car Move into the Buildings.
	// Block 1
	if ((xI >= 100 and xI <= 320) and (yI >= 670 and yI <= 740))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 2
	if ((xI >= 548 and xI <= 1280) and (yI >= 680 and yI <= 740))
	{
		// No need of left key bcz there is boundary on left
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 3a
	if ((xI >= 100 and xI <= 256) and (yI >= 525 and yI <= 580))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 3b
	if ((xI >= 164 and xI <= 256) and (yI >= 420 and yI <= 530))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
	}
	// Block 4
	if ((xI >= 100 and xI <= 256) and (yI >= 175 and yI <= 350))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 5a
	if ((xI >= 292 and xI <= 640) and (yI >= 525 and yI <= 595))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 5b
	if ((xI >= 420 and xI <= 510) and (yI >= 320 and yI <= 530))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
	}
	// Block 6
	if ((xI >= 292 and xI <= 512) and (yI >= 90 and yI <= 170))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 7
	if ((xI >= 676 and xI <= 768) and (yI >= 0 and yI <= 140))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 8
	if ((xI >= 930 and xI <= 1024) and (yI >= 130 and yI <= 340))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 9
	if ((xI >= 930 and xI <= 1250) and (yI >= 330 and yI <= 390))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 10
	if ((xI >= 1124 and xI <= 1216) and (yI >= 470 and yI <= 650))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 11
	if ((xI >= 740 and xI <= 832) and (yI >= 370 and yI <= 650))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 12
	if ((xI >= 804 and xI <= 960) and (yI >= 470 and yI <= 550))
	{
		if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block 13
	if ((xI >= 610 and xI <= 832) and (yI >= 220 and yI <= 300))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
	// Block speed
	if ((xI >= 1124 and xI <= 1216) and (yI >= 25 and yI <= 200))
	{
		if (key == GLUT_KEY_RIGHT)
			xI -= speed;
		else if (key == GLUT_KEY_LEFT)
			xI += speed;
		else if (key == GLUT_KEY_UP)
			yI -= speed;
		else if (key == GLUT_KEY_DOWN)
			yI += speed;
	}
}

void random_placing()
{

	arr[0] = (rand() % 1200) + 50; // 50-1250
	arr[1] = (rand() % 750) + 50;  // 50-800
	obstacle_placing_check(arr[0], arr[1]);

	arr[2] = (rand() % 1200) + 50;
	arr[3] = (rand() % 750) + 50;
	obstacle_placing_check(arr[2], arr[3]);

	arr[4] = (rand() % 1200) + 50;
	arr[5] = (rand() % 750) + 50;
	obstacle_placing_check(arr[4], arr[5]);

	arr[6] = (rand() % 1200) + 50;
	arr[7] = (rand() % 750) + 50;
	obstacle_placing_check(arr[6], arr[7]);

	arr[8] = (rand() % 1200) + 50;
	arr[9] = (rand() % 750) + 50;
	obstacle_placing_check(arr[8], arr[9]);

	arr[10] = (rand() % 1200) + 50;
	arr[11] = (rand() % 750) + 50;
	obstacle_placing_check(arr[10], arr[11]);

	arr[12] = (rand() % 1200) + 50;
	arr[13] = (rand() % 750) + 50;
	obstacle_placing_check(arr[12], arr[13]);

	arr[14] = (rand() % 1200) + 50;
	arr[15] = (rand() % 750) + 50;
	obstacle_placing_check(arr[14], arr[15]);
}

void obstacle_placing_check(int &x, int &y)
{

	// For Moving Cars
	if ((x >= 280 and x < 410) and (y >= 175 and y <= 482))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}

	if ((x >= 50 and x < 126) and (y >= 10 and y <= 810))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}

	if ((x >= 470 and x < 600) and (y >= 10 and y <= 482))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 920 and x < 1050) and (y >= 400 and y <= 640))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}

	//	For walls
	if ((x >= 60 and x <= 330) and (y >= 620 and y <= 780))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 500 and x <= 1280) and (y >= 620 and y <= 780))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}

	if ((x >= 60 and x <= 266) and (y >= 470 and y <= 640))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 124 and x <= 266) and (y >= 370 and y <= 540))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 60 and x <= 266) and (y >= 110 and y <= 400))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 244 and x <= 650) and (y >= 465 and y <= 650))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 380 and x <= 520) and (y >= 260 and y <= 580))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 252 and x <= 522) and (y >= 30 and y <= 220))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 636 and x <= 778) and (y >= 0 and y <= 190))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 890 and x <= 1034) and (y >= 70 and y <= 390))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 890 and x <= 1280) and (y >= 270 and y <= 440))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 1084 and x <= 1280) and (y >= 410 and y <= 700))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 700 and x <= 842) and (y >= 310 and y <= 700))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 764 and x <= 970) and (y >= 410 and y <= 600))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 570 and x <= 842) and (y >= 160 and y <= 350))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
	if ((x >= 1084 and x <= 1280) and (y >= 0 and y <= 250))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
	}
}

void overwrite(int &x, int &y)
{
	// For Blocks
	if (((x >= arr[0] - 60) and x <= (arr[0] + 60)) and ((y >= arr[1] - 60) and y <= (arr[1] + 80)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	if (((x >= arr[2] - 60) and x <= (arr[2] + 60)) and ((y >= arr[3] - 60) and y <= (arr[3] + 80)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	if (((x >= arr[4] - 60) and x <= (arr[4] + 60)) and ((y >= arr[5] - 60) and y <= (arr[5] + 80)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	if (((x >= arr[6] - 60) and x <= (arr[6] + 60)) and ((y >= arr[7] - 60) and y <= (arr[7] + 80)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	// For Trees
	if (((x >= arr[8] - 60) and x <= (arr[8] + 60)) and ((y >= arr[9] - 80) and y <= (arr[9] + 100)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	if (((x >= arr[10] - 60) and x <= (arr[10] + 60)) and ((y >= arr[11] - 80) and y <= (arr[11] + 100)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	if (((x >= arr[12] - 60) and x <= (arr[12] + 60)) and ((y >= arr[13] - 80) and y <= (arr[13] + 100)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
	if (((x >= arr[14] - 60) and x <= (arr[14] + 60)) and ((y >= arr[15] - 80) and y <= (arr[15] + 100)))
	{
		x = (rand() % 1200) + 50;
		y = (rand() % 750) + 50;
		obstacle_placing_check(x, y);
		overwrite(x, y);
	}
}

void menu()
{
	glClearColor(255 /*Red Component*/, 255,					 // 148.0/255/*Green Component*/,
				 255 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLine(0, 0, 0, 940, 10, colors[BLUE]);
	DrawLine(0, 860, 1280, 860, 10, colors[BLUE]);
	DrawLine(1280, 0, 1280, 940, 10, colors[BLUE]);
	DrawLine(0, 0, 1280, 0, 10, colors[BLUE]);
	DrawLine(0, 936, 1280, 936, 10, colors[BLUE]);

	DrawString(480, 890, "WELCOME TO RUSH HOUR.", colors[BLUE]);
	DrawString(560, 600, "Press 1 to Play.", colors[DEEP_SKY_BLUE]);
	DrawString(490, 520, "Press 2 to See the Leader Board.", colors[DEEP_SKY_BLUE]);
	DrawString(500, 440, "Press Escape to Exit any time.", colors[DEEP_SKY_BLUE]);

	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();
}

void menu_2()
{
	glClearColor(255 /*Red Component*/, 255,					 // 148.0/255/*Green Component*/,
				 255 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLine(0, 0, 0, 940, 10, colors[BLUE]);
	DrawLine(0, 860, 1280, 860, 10, colors[BLUE]);
	DrawLine(1280, 0, 1280, 940, 10, colors[BLUE]);
	DrawLine(0, 0, 1280, 0, 10, colors[BLUE]);
	DrawLine(0, 936, 1280, 936, 10, colors[BLUE]);

	DrawString(540, 890, "SELECTION.", colors[BLUE]);
	DrawString(495, 600, "Press 1 to choose Red taxi.", colors[DEEP_SKY_BLUE]);
	DrawString(495, 520, "Press 2 to choose Yellow taxi.", colors[DEEP_SKY_BLUE]);
	DrawString(490, 440, "Press 0 to choose Random taxi.", colors[(rand() % 139) + 1]);

	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();
}

void display_score()
{

	glClearColor(255 /*Red Component*/, 255,					 // 148.0/255/*Green Component*/,
				 255 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	DrawLine(0, 0, 0, 940, 10, colors[BLUE]);
	DrawLine(0, 860, 1280, 860, 10, colors[BLUE]);
	DrawLine(1280, 0, 1280, 940, 10, colors[BLUE]);
	DrawLine(0, 0, 1280, 0, 10, colors[BLUE]);
	DrawLine(0, 936, 1280, 936, 10, colors[BLUE]);

	DrawString(540, 890, "LEADER BOARD.", colors[BLUE]);
	DrawString(450, 800, "NAMES                          SCORES", colors[BLACK]);

	string name = "";
	int s = 0;
	int x_coor = 450, y_coor = 700;

	ofstream fout;
	ifstream fin;
	fin.open("leader_board.txt");
	// Finding out how many scores are stored in the file.

	if (fin)
	{
		while (!fin.eof())
		{
			getline(fin, name, ',');
			fin >> s;
			++stored_num;
		}
		fin.close();

		// Now we are storing them in a array.
		int arr_s[stored_num];
		string arr_n[stored_num];

		int i = 0;
		fin.open("leader_board.txt");
		while (!fin.eof())
		{
			getline(fin, arr_n[i], ',');
			fin >> arr_s[i];
			i++;
		}
		fin.close();

		int temp;
		string tump;
		for (i = 0; i < stored_num; i++)
		{
			for (int j = i + 1; j < stored_num; j++)
			{
				if (arr_s[i] < arr_s[j])
				{
					temp = arr_s[i];
					arr_s[i] = arr_s[j];
					arr_s[j] = temp;

					tump = arr_n[i];
					arr_n[i] = arr_n[j];
					arr_n[j] = tump;
				}
			}
		}

		for (int i = 0; i < stored_num; i++)
		{

			DrawString(x_coor, y_coor, arr_n[i] + "                                    " + to_string(arr_s[i]), colors[BLACK]);
			y_coor -= 50;
		}
	}

	else // when file will be opened for first time it will be empty
	{
		fout.open("leader_board.txt");
		fout.close();
	}

	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();
}

void write_score()
{
	string name = "";
	int s = 0;

	ofstream fout;
	ifstream fin;
	fin.open("leader_board.txt");
	// Finding out how many scores are stored in the file.
	if (fin)
	{
		while (!fin.eof())
		{
			getline(fin, name, ',');
			fin >> s;
			stored_num++;
		}
		fin.close();

		if (stored_num >= 0 and stored_num < 10)
		{
			fout.open("leader_board.txt", ios::app);
			if (fout)
			{
				if (name != "")
					fout << endl;
				fout << user_name << "," << score;
				fout.close();
			}
		}
		if (stored_num == 10) // Means stored scores are more than or equal to 10.
		{
			int arr_s[stored_num];
			string arr_n[stored_num];

			int i = 0;
			fin.open("leader_board.txt");
			while (!fin.eof())
			{
				getline(fin, arr_n[i], ',');
				fin >> arr_s[i];
				i++;
			}
			fin.close();

			// Finding smaller value
			int min = arr_s[0];
			for (int i = 0; i < stored_num; i++)
			{
				if (arr_s[i] < min)
				{
					min = arr_s[i];
				}
			}

			// Finding smaller element
			int element = 0;
			while (element < 10)
			{
				if (arr_s[element] == min)
				{
					break;
				}
				element++;
			}

			if (score >= min)
			{
				arr_s[element] = score;
				arr_n[element] = "\n" + user_name; // for a newline
			}
			// else score will be less than the stored elements which will be discarded.

			ofstream fout;
			fout.open("leader_board.txt");

			for (int i = 0; i < 10; i++)
			{
				fout << arr_n[i] << "," << arr_s[i];
			}
		}
	}
	else
	{
		// For creating file for the first time.
		fout.open("leader_board.txt");
		fout << user_name << "," << score;
		fout.close();
	}
	exit(1);
}