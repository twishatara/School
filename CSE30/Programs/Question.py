#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 6
# Description: this is a program that plays the other side of a guessing game. The user picks a number after inputting a range and then gives the program hints so that the program can guess the number
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# BinarySearch.py 
#--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

print("\n\nEnter two numbers, low then high.")
low = int(input("low = "))
high = int(input("high = "))

while(low>high):
    print("\nPlease enter the smaller followed by the larger number.")
    low = int(input("low = "))
    high = int(input("high = "))

print("\nThink of a number in the range %d to %d."%(low,high))

if(low == high):
    print("\nYour number is %d. I found it in 0 guesses.\n\n"%(low))
    exit()
guess = 0 

m = (high+low)//2

choices = ['L', 'G', 'E', 'l', 'g', 'e']

print("\nIs your number Less than, Greater than, or Equal to %d?"%(m))
choice = input("Type 'L', 'G' or 'E': ")

while(choice not in choices):
    choice = input("\nPlease type 'L', 'G' or 'E': ")
guess += 1

if(choice == 'e' or choice == 'E'):
    print("\nI found your number in 1 guess.\n\n")

if(choice == 'g' or choice == 'G' and guess == 1 and high == low+1): 
    print("\nYour number is %d. I found it in %d guess.\n\n"%(high, guess))
    exit()

while(choice != 'e' and choice != 'E'):
    
    if(choice == 'l' or choice == 'L'):
        high = m-1

    elif(choice == 'g' or choice == 'G'):
        low = m+1

    if(high == low):
        print("\nYour number is %d. I found it in %d guesses.\n\n"%(low, guess))
        break

    if(high<low):
        print("\nYour answers have not been consistent.\n\n")
        break

    m = (high+low)//2

    print("\nIs your number Less than, Greater than, or Equal to %d?"%(m))
    choice = input("Type 'L', 'G' or 'E': ")
    
    while(choice not in choices):
        choice=input("\nPlease type 'L', 'G' or 'E': ")
    guess += 1

    if(choice == 'e' or choice == 'E'):
        print("\nI found your number in %d guesses.\n\n"%(guess))
