#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 4
# The compute picks a number and the user has 3 tires to guess the number. After each guess the program will tell the user if the guess it was too high, too low, or correct
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Guess.py 
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

import random

number = random.randint(1, 10)

count = 0
tries = 2  
guess_try = ["first", "second", "third"]

print("\nI'm thinking of an integer in the range 1 to 10. You have three guesses.")
while count <= tries :
    guess = int(input("\nEnter your "+ guess_try[count] + " guess: " ))
    count += 1
    if guess < number :
        print("Your guess is too low.")
    elif guess == number :
        print("You win!\n") 
        break 
    elif guess > number :
        print("Your guess is too high.")
           
else:
    print ("\nYou lose. The number was {}.\n".format(number))