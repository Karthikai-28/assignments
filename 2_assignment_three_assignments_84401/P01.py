number = int(input("Enter a positive number starting number: "))

if (number > 0):
    number_ = 0
    while (number >= number_):
        print(number_,'and cube of ',number_," is: ",number_**3)
        number_ = number_ + 1
    
else:
    print("Sorry,", number, "is not a positive number. Try again!")