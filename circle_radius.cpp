#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LINE_COUNT 360
#define Height 600
#define Width 800

int radius = 0;
int angleStep = 0;
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
        glColor3ub(255, 255, 255); // White
        break;
    case 1:
        glColor3ub(255, 0, 0); // Red
        break;
    case 2:
        glColor3ub(0, 255, 0); // Green
        break;
    case 3:
        glColor3ub(0, 0, 255); // Blue
        break;
    case 4:
        glColor3ub(255, 0, 255); // Magenta
        break;
    case 5:
        glColor3ub(0, 255, 255); // Cyan
        break;
    case 6:
        glColor3ub(255, 255, 0); // Yellow
        break;

    case 7:
        glColor3ub(255 / 2, 255 / 2, 255 / 2); // Gray
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
    glPointSize(1);
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
        float angle = i * angleStep * M_PI / 180.0; // Increment angle by angleStep for each line
        int zone = findZone(lineCoords[i][0], lineCoords[i][1], lineCoords[i][2], lineCoords[i][3]);
        lineCoords[i][2] = radius * cos(angle); // Update x2 coordinate based on new angle
        lineCoords[i][3] = radius * sin(angle); // Update y2 coordinate based on new angle
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

    printf("Radius: \n");
    scanf("%d", &radius);
    printf("Step: \n");
    scanf("%d", &angleStep);

    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Circle");

    for (int i = 0; i < LINE_COUNT; i++)
    {
        float angle = i * angleStep * M_PI / 180.0;
        lineCoords[i][0] = 0;
        lineCoords[i][1] = 0;
        lineCoords[i][2] = radius * cos(angle);
        lineCoords[i][3] = radius * sin(angle);
    }

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
