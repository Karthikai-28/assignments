#!/usr/bin/env python

import sys
import re
###########################
#Procedure to split the lines.
#Input List with person, connection1 connection2 connection3...
#Output person_out, list of connections
###########################
def split_lines(line_in):
  person_out      = line_in[0].strip()
  connections_out = line_in[1].replace('\n', '')
  connections_out = connections_out.strip()
  connections_out = connections_out.split()
  return person_out,connections_out
###########################

##########################  
#Procedure to create a list of connections.
#input - person, list of friends
#ouput - list of all (person, friend) combinations.
##########################  
def create_connection_friend_list(connection_in, friend_in):
  list_out = [] 
  connection_in_strip = connection_in.strip()
  for friends in friend_in:
     if friends != ' ' and friends != '' and friends != '\n' :
        list_out.append((connection_in_strip,friends))
  return list_out

#########################  
#Procedure to print all combinations of person, friend, and friends of friends.
#Input - List of person and friends.
#Output - Print Person + Friends, and Possible Future Friends.
#########################
def create_connection_friend_friend_list(list_in):
  list_in_loop = list_in

  for first,args in list_in:
      for first2,args2 in list_in_loop:
         if args == first2:
            print(first+"\t"+args+'+'+args2)
  return 
#########################
#main procedure
#########################
def main(argv):
  connection_friend_list  =[]                       	#Reset List

  line = sys.stdin.readline()                       	#Read first Line

  while line:
      line = line.split(":")                		#Split by Colan
      Person,Connections = split_lines(line)

      call_list = []
      call_list = create_connection_friend_list(Person,Connections)
      connection_friend_list.extend(call_list)
      
      line = sys.stdin.readline()                       #Read Line
 
  create_connection_friend_friend_list(connection_friend_list)

#Note there are two underscores around name and main
if __name__ == "__main__":
  main(sys.argv)