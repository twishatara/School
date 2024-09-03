#------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 3
# computes the volume and area of a sphere and cylinder using their respective formulas when the user inputs 3 numbers
#------------------------------------------------------------------------------------------------------------------------------------
# Formulas.py 
#------------------------------------------------------------------------------------------------------------------------------------

import math

#function for the formula for volume of a sphere
def sphere_volume(r):
    v = 4/3*math.pi*pow(r, 3)
    return v 
#end function
    
#function for the formula for area of a sphere 
def sphere_area(r):
    a = 4*math.pi*pow(r, 2)
    return a
#end function

#function for the formula for the volume of a cylinder
def cylinder_volume(r, h):
    v = math.pi*pow(r, 2)*h
    return v  
#end function

#function for the formula for the area of a cylinder
def cylinder_area(r, h):
    a = 2*math.pi*pow(r, 2)+2*math.pi*r*h
    return a
#end function

#function to print the answers to the formulas for the volume and area of a sphere
def print_sphere(r):
    v = sphere_volume(r) 
    a = sphere_area(r) 
    print("The volume of the sphere with radius", r, "is:", v)
    print("The surface area of the sphere with radius", r, "is:", a)
#end function

#function to print the answers to the formulas for the volume and area of a cylinder
def print_cylinder(r, h):
    v = cylinder_volume(r, h)
    a = cylinder_area(r, h)
    print("The volume of the cylinder with radius", r, "and height", h, "is:", v)
    print("The surface area of the cylinder with radius", r, "and height", h, "is:", a)
#end function

#--- main program ----------------------------------------------
print("Enter three numbers:")
nA = float(input("first number: "))
nB = float(input("second number: "))
nC = float(input("third number: "))
print() #blank line

print_sphere(nA)
print()
print_sphere(nB)
print() 
print_sphere(nC)
print()
print_cylinder(nA, nB)
print()
print_cylinder(nB, nC)
print()
print_cylinder(nC, nA)
print()
#--- end program -----------------------------------------------