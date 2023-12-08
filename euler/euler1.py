import numpy as np
import matplotlib.pyplot as plt
tmax = 60  # waktu simulasi
dt = 1.0e-2  # setiap step, waktu bertambah 10 ^ -2 detik
t = 0  # initial value untuk waktu, 0
s, b, r = 12, 2.6666, 28

x = np.zeros(tmax * int(1/dt) + 1)
y = np.zeros(tmax * int(1/dt) + 1)
z = np.zeros(tmax * int(1/dt) + 1)

x[0] = 1.0
y[0] = 1.0
z[0] = 1.0
XV = np.array([x[0], y[0], z[0]])
K = np.zeros(3)

# membuat variable i sebagai counter untuk mengakses komponen vector dengan indexnya
i = 0

# loop selama t belum melebihi tmax
while t <= tmax:
    K[0] = s * (y[i] - x[i])
    K[1] = x[i] * (r - z[i]) - y[i]
    K[2] = x[i] * y[i] - b * z[i]
    XV = XV + dt * K

    # mengambil posisi dari partikel setelah dilakukan metode runge-kutta
    x[i+1] = XV[0]
    y[i+1] = XV[1]
    z[i+1] = XV[2]

    t = t + dt
    i = i + 1
    print(f'time = {t:.3f} ; x = {x[i]:.3f} ; y = {y[i]:.3f}; z = {z[i]:.3f}')

    # membentuk grafis 3 dimensi (plot3) sebagai bidang yang dilalui oleh partikel
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    ax.plot(x[:i+1], y[:i+1], z[:i+1], 'r')
    ax.scatter(x[i], y[i], z[i], c='g', marker='o', s=50)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.set_xlim([-20, 30])
    ax.set_ylim([-60, 60])
    ax.set_zlim([1, 60])
    plt.pause(0.01)

# menampilkan grafis hasil simulasi pergerakan partikel
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.plot(x, y, z, 'bo-', markersize=1)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
plt.show()
