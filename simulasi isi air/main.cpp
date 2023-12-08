#include <GL/glut.h>

float waterLevel = 0.0f; // Initial water level

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
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.7f, 0.7f);
    glVertex2f(0.7f, 0.7f - waterLevel);
    glVertex2f(0.3f, 0.7f - waterLevel);
    glEnd();

    glutSwapBuffers();
}

void update(int /*value*/) {
    waterLevel += 0.005f; // Increase water level

    if (waterLevel > 0.7f) {
        waterLevel = 0.7f; // Limit water level to the top of the glass
    }

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, update, 0); // Schedule the next update
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Upside-Down Glass with Water Simulation");
    glutInitWindowSize(800, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0); // Set up the timer for updates

    glutMainLoop();
    return 0;
}
