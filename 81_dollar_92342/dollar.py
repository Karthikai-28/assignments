def change(amnt):
    num_quarters, amnt = divmod(amnt, 0.25)
    num_dimes,    amnt = divmod(amnt, 0.10)
    num_nickels,  amnt = divmod(amnt, 0.05)
    num_pennies = round(amnt / 0.01, 0)

    return list(map(int, [num_quarters, num_dimes, num_nickels, num_pennies]))

if __name__ == '__main__':
    amnt = float(input("Enter an amount in USD: "))
    num_quarters, num_dimes, num_nickels, num_pennies = change(amnt)
    print("{} quarters, {} dimes, {} nickels, {} pennies".format(
          num_quarters, num_dimes, num_nickels, num_pennies))