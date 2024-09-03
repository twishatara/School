from list import *


#------------------------------------------------------------------------------
#  Test the List type
#------------------------------------------------------------------------------
def main():
    '''
    L = List()
    L.append(1)
    L.append(2)
    L.append(3)
    print(len(L))
    print(L)
    print(repr(L))

    A = List()
    A.append(1)
    A.append(2)
    A.append(3)
    print('A==L :', A==L)
    A.append(4)
    print('A==L :', A==L)
    L.append(5)
    print(L)
    print(A)
    print('A==L is', A==L)

    L.clear()
    print(len(L))
    print(L)

    B = A.copy()
    print(B)
    print(repr(B))
    print('A==B :', A==B)
    print('A is B :', A is B)

    print()
    print(B)
    B.insert(0, 'foo')
    print(B)
    B.insert(3, 'bar')
    print(B)
    B.insert(6, 'one')
    print(B)
    B.insert(-2, 'two')
    print(B)
    print(repr(B))
    print(len(B))

    print()
    print(B.pop(0))
    print(B)
    print(B.pop(2))
    print(B)
    print(B.pop(5))
    print(B)
    print(B.pop(-2))
    print(B)
    print(len(B))
    print()
    '''

    ''' Test reverse '''
    l = List([8, 16, 52, 17])
    print("reverse:")
    print(l.reverse())
    
    
    ''' Test remove '''
    l = List([1, 2, 3, 4, 5])
    print("remove:")
    print(l.remove(3))

    ''' Test getitem '''
    l = List([1, 2, 3, 4, 5])
    print("getitem:")
    print(l.__getitem__(3))
    
    ''' Test setitem '''
    l.__setitem__(3, 5)
    print("setitem:")
    print(l) #tests to make sure the variable was replaced

    ''' Test add '''
    l = List([1, 2, 3])
    l2 = List([1, 2, 3, 4, 5])
    print("add:")
    print(l + l2)

    ''' Test iadd '''
    l = List([1, 26, -6, 8, 5])
    l2 = List([59, 4, 9, 8])
    l += l2
    print("iadd:")
    print(l)

    ''' Test mul '''
    l = List([1, 2, 3])
    l2 = List([1, 2, 3, 4, 5])
    print("mul:")
    print(l * 2)

    ''' Test rmul '''
    l = List([1, 2, 3])
    l2 = List([1, 2, 3, 4, 5])
    print("rmul:")
    print(3 * l)

    # end

#------------------------------------------------------------------------------
if __name__=='__main__':

    main()

# end
    