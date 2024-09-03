def notDivisibleBy(a, n):
    ans = []
    for i in range (1, n):
        if i % a != 0:
            ans.append(i)
        return ans