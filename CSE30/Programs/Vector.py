#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 8
# Description: 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Vector.py 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
import math
import random

#------------------------------------------------------------------------------
# function definitions
#------------------------------------------------------------------------------

#add() 
def add(u, v): #adds the three numbers for u and the three numbers of v 
    "Return the vector sum u+v."
    if not len(u) == len(v): #value error is u and v are not the same dimension
        raise ValueError('incompatible vectors: '+str(u)+', '+str(v))

    ans = []
    for i in range(len(u)):
        ans.append(u[i] + v[i])
    return tuple(ans)
#end add()


#negate() 
def negate(u): #turns the input positive numbers negative and vice versa
    "Return the negative of the vector u."
    ans = []
    for i in range(len(u)):
        ans.append(u[i] * -1)
    return tuple(ans)
#end negate()


#sub() 
def sub(u, v): #subtracts the three numbers for u and the three numbers for v
    "Return the vector difference u-v."
    if not len(u) == len(v): #value error is u and v are not the same dimension
      raise ValueError('incompatible vectors: '+str(u)+', '+str(v))
    
    ans = []
    for i in range(len(u)):
        ans.append(u[i] - v[i])
    return tuple(ans)
#end sub() 


#scalarMult() 
def scalarMult(c, u): #multiply the three numbers of u with a constant c 
    "Return the scalar product cu of the number c by the vector u."
    ans = []
    for i in range(len(u)):
        ans.append(u[i] * c)
    return tuple(ans)        
#end scalarMult()


#hadamard()
def hadamard(u, v): #matrices multiplication??? i have no clue lol 
    "Return the Hadamard product of u with v."
    if not len(u) == len(v): #value error is u and v are not the same dimension
      raise ValueError('incompatible vectors: '+str(u)+', '+str(v))

    ans = []
    for i in range(len(u)):
        ans.append(u[i] * v[i])
    return tuple(ans)
#end hadamard()


#dot() 
def dot(u, v): #matrices multiplication but then add up the 3 answers to get one answer
    "Return the dot product of u with v."
    if not len(u) == len(v): #value error is u and v are not the same dimension
      raise ValueError('incompatible vectors: '+str(u)+', '+str(v))

    ans = []
    return sum(hadamard(u,v))
#end dot() 


#length() 
def length(u): #calculates the length of vector u by multipling it by itself and then taking the squareroot
    "Return the (geometric) length of the vector u."
    k = 0
    for i in range(len(u)):
        k += (u[i] * u[i])
    return math.sqrt(k)
#end length()


# dim()
def dim(u): #returns the length of u 
   "Return the dimension of the vector u."
   return len(u)
# end dim()


# unit() 
def unit(v): #multiply v by the reciprocal of its length 
    "Return the dimension of the vector u."
    ans = []
    reci = 1/length(v) #dot???
    for i in range(len(v)):
        ans.append(v[i] * reci)
    return tuple(ans)
# end unit() 


# angle() 
def angle(u, v):
    "Return the angle (in radians) between vectors u and v."
    if not len(u) == len(v): #value error is u and v are not the same dimension
      raise ValueError('incompatible vectors: '+str(u)+', '+str(v))
    
    return math.acos(dot(unit(u), unit(v)))
# end angle() 


# randVector() 
def randVector(n, a, b): #makes a random vector
    "Return a vector of dimension n whose components are random floats in the range [a, b)."
    ans = []
    for i in range(n):
        ans.append(random.uniform(a,b))
    return tuple(ans)
# end randomVector() 


if __name__=="__main__":
    print("")
    """DESCRIPTION 
            This module provides functions to perform standard vector operations. Vectors
            are represented as tuples of numbers (floats or ints). Functions that take two
            vector arguments will raise a ValueError() exception if the two vectors are of
            different dimensions."""