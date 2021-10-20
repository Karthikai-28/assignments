def smallest(num1, num2, num3):
    if (num1 < num2) and (num1 < num3):
        smallest_num = num1
    elif (num2 < num1) and (num2 < num3):
        smallest_num = num2
    else:
        smallest_num = num3
    print("The smallest numbers is", smallest_num)
    
def equal(num1, num2, num3):
    if (num1 == num2 == num3):
      print("There are three equal numbers.")
    elif (num1 == num2):
      print("There are two equal numbers.")
    elif (num1 == num3):
      print("There are two equal numbers.")
    elif (num2 == num3):
      print("There are two equal numbers.")
    else:
      print("There are zero equal numbers.")

number1 = int(input())
number2 = int(input())
number3 = int(input())

smallest(number1, number2, number3)
equal(number1, number2, number3)