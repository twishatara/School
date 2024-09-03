import random

n = ["one", "two", "three", "four"]

L = []
for i in range(6):
    L.append(random.randint(0,10))

L = (L[n :len(L)] + L[0:n])
print("The result of the totated list should be: {}".format(L))

def rotate(L, i, j, k):
    temp = L[i]
    L[i] = L[j]
    L[j] = L[k]
    L[k] = temp
    return l[n:] + l[:n]


