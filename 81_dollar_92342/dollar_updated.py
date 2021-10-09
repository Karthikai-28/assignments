def exact_change(user_total):
#Check if input is less than 1
    if user_total<=0:
        print("no change")

    else: 
        num_dollars, user_total = divmod(user_total, 100)
        num_quarters, user_total = divmod(user_total, 25)
        num_dimes,    user_total = divmod(user_total, 10)
        num_nickels,  user_total = divmod(user_total, 5)
        num_pennies = round(user_total / 1)

        if num_dollars >= 1:
            if num_dollars == 1:
                    print(str(num_dollars)+" dollar")
            else:
                    print(str(num_dollars)+" dollars")

        if num_quarters >= 1:
            if num_quarters == 1:
                    print(str(num_quarters)+" quarter")
            else:
                    print(str(num_quarters)+" quarters")

        if num_dimes >= 1:
            if num_dimes == 1:
                    print(str(num_dimes)+" dime")
            else:
                    print(str(num_dimes)+" dimes")

        if num_nickels >= 1:
            if num_nickels == 1:
                    print(str(num_nickels)+" nickel")
            else:
                    print(str(num_nickels)+" nickels")

        if num_pennies >= 1:
            if num_pennies == 1:
                    print(str(num_pennies)+" penny")
            else:
                    print(str(num_pennies)+" pennies")
    return num_dollars, num_quarters, num_dimes, num_nickels, num_pennies
        
if __name__ == '__main__':
    input_val = int(input())    
    num_dollars, num_quarters, num_dimes, num_nickels, num_pennies = exact_change(input_val)