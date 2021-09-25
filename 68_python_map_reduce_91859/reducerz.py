#!/usr/bin/env python
#Be sure the indentation is correct and also be sure the line above this is on the first line

import sys
from collections import Counter
###########################
#procedure to loop throught the contacts, and the list of friends.
#Input - Contact, and list of friends
###########################
def loop_list(contact_in,list_in):
  only_friend_list = []
  only_friend_set = set()

  friend_friend_list = []
  friend_friend_counter = []

  might_list = []
  might_set = set()

  probably_list = []
  probably_set = set()

  contact_set = set()
  contact_set.add(contact_in)

# Recreate the list of friends, and the list of possible friends 
  for val in list_in:
      only_friend_list.append(val[1])
      friend_friend_list.append(val[2])
  
  only_friend_set = set(only_friend_list)                   # create unique set of friends. 
  friend_friend_counter = (Counter(friend_friend_list))     # count list of friends friends.

# build might list  
  for val in friend_friend_counter:
      if friend_friend_counter[val] == 2 or friend_friend_counter[val] == 3:
        might_list.append(val)
  might_set = set(might_list)					#create Set
  might_set = might_set - only_friend_set			#remove existing friends
  might_set = might_set - contact_set				#remove self

# build probably list
  for val in friend_friend_counter:
      if friend_friend_counter[val] >= 4:
        probably_list.append(val)
  probably_set = set(probably_list)				#create Set
  probably_set = probably_set - only_friend_set			#remove existing friends
  probably_set = probably_set - contact_set			#remove self
  
#Output the Contact, Might Friends, and Probable Friends.
  sys.stdout.write(contact_in + ':')	

  if len(might_set) >=1:
    might_str = str(might_set)
    might_str = might_str.strip('set([').strip('])').strip(')').strip('(').strip(' ').replace("'","")
    sys.stdout.write(' Might(') 
    sys.stdout.write(might_str)        
    sys.stdout.write(')')

  if len(probably_set) >=1:	
    prob_str = str(probably_set)
    prob_str = prob_str.strip('set([').strip('])').strip(')').strip('(').strip(' ').replace("'","")
    sys.stdout.write(' Probably(')
    sys.stdout.write(prob_str)        
    sys.stdout.write(')') 
	
  print('')   # Force line return
     
  return

###########################
#Main Procedure to loop throught the contacts, and the list of friends.
###########################
def main(argv):
    
  friend_list = []
  prev_Contact = None  

  for line in sys.stdin:

    line = line.strip()
    (Contact, Friend_Friends_Friend) = line.split('\t')
    (Friend,Friends_Friend) = Friend_Friends_Friend.split('+')

# if this is the first iteration
    if not prev_Contact:
	    prev_Contact 		= Contact

#See if the key changes.    
    if prev_Contact == Contact:
      friend_list.append((Contact,Friend,Friends_Friend))
    else:
      loop_list(prev_Contact,friend_list)
      friend_list = []
      friend_list.append((Contact,Friend,Friends_Friend))
    
    prev_Contact 		= Contact
    
#last call
  loop_list(prev_Contact,friend_list)

#Note there are two underscores around name and main
if __name__ == "__main__":
  main(sys.argv)