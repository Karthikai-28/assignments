#!/usr/bin/env python

import sys
##########################
#Main Procedure
##########################
def main(argv):
  current_word  = None
  current_count = 0
  word = None
  for line in sys.stdin:
    line = line.strip()
    word, count = line.split('\t', 1)			#Read in Words, and Count.
    count = int(count)
    if current_word == word:
      current_count += count
    else:
      if current_word:
        print('%s:%s' % (current_word, current_count))	#Prints out the Word, and Total Count.
      current_count = count
      current_word = word
  if current_word == word:
    print('%s:%s' % (current_word, current_count))	#For Last Iteration, Print the output.

#Note there are two underscores around name and main
if __name__ == "__main__":
  main(sys.argv)