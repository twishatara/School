#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 5
#
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# test.py 
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#--- functions ---------------------------------------------------------------------------------------------------------------------------------------------------------------
def getPrimes(n):
    P=[]
    seive=makeSieve(n)

    for i in range(2,len(seive)):
        if seive[i]==True:
            P.append(i)
    return P

def makeSieve(n): 
    S = [True for i in range(n+1)] 
    i = 2

    while (i**2 <= n): 
        if (S[i] == True): 
            for j in range(i*2, n+1, i): 
                S[j] = False
        i += 1
    S[0] = False 
    S[1] = False
    return S
#--- main program ------------------------------------------------------------------------------------------------------------------------------------------------------------

n=int(input("\nEnter a positive integer: ")) 

while(n<=0):
    n=int(input("Please enter a positive integer: "))

primes = getPrimes(n)
sieve = makeSieve(n)

print("\nThere are "+str(len(primes))+" prime numbers less than or equal to "+str(n)+":\n")
count=0

for i in primes:
    if(count==10):
        print("")
        count=0 
    print(i,end=" ")
    count+=1   

print("")    
print("")
