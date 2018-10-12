#!/usr/bin/python
from math import *
from tkinter import *
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
    if Fx == 0:
        tang = 9999999  # when x = 0 tan is infi
    else:
        tang = abs(Fy / Fx)
    if tang >= tan(radians(67.5)) and Fy >= 0:
        # region 1
        return (maxSpeed, maxSpeed, 0)
    elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy >= 0 and Fx >= 0:
        # region 2
        return (200/sqrt(3)*sin(radians(15)),100/sqrt(3)*sin(radians(15))+100*cos(radians(15)),0)
    elif tang < tan(radians(22.5)) and Fx >= 0:
        # region 3
        return (0, 2 * maxSpeed / sqrt(3), maxSpeed / sqrt(3))
    elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy < 0 and Fx >= 0:
        # region 4
        return (0, 2 * maxSpeed / sqrt(6), (maxSpeed / sqrt(2) + maxSpeed / sqrt(6)))
    elif tang > tan(radians(67.5)) and Fy < 0:
        # region 5
        return (0, 0, maxSpeed)
    elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy < 0 and Fx < 0:
        # region 6
        return (2 * maxSpeed / sqrt(6), 0, (maxSpeed / sqrt(2) + maxSpeed / sqrt(6)))
    elif tang < tan(radians(22.5)) and Fx < 0:
        # region 7
        return (2 * maxSpeed / sqrt(3), 0, maxSpeed / sqrt(3))
    elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy >= 0 and Fx < 0:
        # region 8
        return (100/sqrt(3)*sin(radians(15))+100*cos(radians(15)),200/sqrt(3)*sin(radians(15)),0)


#for x in range(0, 10):
for i in range(-128, 128):
    for j in range(-128, 128):
        if (i**2 + j**2 <= 128**2):
            aout, bout, cout = calc(i, j)
            c.coords(C, 128*multi, 128*multi, 128*multi, (128+cout)*multi)
            c.coords(A, 128*multi, 128*multi, (128-aout*sqrt(3)/2)*multi,(128-aout/2)*multi)
            c.coords(B, 128*multi, 128*multi, (128+bout*sqrt(3) / 2) * multi, (128 - bout / 2) * multi)
            if(i==0 and j==0):
               coe = 0
            else:
                coe = maxSpeed / sqrt(i ** 2 + j ** 2)
            print(coe, -(-128+i), -(-128+j))
            c.coords(Joined, 128 * multi, 128 * multi, (128+i)*multi, -(-128+j)*multi)
            gui.update()
            time.sleep(0.001)
gui.title("First title")
gui.mainloop()