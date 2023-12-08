#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Constants
const double roomSizeX = 10.0;  // room size along x-axis
const double roomSizeY = 10.0;  // room size along y-axis
const double roomSizeZ = 10.0;  // room size along z-axis
const double totalTime = 300.0; // total simulation time
const double deltaT = 1.0;      // time step
const double deltaX = 1.0;      // spatial step along each axis
const double alpha = 0.1;       // thermal diffusivity

// Function to initialize the temperature distribution in the room
void initializeRoom(std::vector<std::vector<std::vector<double>>>& room) {
    // Set initial temperature distribution (e.g., a hot spot in the center)
    int midX = room.size() / 2;
    int midY = room[0].size() / 2;
    int midZ = room[0][0].size() / 2;
    room[midX][midY][midZ] = 100.0; // Initial temperature at the hot spot
}

// Function to perform the heat simulation
void simulateHeat(std::vector<std::vector<std::vector<double>>>& room) {
    int steps = static_cast<int>(totalTime / deltaT);

    // Perform time-stepping
    for (int step = 0; step < steps; ++step) {
        // Update temperature in the room using the 3D heat equation
        for (size_t i = 1; i < room.size() - 1; ++i) {
            for (size_t j = 1; j < room[i].size() - 1; ++j) {
                for (size_t k = 1; k < room[i][j].size() - 1; ++k) {
                    double laplacian = (room[i + 1][j][k] - 2 * room[i][j][k] + room[i - 1][j][k]) / (deltaX * deltaX) +
                                       (room[i][j + 1][k] - 2 * room[i][j][k] + room[i][j - 1][k]) / (deltaX * deltaX) +
                                       (room[i][j][k + 1] - 2 * room[i][j][k] + room[i][j][k - 1]) / (deltaX * deltaX);
                    room[i][j][k] += alpha * laplacian * deltaT;
                }
            }
        }
    }
}

// Function to save the temperature distribution to a CSV file
void saveToCSV(const std::vector<std::vector<std::vector<double>>>& room, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& slice : room) {
            for (const auto& row : slice) {
                for (double temperature : row) {
                    file << temperature << ",";
                }
                file << "\n";
            }
            file << "\n";
        }

        file.close();
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
}

int main() {
    // Calculate the number of grid points along each axis
    int numPointsX = static_cast<int>(roomSizeX / deltaX);
    int numPointsY = static_cast<int>(roomSizeY / deltaX);
    int numPointsZ = static_cast<int>(roomSizeZ / deltaX);

    // Initialize the room temperature distribution
    std::vector<std::vector<std::vector<double>>> room(numPointsX, std::vector<std::vector<double>>(numPointsY, std::vector<double>(numPointsZ, 0.0)));
    initializeRoom(room);

    // Perform heat simulation
    simulateHeat(room);

    // Save the results to a CSV file
    saveToCSV(room, "heat_simulation_results.csv");

    std::cout << "Simulation completed. Results saved to 'heat_simulation_results.csv'." << std::endl;

    return 0;
}
