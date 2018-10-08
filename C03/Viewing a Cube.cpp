#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<gl\glut.h>
#include<math.h>

static bool mouseLeftDown;
static float point[2][2];

static float theta;
void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glutSwapBuffers();
}
void timer(int value) {
	theta += 2.0;
	if (theta >= 360.0)
		theta -= 360.0;
	glutTimerFunc(10000 / 30, timer, 1);
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case  'q' | 'Q':
		exit(0); break;
	case VK_ESCAPE:
		exit(0); break;
	default:
		break;
	}
}
void init(void) {
	mouseLeftDown = false;
	point[0][0] = 0;
	point[0][1] = 0;
	point[1][0] = 0;
	point[1][1] = 0;

	theta = 0;
}
void SetupRC(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
void ChangeSize(int w, int h) {

	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		gluOrtho2D(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0 * (float)h / (float)w);
	}
	else {
		gluOrtho2D(-2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -2.0, 2.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			if (!mouseLeftDown) {
				double viewport[4];
				glGetDoublev(GL_VIEWPORT, viewport);

				point[0][0] = x / (float)viewport[2] * 500;
				point[0][1] = (viewport[3] - y) / (float)viewport[3] * 500;
				point[1][0] = point[0][0];
				point[1][1] = point[0][1];

				mouseLeftDown = true;
			}
		}
		else if (state == GLUT_UP) {
			if (mouseLeftDown) {
				mouseLeftDown = false;
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {

		}
		else if (state == GLUT_UP) {

		}
	}
	glutPostRedisplay();

}
void mouseMotion(int x, int y) {
	if (mouseLeftDown) {
		double viewport[4];
		glGetDoublev(GL_VIEWPORT, viewport);

		point[0][0] = x / (float)viewport[2] * 500;
		point[0][1] = (viewport[3] - y) / (float)viewport[3] * 500;

	}
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Simple");
	glutDisplayFunc(renderScene);

	glutReshapeFunc(ChangeSize);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(1000 / 30, timer, 1);
	glutKeyboardFunc(keyboard);
	init();
	SetupRC();
	glutMainLoop();
}