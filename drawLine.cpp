#include <GL/glut.h>

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    drawLine(-0.5, 0.0, 1.5, 0.0);  // Draw a horizontal line
    
    glColor3f(0.0, 1.0, 0.0); // Set color to green
    drawLine(0.0, -0.5, 0.0, 0.5);  // Draw a vertical line

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Draw Lines Example");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
