#!/usr/bin/env python

import sys
import re

##########################
#Procedure to Split the lines into individual variables. 
#Input - Line of data
#Output - InvoiceNo_out , CustomerID_out , Country_out , Amount_Spent_out , InvoiceMonth_out 
##########################
def split_lines(line_in):
  InvoiceNo_out     = line_in[0]                           #Read Invoice Number
  CustomerID_out    = line_in[6]                           #Read Customer ID
  Quantity_out      = line_in[3]                           #Read Question  
  UnitPrice_out     = line_in[5]                           #Read Unit Price
  Country_out       = line_in[7]                           #Read Country
  Country_out       = Country_out.replace('\r', '').replace('\n', '')  			#Strip Line Return
  InvoiceDate_out   = line_in[4]                           				#Read Invoice Date
  Amount_Spent_out = 0	
  Amount_Spent_out  = int(float(Quantity_out)) * int(float(UnitPrice_out))         	#Calculate Amount Spent
  InvoiceMonth_out, date_out, year_time_out  = InvoiceDate_out.split('/')      		#Get Month
  InvoiceMonth_out  = str(InvoiceMonth_out).zfill(2)    				#Hard Pad 2 Characters
  return InvoiceNo_out , CustomerID_out , Country_out , Amount_Spent_out , InvoiceMonth_out

##########################
#Main Procedure 
##########################  
def main(argv):
  line = sys.stdin.readline()                       #Read Header
  line = sys.stdin.readline()                       #Read first Line

  while line:
      line = line.split(",")                            #Split by CSV
      InvoiceNo,CustomerID,Country,Amount_Spent,InvoiceMonth = split_lines(line)
      if CustomerID != '' and InvoiceNo[0] != 'C':	#Exclude C invoices and Null Invoices
          print(Country+'+'+InvoiceMonth+"\t"+str(Amount_Spent)+'+'+CustomerID)
      line = sys.stdin.readline()                       #Read Line
     
#Note there are two underscores around name and main
if __name__ == "__main__":
  main(sys.argv)