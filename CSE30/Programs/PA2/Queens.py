import sys 
import math 

def placeQueen(B, i, j): 
    B[i][j] = 1 
    B[i][0] = j #indicates existence of queen
    n = len(B) - 1
    for row in range(i+1, n+1): 
        for column in range(1, n+1): 
            if column == j: 
                B[row][column] -= 1 #decrements by 1 // if (i,j) is the square of the queen this accuounts for every square under (i,j)   
            else: 
                slope = (i - row) / (j - column) 
                if slope == 1 or slope == -1:
                    B[row][column] -= 1 #decrements diagionaly // if (i,j) is the square of the queen this accounts for the right and left diagonals of the square under (i,j)
    
def removeQueen(B, i, j): #reverses everything place queens did
    B[i][j] = 0 
    B[i][0] = 0 
    n = len(B) - 1
    for row in range(i+1, n+1):
        for column in range(1, n+1):
            if column == j: 
                B[row][column] += 1 #adds one to bring back to 0 
            else: 
                slope = (i - row) / (j - column) 
                if slope == 1 or slope == -1:
                    B[row][column] += 1
            
def printBoard(B):
    t = []
    for i in range(1,len(B)): #checks rows 1 to input n
        t.append(B[i][0])
    print(tuple(t))

def findSolutions(B, i, mode): # NEED HELP PLEASE IM STUPID 
    acc = 0 
    if i > len(B) - 1:
        if mode == "-v":
            printBoard(B)
        return 1  
    for Q in range(1, len(B)): 
        if B[i][Q] == 0:
            placeQueen(B, i , Q)
            acc += findSolutions(B, i+1, mode) #add the new place queens to the table
            removeQueen(B, i, Q) #remove the queen is it j or 1?
    return acc             
        
def main():
    if len(sys.argv) == 1: #if only the file name is given
        print("Usage: python3 Queens.py [-v] number\nOption: -v verbose output, print all solutions")
        #print("Option: -v verbose output, print all solutions")
        sys.exit()

    if len(sys.argv) == 2 and sys.argv[1] == str(sys.argv[1]): #if a single word is given 
        print("Usage: python3 Queens.py [-v] number\nOption: -v verbose output, print all solutions")        
        sys.exit()
        if len(sys.argv) == 2 and isinstance(sys.argv[1], int): #if only a number is given THIS DOESNT WORK
            print(str(n)+ "-Queens has " + str(findSolutions(B, 1, mode)) + " solutions")
            
    if len(sys.argv) == 3: #verbose case
        n = int(sys.argv[2])
        mode = str(sys.argv[1])
        #B = (n+1) * [(n+1)*[0]]  
        B = []
        for a in range(n+1):
            B.append([0]*(n+1))
        print(str(n)+ "-Queens has " + str(findSolutions(B, 1, mode)) + " solutions")
        sys.exit()
    
    
    
'''
        else: 
            isinstance(sys.argv[2], str)
            print("Usage: python3 Queens.py [-v] number")
            print("Option: -v verbose output, print all solutions")
     

   


    if len(sys.argv) == 2: #if only -v or 4 are given 
        n = sys.argv[1]
        if isinstance(n, int): #checks if the argument is an int or a str 
            n = int(sys.argv[1]) #if int => assign n as an int 
            findSolutions(B, i, None) #run outside of verbose
        elif isinstance(n, str): #the argument is a str 
            #n = str(sys.argv[1]) #assign n as an str 
            #if isinstance(first, str):
                #first = str(sys.argv[2])
            print("Usage: python3 Queens.py [-v] number ")
            print("Option: -v verbose output, print all solutions")
            sys.exit()
    if len(sys.argv) == 3: 
        first = sys.argv[1] 
        n = sys.argv[2]
        if isinstance(first, str) and isinstance(n, int):
            first = str(sys.argv[1])
            n = int(sys.argv[2])
            findSolutions(Board(n), i, mode)
            print("check1")



    if len(sys.argv) == 2 and sys.argv[1] == int(sys.argv): 
        findSolutions(Board(n), i, None)
    else len(sys.argv) == 3 and sys.argv[1] = str(sys.argv) and sys.argv[2] == int(sys.argv[])

'''


#-------------------------------------------------------------------------------------------------------------------------------------------
if __name__=='__main__':

   main()
