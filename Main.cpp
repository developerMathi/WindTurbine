#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include "sstream"

using namespace std;


int refreshCount = 0; // intial refresh count, it will increase by one in every frame refresh
int speedFactor = 1; // to adjust the speed, need to read form settings.txt file


//Draw a windTurbine, consisting of a pole and three vanes. 

void drawWindTurbine() {

	// pole of the wind turbine
	glColor3f(0.61, 0.62, 0.63); // grey color
	glBegin(GL_POLYGON);
	glVertex2f(-0.05f, 0);
	glVertex2f(0.05f, 0);
	glVertex2f(0.05f, 3);
	glVertex2f(-0.05f, 3);
	glEnd();

	//basement of the wind turbine
	glColor3f(0.61, 0.62, 0.63); //grey color
	glBegin(GL_POLYGON);
	glVertex2f(-0.08f, 0.1f);
	glVertex2f(0.08f, 0.1f);
	glVertex2f(0.08f, 0);
	glVertex2f(-0.08f, 0);
	glEnd();



	glTranslatef(0, 3, 0); //  multiply the current matrix by a translation matrix set the correct position for the vanes 
	glRotated(refreshCount * speedFactor * (180.0 / 180.0), 0, 0, 1); // rotating animation refresh count and spped factor together affect the rotating speed
	glColor3f(0.38, 0.4, 0.42);// dark grey color
	for (int i = 0; i < 3; i++) { // loop for 3 vanes
		glRotated(120, 0, 0, 1);  // These rotations help to place the vanes like turbine. angles between acsent vanes are 120 degree
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0.3f, 0.2f);
		glVertex2f(1.4f, 0.1f);
		glVertex2f(1.5f, 0);
		glEnd();
	}

	glTranslatef(0, -3, 0); //  multiply the current matrix by a translation matrix, set back to intial position 


	// center circle of turbine
	int triangleAmount = 20; //# of triangles used to draw circle
	const double PI = 3.141592654;
	GLfloat radius = 0.12f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 3); // center of circle
	for (int j = 0; j <= triangleAmount; j++) {
		glVertex2f(
			0 + (radius * cos(j * twicePi / triangleAmount)),
			3 + (radius * sin(j * twicePi / triangleAmount))
		);
	}
	glEnd();
}

 //This function is called when the image needs to be redrawn.It is installed by main() as the glutDisplayFunc.It draws the current frame of the animation.
 void drawDisplay() {
	// Initial Settings
	glClear(GL_COLOR_BUFFER_BIT); // clear buffers to preset values
	glClearColor(0.36, 0.63, 0.95, 1); // Fills the scene with light blue.
	glLoadIdentity(); //replace the current matrix with the identity matrix

	//Add two wind turbines before add hills
	//wind turbine - 1
	glPushMatrix();  //push the current matrix stack
	glTranslated(2, 1.1, 0); // multiply the current matrix by a translation matrix - to set the position of the turbine
	glScaled(0.3, 0.3, 1); //the function to produces a general scaling along the x, y, and z axes - to set the size of the turbine
	drawWindTurbine(); // called the drawWindTurbine method to add a wind turbine 
	glPopMatrix(); // //pop the current matrix stack
	//wind turbine - 2
	glPushMatrix(); //push the current matrix stack
	glTranslated(6.2, 1, 0); // multiply the current matrix by a translation matrix
	glScaled(0.4, 0.4, 1); //the function to produces a general scaling along the x, y, and z axes
	drawWindTurbine(); // called the drawWindTurbine method to add a wind turbine 
	glPopMatrix(); // pop the current matrix stack

	// Draw three green triangles to form a ridge of hills in the background
	glColor3f(0.18, 0.42, 0.26);// color for mountains
	glBegin(GL_POLYGON); // 1st hill from left
	glVertex2f(-3, -2);
	glVertex2f(1.5f, 1.85f);
	glVertex2f(5, -1);
	glEnd();
	glBegin(GL_POLYGON); // 2nd hill from left
	glVertex2f(-3, -2);
	glVertex2f(3, 2.3f);
	glVertex2f(7, -1);
	glEnd();
	glBegin(GL_POLYGON); // 3rd hill from left
	glVertex2f(2, -1);
	glVertex2f(6, 1.4f);
	glVertex2f(10, -1);
	glEnd();

	// Draw a black rectangle to represent the road. 
	glColor3f(0, 0, 0); //black color
	glBegin(GL_POLYGON);
	glVertex2f(0, -0.4f);
	glVertex2f(7, -0.4f);
	glVertex2f(7, 0.4f);
	glVertex2f(0, 0.4f);
	glEnd();

	// Draw a brown rectangle to represent the land. 
	glColor3f(0.42, 0.18, 0.22);// brown color
	glBegin(GL_POLYGON);
	glVertex2f(0, -0.4f);
	glVertex2f(7, -0.4f);
	glVertex2f(7, -2);
	glVertex2f(0, -2);
	glEnd();

	// Draw a yellow line in the middle of the road
	glLineWidth(6);  // Set the line width to be 6 pixels.
	glColor3f(0.73, 0.75, 0.3); // yellow color
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(7, 0);
	glEnd();
	glLineWidth(1);  // Reset the line width to be 1 pixel.

	// draw dotted yellow lines in both two sides of road
	for (int j = 0; j <= 7; j += 2) { // created a loop to get x cordinates
		glLineWidth(6);  // Set the line width to be 6 pixels.
		glColor3f(0.73, 0.75, 0.3);//yellow color
		glBegin(GL_LINES); // line for one side
		glVertex2f(j, 0.3f);
		glVertex2f(j + 1, 0.3f);
		glEnd();
		glBegin(GL_LINES); // line for another side
		glVertex2f(j, -0.3f);
		glVertex2f(j + 1, -0.3f);
		glEnd();
		glLineWidth(1); // Reset the line width to be 1 pixel.
	}


	//Add two wind turbines after add hills
	//wind turbine - 1
	glPushMatrix(); //push the current matrix stack
	glTranslated(0.75, 1.1, 0); // multiply the current matrix by a translation matrix - to set the position of the turbine
	glScaled(0.6, 0.6, 1); //the function to produces a general scaling along the x, y, and z axes - to set the size of the turbine
	drawWindTurbine(); // called the drawWindTurbine method to add a wind turbine 
	glPopMatrix(); //pop the current matrix stack
	//wind turbine - 2
	glPushMatrix(); //push the current matrix stack
	glTranslated(3.7, 0.8, 0);  // multiply the current matrix by a translation matrix - to set the position of the turbine
	glScaled(0.7, 0.7, 1); //the function to produces a general scaling along the x, y, and z axes - to set the size of the turbine
	drawWindTurbine(); // called the drawWindTurbine method to add a wind turbine 
	glPopMatrix(); //pop the current matrix stack

	glutSwapBuffers(); //  swaps the buffers of the current window if double buffered.

}  // end display


// This function is set as the glutTimerFunc to drive the animation
void refreshFrame(int v) {
	//increace the frame count
	refreshCount++;
	//marks the current window as needing to be redisplayed
	glutPostRedisplay();
	//registers a timer callback to be triggered in a specified number of milliseconds (After 10 milSec refreshFrame function will be called againn).
	glutTimerFunc(10, refreshFrame, 0);
}

// This function is set as the glutTimerFunc to read the settings file
// it will get the second line from the settings file and update the speed factor
// error validation included (speed factor must be 0 to 10) 0-off 1-low speed 10-max speed
void readSpeedFactor(int v) {

	string line; // new variable for lines the setting file
	ifstream myfile("Settings.txt"); // init settings file to read the data
	string secondLine; // new variable for get 2nd line the setting file
	int lineNo = 0; // new variable for calculate line number
	if (myfile.is_open()) // open the file
	{
		while (getline(myfile, line)) // while end of the line, read one by one line.
		{
			lineNo++; // add 1 to line number 
			if (lineNo == 2) {
				secondLine = line; // if line number is 2, assign line to second line
			}
		}
		myfile.close();// close the file
		if (!secondLine.empty()) { // validate the second line -is empty or not
			int start = secondLine.find("-"); // find the index of "-" in the second line
			int end = secondLine.length(); // total length of the second line
			if (start > 0) {
				string sfStr = secondLine.substr(start + 1, end - start); // get the substring which contains the speed factor
				int result; // variable for speed factor
				try {
					result = std::stoi(sfStr); // convert string to int
				}
				catch(const std::invalid_argument& e){ 
					std::cerr << "Invalid number in the input strings.\n" << std::endl;// error when invalid string 
				}
				catch (const std::out_of_range& e) {
					std::cerr << "Number out of range in the input strings.\n" << std::endl;// error when int is out of range
				}

				if (0 <= result and result <= 10) {//speed factor must be 0 to 10
					//cout << result;
					speedFactor = result;
				}
				else {
					std::cerr << "Invalid input from settings file - Number not in the range\n"; //error msg - speed factor must be 0 to 10
				}
			}
			else {
				std::cerr << "Invalid input from settings file. cannot find '-' in the second line. speed factor must be after a '-'\n"; //error msg peed factor must be after a '-'
			}
		}
		else {
			std::cerr << "Invalid input from settings file. Empty second line\n"; // error msg as empty second line
		}
	}

	else std::cerr << "Unable to open Settings.txt file. please check the file location and Name.\n";// error in opening the file

	glutPostRedisplay(); //marks the current window as needing to be redisplayed

	//registers a timer callback to be triggered in a specified number of milliseconds (After 5 sec readSpeedFactor function will be called againn).
	// read the settings.txt file in every 5 seconds
	glutTimerFunc(5000, readSpeedFactor, 0);
}
/*
 * This method is called from main() to initialize OpenGL.
 */
void init() {
	glClearColor(0.5f, 0.5f, 1, 1);
	// The next three lines set up the coordinates system.
	glMatrixMode(GL_PROJECTION);// specify which matrix is the current matrix - matrix operations to the projection matrix stack
	glLoadIdentity();// load identity matrix
	glOrtho(0, 7, -1, 4, -1, 1); //multiply the current matrix with an orthographic matrix (x between 0 to 7, y between 4 to -1,distances to the nearer and farther depth clipping planes 1,-1)
	glMatrixMode(GL_MODELVIEW); // specify which matrix is the current matrix - matrix operations to the modelview matrix stack
} 


int main(int argc, char** argv) {
	//initialize the GLUT library
	glutInit(&argc, argv);

	//sets the initial display mode. GLUT_DOUBLE-double buffered window
	glutInitDisplayMode(GLUT_DOUBLE);

	//set the initial window position and size respectively
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 500);

	//creates a top-level window
	glutCreateWindow("Wind turbine _ Mathivathanan");

	// to initialize openGl
	init();

	//sets the display callback for the current window - (function drawDisplay)
	glutDisplayFunc(drawDisplay);

	//registers a timer callback to be triggered in a specified number of milliseconds.- to refresh frame
	glutTimerFunc(100, refreshFrame, 0);

	//registers a timer callback to be triggered in a specified number of milliseconds. - to read settings.txt file
	glutTimerFunc(5000, readSpeedFactor, 0);

	//enters the GLUT event processing loop
	glutMainLoop();

	return 0;
}
