import math
import sys


n = int(sys.argv[1])
k = int(sys.argv[2])


def to_string(B): 
    subsets = '{'
    switch = 0 
    for j in range(len(B)):
        if B[j] == 1: 
            if(switch == 1):
                subsets += ", "
            subsets += str(j)
            switch = 1 
        if B[j] == 0:
            pass
    subsets += '}'
    return subsets 

#creates all the possible bitlists of the subsets
def printSubsets(B, k, i):
    if k == 0: #call to_string
        print(to_string(B))
        return
    elif k > n - i + 1: 
        pass #pass
    else:
        B[i] = 1 
        printSubsets(B,k-1,i+1) #this is the left side of the trace
        B[i] = 0 
        printSubsets(B,k,i+1) #this is the right side of the trace 

def main():
    B = [0] * (n+1)
    B[0] = '*'
    #print(B)
    i = B[1]
    printSubsets(B, k, 1)



if __name__=='__main__': 
    main()
