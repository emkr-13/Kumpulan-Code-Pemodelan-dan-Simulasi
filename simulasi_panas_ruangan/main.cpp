#include <iostream>
#include <GL/glut.h>

const int GRID_SIZE = 50;
const float ROOM_SIZE = 10.0f;
const float CELL_SIZE = ROOM_SIZE / GRID_SIZE;
const float THERMAL_DIFFUSIVITY = 0.1f;

float temperature[GRID_SIZE][GRID_SIZE];

void initializeTemperature() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            temperature[i][j] = 0.0f;
        }
    }

    // Initial heat source in the center
    int center_i = GRID_SIZE / 2;
    int center_j = GRID_SIZE / 2;
    temperature[center_i][center_j] = 100.0f;
}

void updateTemperature() {
    float newTemperature[GRID_SIZE][GRID_SIZE];

    for (int i = 1; i < GRID_SIZE - 1; ++i) {
        for (int j = 1; j < GRID_SIZE - 1; ++j) {
            float laplacian = (temperature[i + 1][j] + temperature[i - 1][j]
                + temperature[i][j + 1] + temperature[i][j - 1] - 4 * temperature[i][j])
                / (CELL_SIZE * CELL_SIZE);

            newTemperature[i][j] = temperature[i][j] + THERMAL_DIFFUSIVITY * laplacian;
        }
    }

    // Update the temperature array
    for (int i = 1; i < GRID_SIZE - 1; ++i) {
        for (int j = 1; j < GRID_SIZE - 1; ++j) {
            temperature[i][j] = newTemperature[i][j];
        }
    }
}

void drawRoom() {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-ROOM_SIZE / 2, -ROOM_SIZE / 2);
    glVertex2f(ROOM_SIZE / 2, -ROOM_SIZE / 2);
    glVertex2f(ROOM_SIZE / 2, ROOM_SIZE / 2);
    glVertex2f(-ROOM_SIZE / 2, ROOM_SIZE / 2);
    glEnd();
}

void drawHeatDistribution() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            float x = -ROOM_SIZE / 2 + i * CELL_SIZE;
            float y = -ROOM_SIZE / 2 + j * CELL_SIZE;
            float z = temperature[i][j];

            glColor3f(1.0f - z / 100.0f, 0.0f, z / 100.0f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + CELL_SIZE, y);
            glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
            glVertex2f(x, y + CELL_SIZE);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawRoom();
    drawHeatDistribution();

    glutSwapBuffers();
}

void update(int value) {
    updateTemperature();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 frames per second
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Heat Distribution Simulation");
    glutFullScreen();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-ROOM_SIZE / 2, ROOM_SIZE / 2, -ROOM_SIZE / 2, ROOM_SIZE / 2);
    glMatrixMode(GL_MODELVIEW);

    initializeTemperature();

    glutMainLoop();

    return 0;
}
