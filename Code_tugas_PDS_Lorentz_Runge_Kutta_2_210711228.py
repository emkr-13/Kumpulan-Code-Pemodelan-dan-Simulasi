import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

sigma = 15 # 13 # 14
rho = 30 # 28 # 29
beta = 8/3 # 8/3 # 8/3
t = 0 
tf = 40 
h = 0.01 

def derivative(r,t):
    x = r[0]
    y = r[1]
    z = r[2]
    return np.array([sigma * (y - x), x * (rho - z) - y, (x * y) - (beta * z)])


time = np.array([]) #Empty time array to fill for the x-axis
x = np.array([]) #Empty array for x values
y = np.array([]) #Empty array for y values
z = np.array([]) #Empty array for z values
r = np.array([1.0, 1.0, 1.0]) #Initial conditions array

while (t <= tf ):
        time = np.append(time, t)
        z = np.append(z, r[2])
        y = np.append(y, r[1])
        x = np.append(x, r[0])
        k1 = derivative(r,t)
        k2 = derivative(r+k1*h/2,t+h/2)
        r = r + k2*h
        t = t + h



fig = plt.figure()
ax = plt.axes(projection='3d')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(-20,20)
ax.set_ylim(-20,20)
ax.set_zlim(0,50)
ax.plot3D(x,y,z)
plt.show()





fig = plt.figure()
ax = plt.axes(projection='3d')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(-20,20)
ax.set_ylim(-20,20)
ax.set_zlim(0,50)

line, = ax.plot([], [], [], lw=1)
def init():
    line.set_data([], [])
    line.set_3d_properties([])
    return line,

def animate(i):
    line.set_data(x[:i], y[:i])
    line.set_3d_properties(z[:i])
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=10000, interval=40, blit=True)
plt.show()

