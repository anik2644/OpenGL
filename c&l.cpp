#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LINE_COUNT 360
#define radius 150
#define Height 600
#define Width 800

int lineCoords[LINE_COUNT][4];

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width / 2, Width / 2 - 1, -Height / 2, Height / 2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int findZone(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    if (dx >= 0 && dy >= 0)
    {
        if (dx >= dy)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if (dx < 0 && dy >= 0)
    {
        if (-dx >= dy)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }
    else if (dx < 0 && dy < 0)
    {
        if (-dx >= -dy)
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
    else
    {
        if (dx >= -dy)
        {
            return 7;
        }
        else
        {
            return 6;
        }
    }
}

void drawPixel(int x, int y, int zone)
{
    switch (zone)
    {
    case 0:
        glColor3f(1.0, 0.0, 0.0); // Red
        break;
    case 1:
        glColor3f(0.0, 1.0, 0.0); // Green
        break;
    case 2:
        glColor3f(0.0, 0.0, 1.0); // Blue
        break;
    case 3:
        glColor3f(1.0, 1.0, 0.0); // Yellow
        break;
    case 4:
        glColor3f(1.0, 0.0, 1.0); // Magenta
        break;
    case 5:
        glColor3f(0.0, 1.0, 1.0); // Cyan
        break;
    case 6:
        glColor3f(1.0, 1.0, 1.0); // White
        break;
    case 7:
        glColor3f(0.5, 0.5, 0.5); // Gray
        break;
    }
    glVertex2i(x, y);
}

void drawLine(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float increment_x = dx / (float)steps;
    float increment_y = dy / (float)steps;
    float x = x0, y = y0;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        drawPixel(round(x), round(y), zone);
        x += increment_x;
        y += increment_y;
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < LINE_COUNT; i++)
    {
        int zone = findZone(lineCoords[i][0], lineCoords[i][1], lineCoords[i][2], lineCoords[i][3]);
        drawLine(lineCoords[i][0], lineCoords[i][1], lineCoords[i][2], lineCoords[i][3], zone);
    }
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{

    int r, step;
    printf("Radius: \n");
    scanf("%d", &r);
    printf("Step: \n");
    scanf("%d", &step);

    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Experiment 01");

    int ran = 360 / step;

    for (int i = 0; i < step; i++)
    {
        float angle = i * step * M_PI / 180.0;
        lineCoords[i][0] = 0;
        lineCoords[i][1] = 0;
        lineCoords[i][2] = r * cos(angle);
        lineCoords[i][3] = r * sin(angle);
    }
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
