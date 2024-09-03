#--------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# lab 3
# Description: Calculates the rational aproximation of pi, the decimal equivalent and the ordinary continued fraction equivalent
#--------------------------------------------------------------------------------------------------------------------------------
# MoreContinuedFractions.py 
#--------------------------------------------------------------------------------------------------------------------------------
from rational import *
import sys 
from decimal import *

def CF2R(L): #CF(L)
    numer = int(L[-1]) 
    denom = 1
    finres = Rational(numer,1)
    L.pop(-1)
    for j in L[-1::-1]: 
        numer = int(L[-1])
        current = Rational(numer, 1)
        finres = current + finres.inverse()
        L.pop(-1)   
    return finres

def R2CF(x): 
    l = []
    a = x.numer
    b = x.denom 
    while a % b != 0: #this is the GCD function
        m = a // b # this is the whole number (7)
        rem = a % b # fraction remainder (31/158)
        a = b
        b = rem 
        l.append(m) 
    m = a // b 
    l.append(m)
    return l

def GCF2R(L):
    if len(L) >= 2:
        return Rational(L[0]) + (Rational(L[1]) / GCF2R(L[2:]))
    if len(L) == 1: 
        return Rational(L[0])
    if len(L) == 0:
        return Rational(1)

def pi_gen(): 
    yield 0 
    yield 4 
    k = 1
    while k <= 266: 
        n = 2 * k - 1
        m = k ** 2
        yield n
        yield m
        k += 1 

    
def usage():
    sys.stderr.write("Usage: $ python3 MoreContinuedFractions.py <input file> <output file>")
    exit()

def main():
    print("")
    L = []
    g = pi_gen()
    for i in range(265):
        L.append(next(g))
    r = (GCF2R(L)) #rational of pi
    print(str(r)) 
    print("")
    getcontext().prec = 101
    print((Decimal(r.numer) / Decimal(r.denom))) #decimal representation of pi
    print("")
    print(R2CF(r)) #ordinary continued fraction
    print("")
    
    
if __name__=='__main__': 
   main()
