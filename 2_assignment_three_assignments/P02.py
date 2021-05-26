def main():
    i = 0
    while True:
        number = int(input("Enter a number between 3 and 12: "))

        if (number >= 3) and (number <= 12):
            print("Here is your square! ")
            print(number**2)
            i = i + 1
        else:
            print("Sorry",number, "is not in the range of 3 and 12. Try Again!")
        
        option = input("Would like to create another? (Enter Y or Yes to continue or N or No to Quit)")
        if option in ("Y", "Yes"):         
            pass
        elif option in ("N", "No"):
            print("Thank you, you created", i ,"squares before quitting")
            exit()
        else:
            print(option,"is not a valid response. Please try again!")
            option = input("Would like to create another? (Enter Y or Yes to continue or N or No to Quit)")

    
            
if __name__ == '__main__':
    main()
    