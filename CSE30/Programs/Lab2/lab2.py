#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Lab Assignment 2
# Description: 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Subset.py (Lab2) 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#changes the binary recursion bit list into subsets where only indexes with "1" have their number displayed
def to_string(L): 
    num = 0 
    x = "{"
    for count, num in enumerate(L):
        x += str(num)
        if (count != len(L)-1):
            x += " ,"
    x += "}"
    return x 

#creates all the possible bitlists of the subsets (only 0's and 1's)
def printSubsets(L, n, k, i):
    #n = len(B) - 1
    if k == 0: 
        print(to_string(L))
        return
    elif k > n - i + 1: 
        pass 
    else:
        #B[i] = 1 
        L.append(i)
        printSubsets(L,n,k-1,i+1) #this is the left side of the trace (k-1,i+1)
        #B[i] = 0 
        L.pop(-1)
        printSubsets(L,n,k,i+1) #this is the right side of the trace (k, i+1)
        return


#---main program start-----------------------------------------------------------------------------------------
if __name__=='__main__': 
    import math
    import sys

    try: 
        if len(sys.argv) == 1 or len(sys.argv) == 2:
            exit()
        
        #if len(sys.argv) == 5:
            #print("{ }")
        
        n = int(sys.argv[1])
        k = int(sys.argv[2])
        #if n == 0 or k == 0:  
        
        if(n < 0 or k < 0):
            exit() 
        
        L = []
        #B = [0] * (n+1)
        #B[0] = '*'
        
        printSubsets(L, n, k, 1)
        #printSubsets(B, k, 1)
    except ValueError:
        exit()