#include <iostream>
#include <cmath>
#include <vector>

int main() {
    double tmax = 25.0; // simulation time
    double dt = 1.0e-2; // time step
    double t = 0.0; // initial time
    double s = 12.0, b = 2.6666, r = 28.0;

    // initial values for particle position in the x, y, and z axes
    double x = 1.0;
    double y = 1.0;
    double z = 1.0;

    std::vector<double> XV{ x, y, z };
    std::vector<double> K(3, 0.0);

    int i = 0;

    while (t <= tmax) {
        K[0] = s * (y - x);
        K[1] = x * (r - z) - y;
        K[2] = x * y - b * z;

        for (int j = 0; j < 3; ++j) {
            XV[j] = XV[j] + dt * K[j];
        }

        x = XV[0];
        y = XV[1];
        z = XV[2];

        t = t + dt;
        i = i + 1;

        std::cout << "time = " << t << " ; x = " << x << " ; y = " << y << " ; z = " << z << "\n";

        // visualization in 3D space
        // (Assuming you have a function `plot3` for visualization)
        // plot3(x, y, z, 'r', x, y, z, 'bo', 'MarkerEdgeColor', 'k', 'MarkerFaceColor', 'g', 'MarkerSize', 8);
        // grid on; box on; view(30, 20);
        // xlim([-20, 30]); ylim([-60, 60]); zlim([1, 60]);
        // xlabel('x'); ylabel('y'); zlabel('z'); pause(0.01);
    }

    // visualization of particle movement
    // (Assuming you have a function `plot3` for visualization)
    // plot3(x, y, z, 'bo-', 'MarkerEdgeColor', 'k', 'MarkerFaceColor', 'g', 'MarkerSize', 1);
    // box on; xlabel('x'); ylabel('y'); zlabel('z');
    // view(30, 20);

    return 0;
}
