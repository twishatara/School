def my_range(start,stop,step):
    while start < stop: 
        yield start
        start += step
print(list(my_range(2,10,2))) 

def interleave(G, H):
    i = next(G)
    k = next(H)
    print(i, k)
    while True:
        if i > k:
            print(k)
            k = next(H)
        elif i < k:
            print(i)
            try:
                i = next(G)
            except StopIteration:
                break
    while True:
        if button == 0:
            yield i
            try:
                i = next(G)
            except StopIteration:
                break
        if button == 1:
            yield k
            try:
                k = next(H)
            except StopIteration:
                break

for i in interleave(my_range(1, 6, 2), my_range(2, 11, 2)):
    print(i)


