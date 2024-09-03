def Diameter(G):
    max = 0 
    for x in self._vertices:
        G.BFS(x)
        for y in self._vertices:
            d = getDistance(y)
            if d > max:
                max = d 
    return max 