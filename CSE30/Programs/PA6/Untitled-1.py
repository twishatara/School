#60 /100 graph.py
#-------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 6
# Description: color every vertext of a graph with a color so that no connected verticies have the
#              same color. returning the set of all the colors used on the graph, making sure that 
#              only the minimum ammount of colors were used.
#-------------------------------------------------------------------------------------------------
# graph.py 
#-------------------------------------------------------------------------------------------------
from queue import Queue
import sys

class Graph(object):
    """Class representing an undirected graph."""
    # _color: a dictionary whose keys are vertices x, and value _color[x], the color of x
    # _ecs: a dictionary whose keys are vertices x, and value _ecs[x], the excluded color set of x
    # the colors determine wether they are adjacent to each other or not
    # get the keys 
    # start a for or while loop to check if the key is in the other vertices list 

    def __init__(self, V, E):
        """Initialize a Graph object."""
        # basic attributes
        self._vertices = list(V)
        self._vertices.sort()
        self._edges = list(E)
        self._adj = {x:list() for x in V}
        self._color = {x:None for x in V} 
        self._ecs = {x:set() for x in V}
        for e in E:
            x,y = tuple(e)
            self._adj[x].append(y)
            self._adj[y].append(x)
            self._adj[x].sort()
            self._adj[y].sort()
        # end
    # end

    @property
    def vertices(self):
        """Return the list of vertices of self."""
        return self._vertices
    # end

    @property
    def edges(self):
        """Return the list of edges of self."""
        return self._edges
    # end

    def __str__(self):
        """Return a string representation of self."""
        s = ''
        for x in self.vertices:
            a = str(self._adj[x])
            s += '{}: {}\n'.format(x, a[1:-1])
        # end
        return s  
    # end      

    def degree(self, x):
        """Returns the degree of vertex x."""
        return len(self._adj[x])
    # end

    def Color(self):
        """
        Determine a proper coloring of a graph by assigning a color from the
        set {1, 2, 3, .., n} to each vertex, where n=|V(G)|, and no two adjacent
        vertices have the same color. Try to minimize the number of colors
        used. Return the subset {1, 2, .., k} of {1, 2, 3, .., n} consisting
        of those colors actually used.
        """

        # start at some vertex 
        # while there are uncolored verticies 
        #   find the best one, call it x 
        #   assign color[x] = smallest color not in ecs[x]
        #   for all y existing in adj[x]
        #       add color x to ecs[y]

        # initializes
        L = set(self._vertices) #undiscovered
        usedcolors = set()
        x = L.pop() 
        color = self._vertices # n = k??
        #self._color[x] = 1 
        discovered = list()
        discovered.append(x) 
        while len(discovered) != 0: 
            cur = discovered.pop(0)
            D = self._ecs[cur] # colors that cur cant be
            sc = set(color) 
            sd = set(D)  
            print(sc)
            print(sd)
            self._color[cur] = min(list(sc-sd)) # generates possible colors
            print(min(sc-sd))
            if self._color[cur] not in usedcolors:
                usedcolors.add(self._color[cur])
            for y in self._adj[cur]:  
                self._ecs[y].add(self._color[cur]) 
                if y in L: 
                    L.remove(y) # move y from undiscovered
                    discovered.append(y) # to discovered 
                # end
            # end
            # end
        return usedcolors # set of colors used 

    def getColor(self, x):
        """ Return the color of x."""
        return self._color[x]
    # end

    def _find_best(self, L):
        """Return the index of the best vertex in the list L."""
        pass
    # end

# end 