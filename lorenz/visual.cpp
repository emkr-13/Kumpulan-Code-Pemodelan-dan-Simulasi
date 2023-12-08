#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

const double tmax = 25.0;
const double dt = 1.0e-2;
double t = 0.0;
double s = 12.0;
double b = 2.6666;
double r = 28.0;

// Initial values for particle positions on the x, y, and z axes
double x = 1.0;
double y = 1.0;
double z = 1.0;

vector<double> XV = {x, y, z};
vector<double> K = {0.0, 0.0, 0.0};

GLFWwindow* window;

void initializeOpenGL() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(800, 600, "Particle Movement Simulation", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
}

void drawParticle() {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    glVertex3f(x, y, z);
    glEnd();
}

void updateParticlePosition() {
    K[0] = s * (y - x);
    K[1] = x * (r - z) - y;
    K[2] = x * y - b * z;

    for (int j = 0; j < 3; j++) {
        XV[j] += dt * K[j];
    }

    x = XV[0];
    y = XV[1];
    z = XV[2];
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateParticlePosition();
    drawParticle();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main() {
    initializeOpenGL();

    while (!glfwWindowShouldClose(window) && t <= tmax) {
        renderScene();
        t += dt;
        cout << "time = " << t << " ; x = " << x << " ; y = " << y << " ; z = " << z << endl;
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
