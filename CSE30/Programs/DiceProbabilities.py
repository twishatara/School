#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 7
# Description: 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# DiceProbabilities.py 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

import random 

def throwDice (m, k, R):
    fv = []
    for dice in range(m):
        fv.append(random.randrange(1, k+1))
    return tuple(fv)

def main(SEED=237):

    random.seed(237)

    print("")
    dices = int(input("Enter the number of dice: "))

    while dices <= 0:
        if dices <= 0: print('The number of dice must be at least 1')
        dices = int(input("Please enter the number of dices: "))

    sides = int(input("\nEnter the number of sides on each die: "))

    while sides <= 1: 
        if sides <= 1: print("The number of sides on each die must be at least 2")
        sides = int(input("Please enter the number of sides on each die: "))

    frequency = [0]*(dices*sides-dices+1)
    trials = int(input("\nEnter the number of trials to preform: "))

    while trials <= 0:
        if trials <=0: print("The number of trials must be at least 1 ")
        trials = int(input("Please enter the number of trials to preform: "))
    
    for trial in range(trials):
        fv = throwDice(dices,sides,frequency)
        total = sum(fv)
        frequency[total-dices]+=1
    
    print("{:>4}{:>15}{:>30}{:>30}".format("Sum","Frequency","Relative Frequency","Experimental Probability"))
    print("-"*79)
    
    for i in range(len(frequency)):
        print("{:>4}{:>12}{:>25.5}{:>25.2f}%".format(dices+i, frequency[i], frequency[i]/trials, frequency[i]*100/trials))

main(SEED=237)