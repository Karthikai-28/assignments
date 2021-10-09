def exact_change(user_total):
    num_dollars, user_total = divmod(user_total, 100)
    num_quarters, user_total = divmod(user_total, 25)
    num_dimes,    user_total = divmod(user_total, 10)
    num_nickels,  user_total = divmod(user_total, 5)
    num_pennies = round(user_total / 1, 0)
    return list(map(int, [num_dollars, num_quarters, num_dimes, num_nickels, num_pennies]))

if __name__ == '__main__':
    input_val = int(input())    
    num_dollars, num_quarters, num_dimes, num_nickels, num_pennies = exact_change(input_val)
    print("{} quarters, {} dimes, {} nickels, {} pennies".format(
          num_quarters, num_dimes, num_nickels, num_pennies))