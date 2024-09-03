#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 7
# Description: 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Probability.py
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

import random

def throwDice(m, k, R): 

    R = random.Random(237)
    t = []

    for dice in range(m):
        t.append(random.randrange(1, k+1))
    return tuple(t)

def main(SEED=237):

    random.seed(237)

    # NUMBER OF DICE
    m = int(input("\nEnter the number of dice: "))
    while m<1:
        print("The number of dice must be at least 1")
        m = int(input("Please enter the number of dice: "))

    # SIDES
    k = int(input("\nEnter the number of sides on each die: "))
    while k<2:
        print("The number of sides on each die must be at least 2")
        k = int(input("Please enter the number of sides on each die: "))

    # TRIALS
    n = int(input("\nEnter the number of trials to perform: "))
    while n<1: 
        print("The number of trials must be at least 1")
        n = int(input("Please enter the number of trials to perform: "))

    R = random.seed(237)
    freq = [0] * (m*k + 1)

    for _ in range(n):
        dice = throwDice(m, k, R)
        i = sum(list(dice))
        freq[i] += 1
    
    print("\n Sum     Frequency     Relative Frequency     Experimental Probability") #this is the title formatting of the chart/output
    print("-" * 70)
    
    for i in range(m,len(freq)): #this is the output/answers for the chart
        relFreq = freq[i]/n
        expProb = relFreq * 100
        print("{:4d}{:11d}{:18.5f}{:21.2f} %".format(i, freq[i], relFreq, expProb))
    
    print("") #blank line that seperates the chart from the new terminal prompt

if __name__=='__main__':
    main(SEED=237)