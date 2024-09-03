#-------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 3
# Description: 
#------------------------------------------------------------------------------
# Lines.py 
#------------------------------------------------------------------------------

import math

#------------------------------------------------------------------------------
#  Do not change the definition of the Point class, other than to define 
#  the function join() at the end.
#------------------------------------------------------------------------------

class Point(object):
   """Class representing a Point in the x-y coordinate plane."""

   def __init__(self, x, y):
       #Initialize a Point object."""
        self.xcoord = x
        self.ycoord = y
   # end

   def __str__(self):
       #Return the string representation of a Point."""
        return '({}, {})'.format(self.xcoord, self.ycoord)
   # end

   def __repr__(self):
        #Return the detailed string representation of a Point."""
        return 'geometry.Point({}, {})'.format(self.xcoord, self.ycoord)
   # end

   def __eq__(self, other): 
        #Return True if self and other have the same coordinates, False otherwise.
        eqx = (self.xcoord==other.xcoord)
        eqy = (self.ycoord==other.ycoord)
        return eqx and eqy
   # end

   def distance(self, other):
        #Return the distance between self and other."""
        diffx = self.xcoord - other.xcoord
        diffy = self.ycoord - other.ycoord
        return math.sqrt( diffx**2 + diffy**2 )
   # end

   def norm(self):
        #Return the distance from self to the origin (0, 0)."""
        return self.distance(Point(0,0))
   # end

   def midpoint(self, other):
        #Return the midpoint of the line segment from self to other."""
        midx = (self.xcoord + other.xcoord)/2
        midy = (self.ycoord + other.ycoord)/2
        return Point(midx, midy)
   # end

   #---------------------------------------------------------------------------
   #  Fill in the definition of this function, belonging to the Point class.
   #---------------------------------------------------------------------------
   def join(self, other):
        #If self==other return None. Otherwise return the line passing through self and other.

        y1 = other.ycoord
        y2 = self.ycoord
        x1 = other.xcoord
        x2 = self.xcoord
        P = Point(x2,y2)
        m = (y2 - y1) / (x2 - x1)
        if self == other: 
            return None
            if self.xcoord == other.xcoord: 
                if self.slope == "infinity":
                    return Line(self.xcoord, self.slope)
        else: 
            return Line(P, m)
        pass


   # end     

# end


#------------------------------------------------------------------------------
#  Fill in the definitions of each method in the Line class.
#------------------------------------------------------------------------------
class Line(object):
   """Class representing a Line in the x-y coordinate plane."""
   
   def __init__(self, P, m):
        #Initialize a Line object."""
        self.Point = P 
        self.slope = m     
        pass
   # end

   def __str__(self):
        #Return a string representation of a Line."""
        return 'Line through ({}, {}) of slope {}'.format(self.Point.xcoord, self.Point.ycoord, self.slope)
        pass
   # end

   def __repr__(self):
        #Return a detailed string representation of a Line."""
        return 'lines.Line(point=({}, {}), slope={})'.format(self.Point.xcoord, self.Point.ycoord, self.slope)
        pass
   # end

   def __eq__(self, other): 
        #Return True if self and other are identical Lines, False otherwise.
        if self.slope == other.slope: # if other.slope == m
            y1 = other.Point.ycoord
            y2 = self.Point.ycoord
            x1 = other.Point.xcoord
            x2 = self.Point.xcoord
            if x2 - x1 == 0:
                if self.slope == "infinity": 
                    return True
            elif x2 - x1 == 0:
                if self.slope != "infinity":
                    return False
            m = (y2 - y1) / (x2 - x1)
            if self.slope == m: 
                return True
        return False
        pass
   # end

   def parallel(self, other): # Get help with this one (how do you call the lines self and other)
        #Return True if self and other are parallel lines, False otherwise.
        if self.slope == other.slope : # if self.m == other.m??? checks if the slopes of the lines self and other are the same 
            return True
        else:
            return False
        pass
   # end

   def perpendicular(self, other): # Get help with this one
       #Return True if self and other are perpendicular lines, False otherwise.
        if self.slope == "infinity": 
            if other.slope == 0: 
                return True
        if other.slope == "infinity": 
            if self.slope == 0: 
                return True
        if other.slope == 0: 
            return False
        if self.slope == -1 * (1/other.slope): 
            return True
        else: 
            return False
        pass
   # end

   def contains_point(self, P):
       #Return True if self contains point P, False otherwise.
        y1 = P.ycoord
        y2 = self.Point.ycoord
        x1 = P.xcoord
        x2 = self.Point.xcoord
        y = y1 - y2
        x = x1 - x2 

        if x == 0 and y == 0: #if points are same, on line 
            return True 
        elif x != 0 and y == 0: 
            if self.slope == 0:
                return True
        elif x == 0 and y != 0: 
            if self.slope == "infinity": 
                return True 
        elif x != 0 and y == 0:
            if self.slope != 0: 
                return False 
        m = y / x 
        if self.slope == m: 
            return True
        else: 
            return False 

        pass
   # end    

   def intersect(self, other): # Get help with this one too
       #If self and other are parallel, return None.  Otherwise return their Point of intersection.
      
        y1 = other.Point.ycoord
        y2 = self.Point.ycoord
        x2 = self.Point.xcoord
        x1 = other.Point.xcoord

        if self.slope == other.slope or self.slope == "infinity" and other.slope == "infinity": #if the slopes of the lines self and other are the same
            return None    
        elif self.slope == "infinity": #no while loop
            m1 = other.slope
            b1 = y1 - (m1 * x1)
            y = m1 * x2 + b1 
            return Point(x2, y)
        elif other.slope == "infinity": #no while loop
            m2 = self.slope
            b2 = y2 - (m2 * x2)
            y = m2 * x1 + b2 
            return Point(x1, y)
        else: 
            m1 = other.slope
            m2 = self.slope
            b1 = y1 - (m1 * x1)
            b2 = y2 - (m2 * x2)
            xi = (b1 - b2) / (m2 - m1)
            yi = m1 * xi + b1
            return Point(xi,yi) #'({},{})'.format(xi,yi) #'({}, {})'.format(xi, yi) 
        pass 
   # end

   def parallel_line(self, P):
       #Returns the Line through P that is parallel to self.""
        return Line(P, self.slope)
        pass
   # end

   def perpendicular_line(self, P):
       #Returns the Line through P that is perpendicular to self."""
        y1 = P.ycoord
        y2 = self.Point.ycoord
        x1 = P.xcoord
        x2 = self.Point.xcoord

        if self.slope == "infinity": 
            m = 0
            return Line(P, m)
        if self.slope == 0: 
            m = "infinity"
            return Line(P, m)
        else:
            m = (y2 - y1) / (x2 - x1)
            m1 = -1 * (1 / (m)) 
            return Line(P, m1)
        #if self.slope == -1 * (1/m): 
            #return True
        
        pass
    
   # end


# end

#------------------------------------------------------------------------------
#  Do not change functon main(). Its role is just to test all of the above.
#  Actually you can change it during your own independent testing, but return
#  it to exactly this state before you submit the project.
#------------------------------------------------------------------------------
def main():

   P = Point(1, 3)
   Q = Point(3, 3)
   R = Point(1, 1)
   S = Point(3, 1)
   T = Point(4, 3)
   U = Point(5, 5)
   V = Point(2, 2)
   W = Point(2, 5)
   X = Point(2, -1)

   A = Line(P, -1)
   B = Line(R, 1)
   C = S.join(T) #points_to_line(S, T)
   D = Line(W, 'infinity')
   E = Line(Q, 0)
   F = C.parallel_line(P)

   print()
   print('A =', A)
   print(repr(A))
   print()
   print('B =', B)
   print(repr(B))
   print()
   print('C =', C)
   print(repr(C))
   print()
   print('D =', D)
   print(repr(D))
   print()
   print('E =', E)
   print(repr(E))
   print()
   print('F =', F)
   print(repr(F))

   print()
   print(B.intersect(C)==U)
   print(A.intersect(B)==V)
   print(D.intersect(C)==X)
   print(D.intersect(Line(T,'infinity'))==None)
   print(A.perpendicular(B))
   print(D.perpendicular(E))
   print(A.parallel(B.perpendicular_line(Q)))
   print(A.contains_point(S))
   print(B.contains_point(U))
   print(C.contains_point(X))
   print(F.contains_point(W))

   print()

# end

#------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end

#------------------------------------------------------------------------------
#  If your Line class and join() method in the Point class are correct, then
#  the output of function main() should be as follows.
#------------------------------------------------------------------------------
"""

A = Line through (1, 3) of slope -1
lines.Line(point=(1, 3), slope=-1)

B = Line through (1, 1) of slope 1
lines.Line(point=(1, 1), slope=1)

C = Line through (3, 1) of slope 2.0
lines.Line(point=(3, 1), slope=2.0)

D = Line through (2, 5) of slope infinity
lines.Line(point=(2, 5), slope=infinity)

E = Line through (3, 3) of slope 0
lines.Line(point=(3, 3), slope=0)

F = Line through (1, 3) of slope 2.0
lines.Line(point=(1, 3), slope=2.0)

True
True
True
True
True
True
True
True
True
True
True

"""
      