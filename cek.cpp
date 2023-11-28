#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Definisikan konstanta dan parameter simulasi
const double q = 1.0;   // Muatan partikel
const double m = 1.0;   // Massa partikel
const double dt = 0.01;  // Langkah waktu
const double waktu_akhir = 10.0;

// Model persamaan
std::vector<double> electricField(double t) {
    return {2.0, 3.0, 2.0 * t};
}

std::vector<double> magneticField(double t) {
    return {4.0, std::sin(2.0 * M_PI * t), 0.0};
}

// Metode Runge-Kutta orde-2
std::vector<double> rungeKuttaOrder2(std::vector<double> conditions, double t) {
    std::vector<double> k1, k2;

    // F = ma = qE + v x B
    std::vector<double> E = electricField(t);
    std::vector<double> B = magneticField(t);
    std::vector<double> F = {q * E[0] + conditions[3] * q * B[2] - conditions[5] * q * B[1],
                            q * E[1] - conditions[2] * q * B[2] + conditions[4] * q * B[0],
                            q * E[2] + conditions[2] * q * B[1] - conditions[3] * q * B[0]};

    // K1
    for (int i = 0; i < 6; ++i) {
        k1.push_back(dt * F[i] / m);
    }

    // Update kondisi dengan K1
    for (int i = 0; i < 3; ++i) {
        conditions[i] += conditions[i + 3] * dt + 0.5 * k1[i];
    }
    for (int i = 3; i < 6; ++i) {
        conditions[i] += k1[i];
    }

    // F = ma = qE + v x B (update dengan kondisi baru)
    E = electricField(t + dt);
    B = magneticField(t + dt);
    F = {q * E[0] + conditions[3] * q * B[2] - conditions[5] * q * B[1],
         q * E[1] - conditions[2] * q * B[2] + conditions[4] * q * B[0],
         q * E[2] + conditions[2] * q * B[1] - conditions[3] * q * B[0]};

    // K2
    for (int i = 0; i < 6; ++i) {
        k2.push_back(dt * F[i] / m);
    }

    // Update kondisi dengan K2
    for (int i = 0; i < 3; ++i) {
        conditions[i] += 0.5 * k2[i];
    }
    for (int i = 3; i < 6; ++i) {
        conditions[i] += 0.5 * k2[i];
    }

    return conditions;
}

int main() {
    // Inisialisasi
    double t = 0.0;
    std::vector<double> conditions = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    // Simulasi
    std::ofstream outputFile("trajectory.csv");
    while (t <= waktu_akhir) {
        outputFile << t << "," << conditions[0] << "," << conditions[1] << "," << conditions[2] << "\n";

        // Update kondisi menggunakan metode Runge-Kutta orde-2
        conditions = rungeKuttaOrder2(conditions, t);
        t += dt;
    }
    outputFile.close();

    std::cout << "Simulasi selesai. Hasil tersimpan dalam trajectory.csv" << std::endl;

    return 0;
}
