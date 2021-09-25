#!/usr/bin/env python

import sys
import re
##########################
#Main Procedure
##########################
def main(argv):
  line = sys.stdin.readline()			#read the first line
  pattern = re.compile("[a-zA-Z0-9]+")
 
  while line:
    for word in pattern.findall(line):
        vowels = ''
        for i in word.lower():
            if(i=='a' or i=='e' or i=='i' or i=='o' or i=='u'):
                vowels += i
        vowels_sorted = sorted(vowels)
        vowels_print  = ''.join(vowels_sorted)
        if len(vowels_print) == 0:		#If there are no vowels, return a space
          print("_"+"\t"+"1")
        if len(vowels_print) >= 1:		#If there are more than 1 vowels, print the combination with 1.
          print(vowels_print+"\t"+"1")

    line = sys.stdin.readline()
#Note there are two underscores around name and main
if __name__ == "__main__":
  main(sys.argv)
