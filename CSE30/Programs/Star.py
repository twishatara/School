import turtle

#variable definitions 
n = int(input('Enter an odd integer greater than or equal to 3: ')) #user input
angle = 180.0-180.0/n #star formula

#window specifics
wn = turtle.Screen() #window
wn.bgcolor("white")
wn.title(str(n)+" pointed star")

#star specifics 
star = turtle.Turtle() #turtle named star
star.color("blue", "green") #pen color, star color
star.pensize(2)
star.penup()
star.setpos(-150,0)
star.pendown()

star.speed(0) #turtle/drawing speed
star.begin_fill() #star color 
for i in range(n):
    star.forward(300)
    star.right(angle)
    star.dot(10, "red")
star.end_fill()

star.hideturtle()
wn.mainloop()

# Twisha Sharma 
# tvsharma@ucsc.edu
# CSE 20 - 02
# p2 - Star.py 



