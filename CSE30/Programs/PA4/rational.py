#-------------------------------------------------------------------------------
# Twisha Sharma 
# tvsharma@ucsc.edu
# Programming Assignment 4
# Description: 
#------------------------------------------------------------------------------
# rational.py 
#------------------------------------------------------------------------------
from rational import *
from decimal import * 


def _gcd(a, b): 
    while a % b != 0:
        olda = a
        oldb = b
        a = oldb
        b = olda % oldb
    return b

class Rational(object):
    def __init__(self, n, d=1):
        # initialize a Rational object.
        fac = _gcd(n, d)
        self.numer = n // fac
        self.denom = d // fac
    
    def numer(self):
        # returns the numerator (use the @property decorator)
        return '({})'.format(self.numer)
    
    def denom(self): 
        # returns the denominator (use the @property decorator)
        d = 1
        return '({}/{})'.format(self.denom, d)

    def __add__(self, other):
        # return the sum of two rational numbers.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        s = (a * d)+(c * b)
        k = (b * d) 
        return Rational(s, k)

    def __eq__(self, other):
        # return True if self == other, False otherwise.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        self.numer = a * d
        self.denom = b * d
        other.numer = c * b
        other.denom = d * b
        return self.numer == other.numer

    def __float__(self):
        # return the float equivalent of self.
        a = self.numer 
        b = self.denom
        return float(a / b)

    def __ge__(self, other):
        # return true if self >= other, False otherwise.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        self.numer = a * d
        self.denom = b * d
        other.numer = c * b
        other.denom = d * b
        return self.numer >= other.numer

    def __gt__(self, other):
        # return true if self > other, False otherwise.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        self.numer = a * d
        self.denom = b * d
        other.numer = c * b
        other.denom = d * b
        return self.numer > other.numer

    def __le__(self, other):
        # return true if self <= other, False otherwise.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        self.numer = a * d
        self.denom = b * d
        other.numer = c * b
        other.denom = d * b
        return self.numer <= other.numer

    def __lt__(self, other):
        # return true if self < other, False otherwise.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        self.numer = a * d
        self.denom = b * d
        other.numer = c * b
        other.denom = d * b
        return self.numer < other.numer

    def __mul__(self, other):
        # return the product of two rational numbers. 
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        s = a * c
        k = b * d 
        return Rational(s, k)

    def __ne__(self, other):
        # return False if self == other, True otherwise.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        if a == c and b == d:
            return False 
        else: 
            return True 

    def __repr__(self):
        # return the detailed string representation of a rational number.
        a = self.numer 
        b = self.denom
        return 'rational.Rational({}, {})'.format(a, b)

    def __str__(self):
        # return the string representation of a rational number.
        a = self.numer 
        b = self.denom
        if (b == 1):
            return str(a) + "/" + str(b)
        else:
            return str(a) + "/" + str(b)

    def __sub__(self, other):
        # return the difference of two rational numbers.
        a = self.numer 
        b = self.denom
        c = other.numer
        d = other.denom
        s = (a * d) - (c * b)
        k = (b * d)
        return Rational(s, k)
    
    def __truediv__(self, other):
        # return the quotient of two rational numbers.
        return self * other.inverse()

    def inverse(self):
        # return the multiplicative inverse of a rational number.
        a = self.numer
        b = self.denom
        return Rational(b, a)