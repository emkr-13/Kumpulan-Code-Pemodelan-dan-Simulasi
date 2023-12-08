import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Baca data dari file CSV
data = np.genfromtxt('/home/krisna/Documents/Semester 7/Pemodelan dan Simulasi/euler/output/trajectory.csv', delimiter=',')

# Pisahkan data
t = data[:, 0]
x = data[:, 1]
y = data[:, 2]
z = data[:, 3]

# Visualisasi
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z, label='Lintasan Partikel Bermuatan')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Lintasan Partikel Bermuatan')

plt.show()