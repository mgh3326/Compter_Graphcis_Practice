#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<gl\glut.h>
#include<iostream>
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);
	{
		glColor3f(1, 0, 0);
		glVertex2f(-50, -50);
		glColor3f(0, 1, 0);
		glVertex2f(0, -50);
		glColor3f(0, 0, 1);

		glVertex2f(0, 0);
		glColor3f(0, 0, 0);

		glVertex2f(-50, 0);
	}
	glEnd();
	glFlush();
}
void SetupRC(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
void ChangeSize(int w, int h) {
	GLfloat aspectRatio;

	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;

	float windowWidth, windowHeight;
	if (w <= h) {
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
	}
	else {
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
	}
	glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0, -1.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("My first OpenGL program!");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
}