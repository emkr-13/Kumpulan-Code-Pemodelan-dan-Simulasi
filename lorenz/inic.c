#include <stdio.h>

int main() {
    double tmax = 25;  // waktu simulasi
    double dt = 1.0e-2; // setiap step, waktu bertambah 10 ^ -2 detik
    double t = 0;       // initial value untuk waktu, 0
    double s = 12, b = 2.6666, r = 28;

    // menentukan initial value dari posisi partikel pada sumbu x, y, dan z dari bidang
    double x[1000], y[1000], z[1000];
    x[0] = 1.0;
    y[0] = 1.0;
    z[0] = 1.0;

    double XV[3] = {x[0], y[0], z[0]};
    double K[3] = {0, 0, 0};

    // membuat variable i sebagai counter untuk mengakses komponen vector dengan indexnya
    int i = 0;

    // loop selama t belum melebihi tmax
    while (t <= tmax) {
        K[0] = s * (y[i] - x[i]);
        K[1] = x[i] * (r - z[i]) - y[i];
        K[2] = x[i] * y[i] - b * z[i];
        
        for (int j = 0; j < 3; j++) {
            XV[j] = XV[j] + dt * K[j];
        }

        // mengambil posisi dari partikel setelah dilakukan metode runge-kutta
        x[i + 1] = XV[0];
        y[i + 1] = XV[1];
        z[i + 1] = XV[2];

        t = t + dt;
        i = i + 1;

        printf("time = %8.3f ; x = %8.3f ; y = %8.3f; z = %8.3f\n", t, x[i], y[i], z[i]);

        // membentuk grafis 3 dimensi (plot3) sebagai bidang yang dilalui oleh partikel
        printf("3D Plot: x = %8.3f ; y = %8.3f ; z = %8.3f\n", x[i], y[i], z[i]);
        // Include code for 3D plotting in C (graphics libraries such as OpenGL or other)
    }

    // menampilkan grafis hasil simulasi pergerakan partikel
    printf("2D Plot: x, y, z\n");
    // Include code for 2D plotting in C (graphics libraries such as OpenGL or other)

    return 0;
}
