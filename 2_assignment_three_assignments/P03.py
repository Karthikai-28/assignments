def main():
    number = int(input("Enter your starting number: "))
    while True:
            
        print("Enter A for Add, S for Subtract, M for multiply, or D for Divide to perform on", number,"or enter -999 to end:")
        option = input()
        
        if option == "A":
            print("Add", number, "with what value: ")
            add = int(input())
            ans = number + add
            print("The result is ",ans)
            
        elif option == "S":
            print("Add", number, "with what value: ")
            subtract = int(input())
            ans = number - subtract
            print("The result is ",ans)
            
        elif option == "M":
            print("Add", number, "with what value: ")
            multiply = int(input())
            ans = number * multiply
            print("The result is ",ans)
            
        elif option == "D":
            print("Add", number, "with what value: ")
            divide = int(input())
            ans = number / divide
            print("The result is ",ans)
            
        elif option == "-999":
            print("Program ended with a result of ",ans)
            exit()
            
        else:
            print("Sorry",option,"is not a valid operation. Try Again!")
        
if __name__ == "__main__":
    main()