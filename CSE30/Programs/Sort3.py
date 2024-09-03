#-------------------------------------------------------------------------------
#  Sort3.py
#  Sorts three (distinct) numbers in ascending order
#-------------------------------------------------------------------------------

def min3(a, b, c):
   if a<b: 
      m = a
   else:   
      m = b
   # end if-else

   if c<m: 
      m = c
   # end if

   return m
#end min3()

def max3(a, b, c):
   if a<b: 
      M = b
   else:   
      M = a
   # end if-else

   if M<c: 
      M = c
   # end if

   return M
# end max3()

def mid3(a, b, c):
   if a<b<c or c<b<a: 
      return b
   elif b<a<c or c<a<b: 
      return a
   elif a<c<b or b<c<a:  
      return c
   # end if-elif
   # what happens if they are not distinct?
# end mid3()


#-- main program --------------------------------------------------------------

print('Enter three numbers.')
x = float(input('First number: '))
y = float(input('Second number: '))
z = float(input('Third number: '))

print(min3(x,y,z), mid3(x,y,z), max3(x,y,z))

