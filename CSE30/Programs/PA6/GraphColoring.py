
import sys
from graph import *


def CheckProperColoring(G):
    """
    Return True if no two adjacent vertices in G have like colors,
    False otherwise.
    """
    pass
# end

def main():
    if len(sys.argv)!=3:
        usage()
    try:
        infile = open(sys.argv[1])
    except FileNotFoundError as e:
        print(e, file=sys.stderr)
        usage()
    

    outfile = open(sys.argv[2], 'w')
    lines = infile.readlines() # read lines put every line in a list

    V = []
    v = int(lines[0])
    for k in range(1, v+1):
        V.append(k)
    E = [] 
    for i in range(1, len(lines) - 1):
        strpair = lines[i]
        edge = strpair.split(" ")  
        tup = (int(edge[0]), int(edge[1]))
        E.append(tup) 
    G = Graph(V,E)
    s = set(G.Color())
    print(len(s), 'colors used:', s, file=outfile) 

    infile.close()

# end

if __name__=='__main__': 
    main()