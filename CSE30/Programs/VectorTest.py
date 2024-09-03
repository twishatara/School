#------------------------------------------------------------------------------
#  VectorTest.py
#------------------------------------------------------------------------------

import Vector

A = (-3, -4, 7)
B = (6, -2, 2)
C = (4, 4)
D = (-2, 2)

print()
print('dim(', A, ') =', Vector.dim(A))
print('dim(', C, ') =', Vector.dim(C))
print(A, '+', B, '=', Vector.add(A,B))
print('-', B, '=', Vector.negate(B))
print(A, '-', B, '=', Vector.sub(A,B))
print(2.5, A, '=', Vector.scalarMult(2.5, A))
print(-3.5, B, '=', Vector.scalarMult(-3.5, B))
print('hadamard(', A, ',', B, ') =', Vector.hadamard(A,B))
print('dot(', A, ',', B, ') =', Vector.dot(A,B))
print('|', A, '| =', Vector.length(A))
print('|', B, '| =', Vector.length(B))
print('unit(', C, ') =', Vector.unit(C))
print('unit(', D, ') =', Vector.unit(D))
print('angle(', C, ',', D, ') =', Vector.angle(C, D))

print()
E = Vector.randVector(2,-3,3)
print('random vector = ', E)
print()

# uncomment one of the lines below to raise a ValueError()
#Vector.add(A, C) 
#Vector.sub(A, C)
#Vector.hadamard(A, C)
#Vector.dot(A, C)
#Vector.angle(A, C)

