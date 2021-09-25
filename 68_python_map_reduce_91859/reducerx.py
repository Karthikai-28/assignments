#!/usr/bin/env python
 
import sys
import pandas as pd
from collections import Counter

##########################
#Procedure to find the biggest spender.
#input
#list of values by the following keys, invoice month, country,
#output
#InvoiceMonth_in, Country_in, big spender
##########################
def print_rows(list_in,InvoiceMonth_in,Country_in):	    
#Combine the Amounts for each Customer.
    d = {x:0 for x,_ in list_in}
    for name,num in list_in: d[name] += num
    Result = map(tuple, d.items())

#Find the max value in the List.
    max_Cust = max(Result,key=lambda item:item[1])[0]
    max_val = max(Result,key=lambda item:item[1])[1]

#If there is a tie print them all
    for first,args in Result:
        if args == max_val:
            print(InvoiceMonth_in + ', ' + Country_in + ', ' + first)

##########################
#Main procedure 
##########################
def main(argv):
  prev_Country = None
  prev_InvoiceMonth = None
  prev_CustomerID = None
  current_amt = 0
  cust_list = []	

# Read values.    
  for line in sys.stdin:
    line = line.strip()
    (Country_InvoiceMonth,Amount_Spent_CustomerID) = line.split('\t')
    (Country,InvoiceMonth) = Country_InvoiceMonth.split('+')
    (Amount_Spent,	CustomerID) = Amount_Spent_CustomerID.split('+')


    Amount_Spent = int(Amount_Spent)
	
# if this is the first iteration
    if not prev_Country:
      prev_Country 		= Country
      prev_InvoiceMonth 	= InvoiceMonth
      prev_CustomerID 	= CustomerID

# Check if there is a change in key        
    if prev_Country == Country:
        if prev_InvoiceMonth == InvoiceMonth:
          if prev_CustomerID == CustomerID:
            cust_list.append((CustomerID,Amount_Spent))
          else:
            cust_list.append((CustomerID,Amount_Spent))
        else:
          print_rows(cust_list,prev_InvoiceMonth,prev_Country)	           
          cust_list = []	   
          cust_list.append((CustomerID,Amount_Spent))
    else:
        print_rows(cust_list,prev_InvoiceMonth,prev_Country)	           
        cust_list = []	   
        cust_list.append((CustomerID,Amount_Spent))
    
    prev_Country = Country
    prev_InvoiceMonth = InvoiceMonth
    prev_Customer_ID = CustomerID

    print_rows(cust_list,prev_InvoiceMonth,prev_Country)	           #Call the procedure to print
    cust_list = []


#Note there are two underscores around name and main
if __name__ == "__main__":
  main(sys.argv)