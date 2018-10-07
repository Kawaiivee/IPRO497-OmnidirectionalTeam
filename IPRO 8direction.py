#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  6 21:47:57 2018

@author: cara4lyfe
"""

from math import *
import sympy


# In[10]:


#input
xAxis = list(range(-128,129))
yAxis = list(range(-128,129))


# In[ ]:


#constants
maxSpeed = 100
#dic to store data
dic = {}
noPositive = 0
# In[84]:
tan(radians(45.5))
# In[84]:
#Advanced
noPositive = 0
n = 0
i = 0
for Fx in xAxis:
    for Fy in yAxis:
        #ratio of power:
        r = sqrt((Fx**2+Fy**2)/128**2)
        if Fx == 0:
            tang = 9999999 #when x = 0 tan is infi
        else:
            tang = abs(Fy/Fx)
        if (Fx**2+Fy**2<=128**2):
            if  tang >= tan(radians(67.5)) and Fy >= 0:
                #region 1
                dic[(Fx,Fy)]= (maxSpeed,maxSpeed,0)
            elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy >= 0 and Fx >= 0:
                #region 2
                dic[(Fx,Fy)]= (maxSpeed/sqrt(2),maxSpeed/sqrt(2),0)
            elif tang < tan(radians(22.5)) and Fx >= 0:
                #region 3
                dic[(Fx,Fy)]= (0,2*maxSpeed/sqrt(3),maxSpeed/sqrt(3))
            elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy < 0 and Fx >= 0:
                #region 4
                dic[(Fx,Fy)]= (0,2*maxSpeed/sqrt(6),(maxSpeed/sqrt(2)+maxSpeed/sqrt(6)))
            elif tang >= tan(radians(67.5)) and Fy < 0:
                #region 5
                dic[(Fx,Fy)]= (0,0,maxSpeed)
            elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy < 0 and Fx < 0:
                #region 6
                dic[(Fx,Fy)]= (2*maxSpeed/sqrt(6),0,(maxSpeed/sqrt(2)+maxSpeed/sqrt(6)))
            elif tang < tan(radians(22.5)) and Fx < 0:
                #region 7
                dic[(Fx,Fy)]= (2*maxSpeed/sqrt(3),0,maxSpeed/sqrt(3))
            elif tang < tan(radians(67.5)) and tang >= tan(radians(22.5)) and Fy >= 0 and Fx < 0:
                #region 8
                dic[(Fx,Fy)]= (maxSpeed/sqrt(2),maxSpeed/sqrt(2),0)
            else:
                print(Fx,Fy)
                i = i+1
            print(n)
            n = n+1
        print("misshit: ", i)
print(n)
print("Done")

# In[84]:
f = open('IPRO8directiondata.txt','w')
for key in dic:
    f.write("%i, %i\n" % (key[0], key[1]))
    f.write("%f, %f, %f\n" % (dic[key][0], dic[key][1], dic[key][2]))
f.write('EOF')
f.close()
# In[84]:
f = open('IPRO8directiondataOneLineRounded.txt','w')
for key in dic:
    f.write("%i,%i,%i,%i,%i\n" % (key[0], key[1],dic[key][0], dic[key][1], dic[key][2]))
f.write('EOF')
f.close()