#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu CSE 30 Srping 2021
# Lab Assignment 1
# Description: Prints the integers that are the power remainder of n and when divided by m equal r 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Sequence.py 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

def power_remainder(n, m, r): 
    x = 1
    while True:
        a = pow(x, n)
        if a % m == r:
            yield a
        x += 1
         
# end

def common_terms(g, h): 
    button = next(g)
    flag = next(h) 
    while True: 
        if button > flag: flag = next(h)
        if button < flag: button = next(g)
        elif button == flag:
            yield button 
            button = next(g)
   # end
# end


def main():
    #print(power_remainder(2,3,1))
    #print(common_terms(power_remainder(2, 3, 1), power_remainder(3, 5, 4)))
    
    A = power_remainder(2, 3, 1)
    B = power_remainder(3, 5, 4)
    C = common_terms(power_remainder(2, 3, 1), power_remainder(3, 5, 4))
    
    print()
    for i in range(15):
        s = "  {0:<12}{1:<12}{2:<12}".format(next(A), next(B), next(C))
        print(s)
        #end
    print()

   

# end

#-------------------------------------------------------------------------------
if __name__=='__main__':

   main()

# end