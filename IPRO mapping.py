
# coding: utf-8

# In[36]:


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

# In[24]:


atan(1/1)


# In[77]:


Fa, Fb = sympy.symbols("Fa Fb", real=True)
Fx = 0
Fy = 128
eq1 = sympy.Eq((Fy-sqrt(3)*Fx)*Fb-(Fy+sqrt(3)*Fx)*Fa, 0)
eq2 = sympy.Eq(((sqrt(3)/2)*Fb+(sqrt(3)/2)*Fa)**2+(0.5*Fb-0.5*Fa)**2, 10000)
sol=sympy.solve([eq1, eq2])
if sol[0][Fa] >0 and sol[0][Fb]>0:
    print("yes")
elif sol[1][Fa] >0 and sol[1][Fb]>0:
    print("haha")

# In[83]:

n = 0
for Fx in xAxis:
    for Fy in yAxis:
        #ratio of power:
        r = sqrt((Fx**2+Fy**2)/128**2)
        #on the edge
        if (Fx**2+Fy**2<128**2 and Fx**2+Fy**2>126**2):
            if Fy>64 and Fx>(-64*sqrt(3)) and Fx<(64*sqrt(3)):
                #Fc=0
                Fa, Fb = sympy.symbols("Fa Fb", real=True)
                eq1 = sympy.Eq((sqrt(3)*Fy-Fx)*Fb-(sqrt(3)*Fy+Fx)*Fa, 0)
                eq2 = sympy.Eq((0.5*Fb+0.5*Fa)**2+((sqrt(3)/2)*Fb-(sqrt(3)/2)*Fa)**2, maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fa] >0 and sol[0][Fb]>0:
                    dic[(Fx,Fy)]= (sol[0][Fa],sol[0][Fb],0)
                elif sol[1][Fa] >0 and sol[1][Fb]>0:
                    dic[(Fx,Fy)]= (sol[1][Fa],sol[1][Fb],0)
                else:
                    noPositive = noPositive+1
            if Fy<64 and Fx>-128 and Fx<0:
                #Fb=0
                Fa, Fc = sympy.symbols("Fa Fc", real=True)
                eq1 = sympy.Eq((sqrt(3)*Fy+Fx)*Fa-(2*Fx)*Fc, 0)
                eq2 = sympy.Eq((0.5*Fa-Fc)**2+(-(sqrt(3)/2)*Fa)**2, maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fa] >0 and sol[0][Fc]>0:
                    dic[(Fx,Fy)]= (sol[0][Fa],0,sol[0][Fc])
                elif sol[1][Fa] >0 and sol[1][Fc]>0:
                    dic[(Fx,Fy)]= (sol[1][Fa],0,sol[1][Fc])
                else:
                    noPositive = noPositive+1
            if Fy<64 and Fx>0 and Fx<128:
                #Fa=0
                Fb, Fc = sympy.symbols("Fb Fc", real=True)
                eq1 = sympy.Eq(-(sqrt(3)*Fy+Fx)*Fb-(2*Fx)*Fc, 0)
                eq2 = sympy.Eq((0.5*Fb-Fc)**2+((sqrt(3)/2)*Fb)**2, maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fc] >0 and sol[0][Fb]>0:
                    dic[(Fx,Fy)]= (0,sol[0][Fb],sol[0][Fc])
                elif sol[1][Fc] >0 and sol[1][Fb]>0:
                    dic[(Fx,Fy)]= (0,sol[1][Fb],sol[1][Fc])
                else:
                    noPositive = noPositive+1
            print("on circle")
                    
        #inside circle
        #rounded number:
        rFx = int(round(Fx/r))
        rFy = int(round(Fy/r))
        if (Fx**2+Fy**2<126**2):
            if Fy>64 and Fx>(-64*sqrt(3)) and Fx<(64*sqrt(3)):
                #Fc=0
                Fa, Fb = sympy.symbols("Fa Fb", real=True)
                eq1 = sympy.Eq((sqrt(3)*Fy-Fx)*Fb-(sqrt(3)*Fy+Fx)*Fa, 0)
                eq2 = sympy.Eq((0.5*Fb+0.5*Fa)**2+((sqrt(3)/2)*Fb-(sqrt(3)/2)*Fa)**2, maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fa] >0 and sol[0][Fb]>0:
                    if (rFx, rFy) in dic:
                        print("in dic")
                        dic[(Fx,Fy)]= dic[(rFx,rFy)]
                    else:
                        dic[(Fx,Fy)]= (sol[0][Fa],sol[0][Fb],0)
                elif sol[1][Fa] >0 and sol[1][Fb]>0:
                    if (rFx, rFy) in dic:
                        print("in dic")
                        dic[(Fx,Fy)]= dic[(rFx,rFy)]
                    else:
                        dic[(Fx,Fy)]= (sol[1][Fa],sol[1][Fb],0)
                else:
                    noPositive = noPositive+1
            if Fy<64 and Fx>-128 and Fx<0:
                #Fb=0
                Fa, Fc = sympy.symbols("Fa Fc", real=True)
                eq1 = sympy.Eq((sqrt(3)*Fy+Fx)*Fa-(2*Fx)*Fc, 0)
                eq2 = sympy.Eq((0.5*Fa-Fc)**2+(-(sqrt(3)/2)*Fa)**2, maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fa] >0 and sol[0][Fc]>0:
                    if (rFx, rFy) in dic:
                        print("in dic")
                        dic[(Fx,Fy)]= dic[(rFx,rFy)]
                    else:
                        dic[(Fx,Fy)]= (sol[0][Fa],sol[0][Fb])
                elif sol[1][Fa] >0 and sol[1][Fc]>0:
                    if (rFx, rFy) in dic:
                        print("in dic")
                        dic[(Fx,Fy)]= dic[(rFx,rFy)]
                    else:
                        dic[(Fx,Fy)]= (sol[1][Fa],0,sol[1][Fc])
                else:
                    noPositive = noPositive+1
            if Fy<64 and Fx>0 and Fx<128:
                #Fa=0
                Fb, Fc = sympy.symbols("Fb Fc", real=True)
                eq1 = sympy.Eq(-(sqrt(3)*Fy+Fx)*Fb-(2*Fx)*Fc, 0)
                eq2 = sympy.Eq((0.5*Fb-Fc)**2+((sqrt(3)/2)*Fb)**2, maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fc] >0 and sol[0][Fb]>0:
                    if (rFx, rFy) in dic:
                        print("in dic")
                        dic[(Fx,Fy)]= dic[(rFx,rFy)]
                    else:
                        dic[(Fx,Fy)]= (0,sol[0][Fb],sol[0][Fc])
                elif sol[1][Fc] >0 and sol[1][Fb]>0:
                    if (rFx, rFy) in dic:
                        print("in dic")
                        dic[(Fx,Fy)]= dic[(rFx,rFy)]
                    else:
                        dic[(Fx,Fy)]= (0,sol[1][Fb],sol[1][Fc])
                else:
                    noPositive = noPositive+1
        print(n)
        n = n+1
print("Done")
print("No Positive:" , noPositive)
# In[84]:
#Advanced

n = 0
for Fx in xAxis:
    for Fy in yAxis:
        #ratio of power:
        r = sqrt((Fx**2+Fy**2)/128**2)
        if (Fx**2+Fy**2<=128**2):
            if Fy>64 and Fx>(-64*sqrt(3)) and Fx<(64*sqrt(3)):
                #Fc=0
                Fa, Fb = sympy.symbols("Fa Fb", real=True)
                eq1 = sympy.Eq((sqrt(3)*Fy-Fx)*Fb-(sqrt(3)*Fy+Fx)*Fa, 0)
                eq2 = sympy.Eq((0.5*Fb+0.5*Fa)**2+((sqrt(3)/2)*Fb-(sqrt(3)/2)*Fa)**2, r*maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fa] >0 and sol[0][Fb]>0:
                    dic[(Fx,Fy)]= (sol[0][Fa],sol[0][Fb])
                elif sol[1][Fa] >0 and sol[1][Fb]>0:
                    dic[(Fx,Fy)]= (sol[1][Fa],sol[1][Fb],0)
            if Fy<64 and Fx>-128 and Fx<0:
                #Fb=0
                Fa, Fc = sympy.symbols("Fa Fc", real=True)
                eq1 = sympy.Eq((sqrt(3)*Fy+Fx)*Fa-(2*Fx)*Fc, 0)
                eq2 = sympy.Eq((0.5*Fa-Fc)**2+(-(sqrt(3)/2)*Fa)**2, r*maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fa] >0 and sol[0][Fc]>0:
                    dic[(Fx,Fy)]= (sol[0][Fa],0,sol[0][Fc])
                elif sol[1][Fa] >0 and sol[1][Fc]>0:
                    dic[(Fx,Fy)]= (sol[1][Fa],0,sol[1][Fc])
            if Fy<64 and Fx>0 and Fx<128:
                #Fa=0
                Fb, Fc = sympy.symbols("Fb Fc", real=True)
                eq1 = sympy.Eq(-(sqrt(3)*Fy+Fx)*Fb-(2*Fx)*Fc, 0)
                eq2 = sympy.Eq((0.5*Fb-Fc)**2+((sqrt(3)/2)*Fb)**2, r*maxSpeed**2)
                sol=sympy.solve([eq1, eq2])
                if sol[0][Fc] >0 and sol[0][Fb]>0:
                    dic[(Fx,Fy)]= (0,sol[0][Fb],sol[0][Fc])
                elif sol[1][Fc] >0 and sol[1][Fb]>0:
                    dic[(Fx,Fy)]= (0,sol[1][Fb],sol[1][Fc])
        print(n)
        n = n+1
print("Done")


# In[84]:
dic[(-120, -10)]


