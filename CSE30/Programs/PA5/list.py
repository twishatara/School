#-------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 5
# Description: 
#------------------------------------------------------------------------------
# list.py 
#------------------------------------------------------------------------------
class _Node(object):
    def __init__(self, x):
        self.data = x
        self.next = None
    # end

# end

class List(object):

    def __init__(self, s=None):
        """Initialize self, a List object."""
        self._front = None
        self._back = None
        self._length = 0
        if s:
            for x in s:
                self.append(x)
            # end
        # end
    # end

    def __len__(self):
        """Return the length of self."""
        return self._length
    # end

    def __str__(self):
        """Return a string representation of self."""
        s = '['
        for x in self:
            s += "{}, ".format(repr(x))
        # end
        if len(self)>0:
            s = s[0:-2]+']'
        else:
            s += ']'
        # end
        return s
    # end

    def __repr__(self):
        """Return a detailed string representation of self."""
        return 'list.List('+str(self)+')'
    # end

    def __iter__(self):
        """Return an iterator over self."""
        N = self._front
        while N:
            yield N.data
            N = N.next
        # end
    # end

    def __eq__(self, other):
        """
        Return True if self and other are the same sequence, False otherwise.
        """
        eq = (len(self)==len(other))
        N = self._front
        M = other._front
        while eq and N:
            eq = (N.data==M.data)
            N = N.next
            M = M.next
        # end
        return eq
    # end

    def append(self, x):
        """Add item x to back of List."""
        N = _Node(x)
        if len(self)==0:
            self._front = self._back = N
        else:
            self._back.next = N
            self._back = N
        # end
        self._length += 1
    # end 

    def clear(self):
        """Delete all items from List."""
        self._front = None
        self._back = None
        self._length = 0
    # end 

    def copy(self):
        """Return a (shallow) copy of List."""
        C = List()
        for x in self:
            C.append(x)
        # end
        return C
    # end

    def insert(self, i, x):
        """Add item x at position i of List, where -n<=i<=n and n=len(self)."""
        n = len(self)
        if not isinstance(i, int):
            raise TypeError('insert() index must be integer')
        # end
        if not -n<=i<=n:
            raise IndexError('insert() index out of range')
        # end

        # interpret negative i as position n-|i|
        if i<0: i += n

        # perform insertion
        N = _Node(x)
        if n==0:   # sepcial case: insertion into an empty list
            self._front = self._back = N
        elif i==n: # special case: insertion at the back
            self._back.next = N
            self._back = N
        elif i==0: # special case: insertion at the front
            N.next = self._front
            self._front = N
        else:      # general case: 1<=i<=n-1
            P = self._front
            S = P.next
            for j in range(1, i):
                P = S
                S = S.next
                # end
                P.next = N
                N.next = S
        # end
        self._length += 1
    # end

    def pop(self, i=-1):
        """
        Delete item at position i of List, where -n<=i<=(n-1) and n=len(self).
        """
        n = len(self)
        if not isinstance(i, int):
            raise TypeError('pop() index must be integer')
        # end
        if n==0:
            raise IndexError('cannot pop() empty List')
        # end
        if not -n<=i<=(n-1):
            raise IndexError('pop() index out of range')
        # end

        # interpret negative i as position n-|i|
        if i<0: i += n

        # perform deletion
        if n==1:      # special case: deletion from a 1-element list
            N = self._front
            self._front = self._back = None
        elif i==0:    # special case: delete front element
            N = self._front
            self._front = N.next
            N.next = None
        else:         # general case: 1<=i<=n-1
            P = self._front
            S = P.next
            for j in range(1, i):
                P = S
                S = S.next
                # end
            N = S
            S = N.next
            P.next = S
            N.next = None
            if not S:  # sub-case: delete back element
                self._back = P
            # end
        # end
        self._length -= 1
        return N.data
# end

#---------------------------------------------------------------------------
#  Functions to be added to List for pa5
#---------------------------------------------------------------------------

    def remove(self, x):
        """
        Delete leftmost occurance of x in List. Raise ValueError if x is not
        contained in self.
        """
        flag = 0 
        L = List()
        n = self._length

        now = self._front
        for i in range(0, n):
            if x == now.data: 
                self.pop(i)
                flag += 1 
                break
            now = now.next
        if flag == 0: 
            raise ValueError()
        return self
        # end

    def reverse(self):
        """Reverse the items of List."""
        n = self._length
        L = List()
        while n >= 1: #for j in range(n):
            i = self.pop(n-1)
            L.append(i)
            n = self._length
        return L
    # end

    def __getitem__(self, i):
        """
        Return item at position i of self, where -n<=i<=n-1 and n=len(self).
        """
        flag = 0 
        n = self._length
        now = self._front
        for j in range(0 , n): 
            if j == i: # if the index you are at = the index you want 
                return now.data # is this the correct way to print the data
            now = now.next # go to the next index
        now = self._front
        for j in range(-n , 0): 
            if j == i: # if the index you are at = the index you want 
                return now.data # is this the correct way to print the data
            now = now.next
        if i >= n: 
            raise ValueError()
        if i < -n:
            raise ValueError()
        pass
    # end

    def __setitem__(self, i, x):
        """
        Overwrite item at position i of self by x, where -n<=i<=n-1 and 
        n=len(self).
        """
        flag = 0 
        n = self._length
        now = self._front
        for j in range(0 , n): 
            if j == i:
                now.data = x 
            now = now.next
        now = self._front
        for j in range(-n , 0): 
            if j == i:
                now.data = x 
            now = now.next 
        if i >= n:
            raise ValueError()
        if i < -n:
            raise ValueError()
    # end

    def __add__(self, other):
        """
        Return the concatenation of self with other. This function implements
        the operation self + other.
        """
        endlist = List()
        selfcopy = List(self)
        othercopy = List(other)
        if self._length == 0: 
            return othercopy
        if other._length == 0:
            return selfcopy
        endlist._length = self._length + other._length
        selfcopy._back.next = othercopy._front
        endlist._back = othercopy._back 
        endlist._front = selfcopy._front
        return endlist

    # end

    def __iadd__(self, other):
        """
        Replace self by the concatenation of self with other. This function
        implements the operation self += other.
        """
        '''
        endlist = List()
        selfcopy = List(self)
        othercopy = List(other)
        if self._length == 0: 
            return othercopy
        if other._length == 0:
            return selfcopy
        endlist._length = self._length + other._length
        selfcopy._back.next = othercopy._front
        endlist._back = othercopy._back 
        endlist._front = selfcopy._front
        return endlist
        '''
        self = self + List(other)
        return self
        
    # end

    def __mul__(self, n):
        """
        Return the n-fold concatenation of self with self, where n>=0. This
        function implements the operation self*n.
        """
        #go thru self and append the values of self n times to a new list and return a new list
        L = List()
        for n in range(n): 
            selfcopy = List(self)
            L += selfcopy
        return L 
        pass
    # end

    def __rmul__(self, n):
        """
        Return the n-fold concatenation of self with self, where n>=0, reversing
        the order of self and n. This function implements the operation n*self.
        """
        L = List()
        for n in range(n): 
            selfcopy = List(self)
            L += selfcopy
        return L 
        pass
    # end

    # end
    #------------------------------------------------------------------------------
