#include <GL/glut.h>

float waterPositionX = 0.0f; // Initial position of water

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw inverted glass
    glColor3f(0.8f, 0.8f, 1.0f); // Light blue color for glass
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.7f, 0.0f);
    glVertex2f(0.3f, 0.0f);
    glEnd();

    // Draw water
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for water
    glBegin(GL_POLYGON);
    glVertex2f(0.3f + waterPositionX, 0.7f);
    glVertex2f(0.7f + waterPositionX, 0.7f);
    glVertex2f(0.6f + waterPositionX, 0.1f);
    glVertex2f(0.4f + waterPositionX, 0.1f);
    glEnd();

    glutSwapBuffers();
}

void update(int /*value*/) {
    waterPositionX += 0.01f; // Move water to the right

    if (waterPositionX > 0.5f) {
        waterPositionX = -0.5f; // Reset position when reaching the right edge
    }

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, update, 0); // Schedule the next update
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Inverted Glass with Water Simulation");
    glutInitWindowSize(800, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0); // Set up the timer for updates

    glutMainLoop();
    return 0;
}
