#!/usr/local/bin/python3
import sys 

name = input("File Name: ")

for line in reversed(list(open(name))):
    print(line.rstrip())
