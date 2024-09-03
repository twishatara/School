def transpose(D):
    d = dict() 
    for i in D: 
        d[i] = []
    for i in D: 
        for j in D[i]:
            d[j] += i
    return d

x = {'1': ['2', '3'], '2': ['3'], '3': ['4'], '4': ['2']}
print(transpose(x))