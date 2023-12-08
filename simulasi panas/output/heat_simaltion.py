import numpy as np
import matplotlib.pyplot as plt

# Load data from CSV file
data = np.genfromtxt('/home/krisna/Documents/Semester 7/Pemodelan dan Simulasi/euler/simulasi panas/output/heat_simulation_results.csv', delimiter=',')

# Create a meshgrid for 2D plotting
x = np.arange(0, data.shape[0])
y = np.arange(0, data.shape[1])

X, Y = np.meshgrid(x, y)

# Create a 2D plot
plt.imshow(data, cmap='viridis', origin='lower', extent=[0, data.shape[0], 0, data.shape[1]])
plt.colorbar(label='Temperature')

# Customize plot
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('2D Temperature Distribution')

# Show the plot
plt.show()
