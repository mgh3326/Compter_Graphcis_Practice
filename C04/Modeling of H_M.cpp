#include<Windows.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<gl\glut.h>
#include<math.h>

static bool mouseLeftDown;
static float point[2][2];

static float theta;

GLUquadricObj* p;

void base(void)
{
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(p, 0.5, 0.5, 0.3, 20, 1);
	glPopMatrix();
}

void lower_arm(void)
{
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, 0.5, 0);
	glScalef(0.2, 1, 0.2);
	glutWireCube(1);
	glPopMatrix();
}

void upper_arm(void)
{
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glScalef(0.2, 0.8, 0.2);
	glutWireCube(1);
	glPopMatrix();
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);
	base();
	lower_arm();
	upper_arm();

	glutSwapBuffers();
}

void timer(int value)
{
	theta += 2.0;
	if (theta >= 360.0)
		theta -= 360.0;
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 1);
}

void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case VK_ESCAPE:
		gluDeleteQuadric(p);
		exit(0);
	}
}

void init(void)
{
	p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_LINE);
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void ChangeSize(int w, int h)
{
	if (h == 0)

		h = 1;


	glViewport(0, 0, w, h); //실제로 보이는 화면의 크기(윈도우창과 별개)


	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();


	if (w <= h)

	{
		glOrtho(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0 * (float)h / (float)w, -10.0, 10.0);
	}

	else

	{
		glOrtho(-2.0 * (float)w / (float)h, 2.0 * (float)w / (float)h, -2.0, 2.0, -10.0, 10.0);
	}


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (!mouseLeftDown)
			{
				double viewport[4];
				glGetDoublev(GL_VIEWPORT, viewport);

				point[0][0] = x / (float)viewport[2] * 500;
				point[0][1] = (viewport[3] - y) / (float)viewport[3] * 500;
				point[1][0] = point[0][0];
				point[1][1] = point[0][1];

				mouseLeftDown = true;
			}
		}
		else if (state == GLUT_UP)
		{
			if (mouseLeftDown)
			{
				mouseLeftDown = false;
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
		}
		else if (state == GLUT_UP)
		{
		}
	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	if (mouseLeftDown)
	{
		double viewport[4];
		glGetDoublev(GL_VIEWPORT, viewport);

		point[0][0] = x / (float)viewport[2] * 500;
		point[0][1] = (viewport[3] - y) / (float)viewport[3] * 500;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 디스플레이모드 설정
	glutInitWindowSize(500, 500);
	glutCreateWindow("Simple");
	glutInitWindowPosition(0, 0);

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
