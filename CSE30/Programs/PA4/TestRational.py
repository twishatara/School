#------------------------------------------------------------------------------
#  TestRational.py
#  A weak test of the Rational class.
#------------------------------------------------------------------------------
from rational import *
from decimal import *


def main():

   A = Rational(745839234, 293847742)  # 372919617/146923871
   B = Rational(658, -239) # -658/239
   C = A*B
   D = C.inverse()

   print()
   print(A)
   print(repr(A))
   print(B)
   print(repr(B))
   print(C)
   print(repr(C))
   print(D)
   print(repr(D))
   print()
   print(A+B)
   print(A-B)
   print(A*B)
   print(A/B)
   print(A.inverse())
   print()

   a = float(A)
   b = float(B)
   c = a*b
   d = 1/c
   print(a)
   print(b)
   print(c)
   print(d)
   print()

   getcontext().prec = 50  # set Decimal precision to 1000 digits
   a = Decimal(A.numer)/Decimal(A.denom)
   b = Decimal(B.numer)/Decimal(B.denom)
   c = a*b
   d = 1/c
   print(a)
   print(b)
   print(c)
   print(d)
   print()

   print(A>B)
   print(B>=C)
   print(C<D)
   print(D<=A)
   print( A==C/B )
   print( (A*B)/(C*D)==(A/C)*(B/D) )
   print()

   help(Rational)

# end

#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end