from rational import *
import sys 
from decimal import *


def CF(L):
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

def usage():
    sys.stderr.write("Usage: $ python3 ContinuedFractions.py <input file> <output file>")
    exit()

def main():
    if len(sys.argv)!=3:
      usage()
    try:
        infile = open(sys.argv[1])
    except FileNotFoundError as e:
        print(e, file=sys.stderr)
        usage()
    
    outfile = open(sys.argv[2], 'w')
    lines = infile.readlines()

    for S in lines:
        L = S.split()
        result = CF(L)
        print("", file = outfile)
        print(result, file = outfile)
        getcontext().prec = 100
        print(Decimal(result.numer)/Decimal(result.denom), file = outfile)
        R = ' '.join(L)
        #print(R, file=outfile)

        

    infile.close()
    outfile.close()

if __name__=='__main__': 
   main()