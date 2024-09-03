import math 
import sys 

n = int(sys.argv[1])
k = int(sys.argv[2])

'''
my_set = {1}
s = 1
for i in range(n):
    my_set.add(s)
    s = s + 1 
my_set = set(my_set)
#print("set is = ", my_set)
'''

def to_string(B): #bit list converts to subset
    setString = '{' 
    button = 0 
    for i in range(len(B)): #i is index of bit list
        if B[i] == 1: 
            if(button == 1):
                setString += ", " #+= appending for strings 
                setString += str(i) #+= because adding to whats in set string
            button = 1
    setString += "}"
    return setString

def printSubsets(B, k, i):
    if k == 0: #call to_string
        print(B)
        print(to_string(B))
    elif k > n - i + 1:
        return #pass
    else:
        B[i] = 1
        printSubsets(B, k-1, i+1) 
        B[i] = 0 
        printSubsets(B, k, i+1)


def main():
    #B = list(range(0, n+1))
    B = [0] * (n + 1) 
    B[0] = '*'
    #print(B)
    i = B[1]
    #to_string(B)
    printSubsets(B, k, 1)


if __name__ == '__main__':
    main()