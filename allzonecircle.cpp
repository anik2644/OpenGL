/*
Circle with 8 regions without printing table
*/
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int slices = 16;
static int stacks = 16;
#define LINE_COUNT 10
#define Height 512
#define Width 512
int lineCoords[LINE_COUNT][4];

int generateRandX()
{
  return (rand() % Width) - Width / 2;
}

int generateRandY()
{
  return (rand() % Height) - Height / 2;
}

void generateLines()
{
  for (int i = 0; i < LINE_COUNT; i++)
  {
    lineCoords[i][0] = generateRandX();
    lineCoords[i][1] = generateRandY();
    lineCoords[i][2] = generateRandX();
    lineCoords[i][3] = generateRandY();
  }
}

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
  if (dx >= 0 and dy >= 0)
  {
    if (dx >= dy)
    {
      printf("GREEN\n");
      return 0;
    }
    else
    {
      printf("SKYBLUE\n");
      return 1;
    }
  }
  else if (dx < 0 and dy >= 0)
  {
    if (-dx >= dy)
    {
      printf("YELLOW\n");
      return 3;
    }
    else
    {
      printf("PURPLE\n");
      return 2;
    }
  }
  else if (dx < 0 and dy < 0)
  {
    if (-dx >= -dy)
    {
      printf("RED\n");
      return 4;
    }
    else
    {
      printf("BLUE\n");
      return 5;
    }
  }
  else
  {
    if (dx >= -dy)
    {
      printf("PINK\n");
      return 7;
    }
    else
    {
      printf("WHITE\n");
      return 6;
    }
  }
}

void drawPixel(int x, int y)
{
  glVertex2i(x, y);
}

int centre_x, centre_y, radius, region;

void draw8way(int x, int y)
{
  drawPixel(x + centre_x, y + centre_y);
  drawPixel(y + centre_x, x + centre_y);
  drawPixel(-y + centre_x, x + centre_y);
  drawPixel(-x + centre_x, y + centre_y);
  drawPixel(-x + centre_x, -y + centre_y);
  drawPixel(-y + centre_x, -x + centre_y);
  drawPixel(y + centre_x, -x + centre_y);
  drawPixel(x + centre_x, -y + centre_y);
}

void drawCircle0(int r)
{
  int x = r, y = 0;
  int d = 5 - 4 * r;
  draw8way(x, y);
  while (x >= y)
  {
    if (d <= 0)
    {
      d += (2 * y + 3) * 4; // north
      y++;
    }
    else
    {
      d += (2 * y - 2 * x + 5) * 4; // north-west
      x--;
      y++;
    }
    draw8way(x, y);
  }
}

void drawCircle1(int r)
{
  int x = 0, y = r;
  int d = 5 - 4 * r;
  draw8way(x, y);
  while (x < y)
  {
    if (d < 0)
    {
      d += (2 * x + 3) * 4; // east
      x++;
    }
    else
    {
      d += (2 * x - 2 * y + 5) * 4; // south-east
      x++;
      y--;
    }
    draw8way(x, y);
  }
}

void drawCircle2(int r)
{
  int x = 0, y = r;
  int d = 5 - 4 * r;
  draw8way(x, y);
  while (-x < y)
  {
    if (d < 0)
    {
      d += (3 - 2 * x) * 4; // west
      x--;
    }
    else
    {
      d += (-2 * x + 5 - 2 * y) * 4; // south-west
      x--;
      y--;
    }
    draw8way(x, y);
  }
}

void drawCircle3(int r)
{
  int x = -r, y = 0;
  int d = 5 - 4 * r;
  draw8way(x, y);
  while (abs(y) < abs(x))
  {
    if (d < 0)
    {
      d += (2 * y + 3) * 4; // north
      y++;
    }
    else
    {
      d += (2 * x + 2 * y + 5) * 4; // north-east
      x++;
      y++;
    }
    draw8way(x, y);
  }
}

void drawCircle4(int r)
{
  int x = -r, y = 0;
  int d = 5 - 4 * r;
  draw8way(x, y);
  while (abs(y) < abs(x))
  {
    printf("%d %d\n", x, y);
    if (d < 0)
    {
      d += (-2 * y + 3) * 4; // south
      y--;
    }
    else
    {
      d += (-2 * y + 2 * x + 5) * 4; // south-east
      x++;
      y--;
    }
    draw8way(x, y);
  }
}

void drawCircle5(int r)
{
  int x = 0, y = -r;
  int d = 5 - 4 * r;

  draw8way(x, y);
  while (abs(x) < abs(y))
  {
    if (d < 0)
    {
      d += (-2 * x + 3) * 4; // west
      x--;
    }
    else
    {
      d += (-2 * x + 2 * y + 5) * 4; // north-west
      x--;
      y++;
    }
    draw8way(x, y);
  }
}

void drawCircle6(int r)
{
  int x = 0, y = -r;
  int d = 5 + 4 * r;
  draw8way(x, y);
  while (x < -y)
  {
    if (d < 0)
    {
      d += (2 * x + 3) * 4; // E
      x++;
    }
    else
    {
      d += (2 * x + 2 * y + 5) * 4; // NE
      x++;
      y++;
    }
    draw8way(x, y);
  }
}

void drawCircle7(int r)
{
  int x = r, y = 0;
  int d = 5 - 4 * r;
  draw8way(x, y);
  while (-y < x)
  {
    if (d < 0)
    {
      d += (-2 * y + 3) * 4; // S
      y--;
    }
    else
    {
      d += (-2 * x + 5 - 2 * y) * 4; // SW
      x--;
      y--;
    }
    draw8way(x, y);
  }
}

void drawCircle(int rad, int reg)
{
  switch (reg)
  {
  case 0:
    glColor3ub(255, 0, 0);
    drawCircle0(rad);
    break;
  case 1:
    glColor3ub(0, 255, 0);
    drawCircle1(rad);
    break;
  case 2:
    glColor3ub(0, 0, 255);
    drawCircle2(rad);
    break;
  case 3:
    glColor3ub(255, 0, 255);
    drawCircle3(rad);
    break;
  case 4:
    glColor3ub(255, 255, 0);
    drawCircle4(rad);
    break;
  case 5:
    glColor3ub(0, 255, 255);
    drawCircle5(rad);
    break;
  case 6:
    glColor3ub(255, 255, 255);
    drawCircle6(rad);
    break;
  case 7:
    glColor3ub(128, 128, 0);
    drawCircle7(rad);
    break;
  }
}

int x_0, x_1, y_0, y_1;

static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1, 1, 1);
  glBegin(GL_LINES);
  glVertex2i(-Width / 2, 0);
  glVertex2i(Width / 2 - 1, 0);
  glVertex2i(0, -Height / 2);
  glVertex2i(0, Height / 2 - 1);
  glEnd();

  glPointSize(2);
  glBegin(GL_POINTS);
  drawCircle4(radius);
  glEnd();

  glutSwapBuffers();
}

static void idle(void)
{
  glutPostRedisplay();
}

// Program entry point

int main(int argc, char *argv[])
{
  printf("Enter Center of Circle in following format: x y\n");
  scanf("%d %d", &centre_x, &centre_y);
  printf("Enter Radius of Circle:\n");
  scanf("%d", &radius);
  glutInit(&argc, argv);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(10, 10);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  generateLines();
  glutCreateWindow("Experiment 01");

  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutIdleFunc(idle);

  glutMainLoop();

  return EXIT_SUCCESS;
}

// g++ hello.cpp -o Draw8way -lglut -lGLU -lGL
