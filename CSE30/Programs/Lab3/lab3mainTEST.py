#lab3main


def main():
    x = Rational(1137,158)
    L = []
    for i in range(265):  
        flag = next(pi_gen()) 
        L.append(flag) 
    r = GCF2R(L) 
    print("")
    print(str(r))
    print("")
    getcontext().prec = 101
    print(Decimal(r.numer) / Decimal(r.denom)) #deimal equivalent
    print("")
    #l1 = [7,5,10,3]
    button = R2CF(x)
    print(button)
    print("")

    '''
    print("")
    r = GCF2R(pi_gen()) #returns rational of pi?
    print(r)
    print("")
    getcontext().prec = 100 
    print(Decimal(r.numer) / Decimal(r.denom))
    print("")
    l1 = [0,4,1,1,3,4]
    print(CF2R(l1))
    print("")
    '''
    #R1 = Rational(1137,158)
    #print(R2CF(R1))
    #l1 = [0,4,1,1,3,4]
    #print(CF2R(l1))

    
    
if __name__=='__main__': 
   main()