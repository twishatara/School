import math 
x = float(input("Enter value for x:"))
s = ["circle", "square", "eq_triangle"]

def circlearea(x):
    a = math.pi*pow(x,2)
    return a 

def squarearea(x):
    a = pow(x,2)
    return a 

def eq_trianglearea(x):
    a = (math.sqrt(3)/4)*pow(x, 2)
    return a 

def areaOf(s, x):
    c = circlearea(x)
    sq = squarearea(x)
    eq = eq_trianglearea(x)
    print("The area of the circle is", c)
    print("The area of the square is", sq)
    print("The area of the equilateral triangle is", eq)

print(areaOf(s, x))