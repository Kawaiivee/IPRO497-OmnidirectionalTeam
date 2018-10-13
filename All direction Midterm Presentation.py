#!/usr/bin/python
from math import *
from tkinter import *
import sympy
import time
gui = Tk()
var=IntVar()
multi = 5
gui.geometry("1280x1280")
c = Canvas(gui ,width=256*multi ,height=256*multi)
c.pack()
#max speed
maxSpeed = 100
#create lines
C = c.create_line(128*multi, 128*multi, 128*multi, (128+maxSpeed)*multi, fill="red", arrow = "last", width = "10", arrowshape = (80,100,30))
A = c.create_line(128*multi, 128*multi, (128-maxSpeed*sqrt(3)/2)*multi,(128-maxSpeed/2)*multi, fill="blue", arrow = "last", width = "10", arrowshape = (80,100,30))
B = c.create_line(128*multi, 128*multi, (128+maxSpeed*sqrt(3)/2)*multi,(128-maxSpeed/2)*multi, fill="yellow", arrow = "last", width = "10", arrowshape = (80,100,30))
Joined = c.create_line(128*multi, 128*multi, 0, 0, fill="black", arrow = "last", width = "10", arrowshape = (80,100,30))

def calc(Fx,Fy):
    # ratio of power:
    r = sqrt((Fx ** 2 + Fy ** 2) / 128 ** 2)
    if Fx == 0:
        tan = 9999999  # when x = 0 tan is infi
    else:
        tan = abs(Fy / Fx)
    if (Fx ** 2 + Fy ** 2 <= 128 ** 2):
        if tan > (1 / sqrt(3)) and Fy > 0:
            # Fc=0
            Fa, Fb = sympy.symbols("Fa Fb", real=True)
            eq1 = sympy.Eq((sqrt(3) * Fy - Fx) * Fb - (sqrt(3) * Fy + Fx) * Fa, 0)
            eq2 = sympy.Eq((0.5 * Fb + 0.5 * Fa) ** 2 + ((sqrt(3) / 2) * Fb - (sqrt(3) / 2) * Fa) ** 2,
                           (r * maxSpeed) ** 2)
            sol = sympy.solve([eq1, eq2])
            if sol[0][Fa] > 0 and sol[0][Fb] > 0:
                return (sol[0][Fa], sol[0][Fb], 0)
            elif sol[1][Fa] > 0 and sol[1][Fb] > 0:
                return (sol[1][Fa], sol[1][Fb], 0)
        elif Fx < 0:
            # Fb=0
            Fa, Fc = sympy.symbols("Fa Fc", real=True)
            eq1 = sympy.Eq((sqrt(3) * Fy + Fx) * Fa - (2 * Fx) * Fc, 0)
            eq2 = sympy.Eq((0.5 * Fa - Fc) ** 2 + (-(sqrt(3) / 2) * Fa) ** 2, (r * maxSpeed) ** 2)
            sol = sympy.solve([eq1, eq2])
            if sol[0][Fa] > 0 and sol[0][Fc] > 0:
                return (sol[0][Fa], 0, sol[0][Fc])
            elif sol[1][Fa] > 0 and sol[1][Fc] > 0:
                return (sol[1][Fa], 0, sol[1][Fc])
        elif Fx > 0:
            # Fa=0
            Fb, Fc = sympy.symbols("Fb Fc", real=True)
            eq1 = sympy.Eq(-(sqrt(3) * Fy + Fx) * Fb - (2 * Fx) * Fc, 0)
            eq2 = sympy.Eq((0.5 * Fb - Fc) ** 2 + ((sqrt(3) / 2) * Fb) ** 2, (r * maxSpeed) ** 2)
            sol = sympy.solve([eq1, eq2])
            if sol[0][Fc] > 0 and sol[0][Fb] > 0:
                return (0, sol[0][Fb], sol[0][Fc])
            elif sol[1][Fc] > 0 and sol[1][Fb] > 0:
                return (0, sol[1][Fb], sol[1][Fc])
        elif Fx == 0:
            # Fa=0 Fb=0
            Fc = sympy.symbols("Fc", real=True)
            eq = sympy.Eq((Fc) ** 2, (r * maxSpeed) ** 2)
            sol = sympy.solve(eq)
            if sol[0] > 0:
                return (0, 0, sol[0])
            elif sol[1] > 0:
                return (0, 0, sol[1])


#for x in range(0, 10):
for i in range(-128, 128):
    for j in range(-128, 128):
        if (i**2 + j**2 <= 128**2):
            aout, bout, cout = calc(i, j)
            c.coords(C, 128*multi, 128*multi, 128*multi, (128+cout)*multi)
            c.coords(A, 128*multi, 128*multi, (128-aout*sqrt(3)/2)*multi,(128-aout/2)*multi)
            c.coords(B, 128*multi, 128*multi, (128+bout*sqrt(3) / 2) * multi, (128 - bout / 2) * multi)
            c.coords(Joined, 128 * multi, 128 * multi, (128+i)*multi, -(-128+j)*multi)
            gui.update()
            #time.sleep(0.001)
gui.title("First title")
gui.mainloop()