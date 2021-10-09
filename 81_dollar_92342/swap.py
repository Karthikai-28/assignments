def swapnumbers(a, b):
    temp = a
    a = b
    b = temp
    print("After Swapping two Number",(a, b))
    
if __name__ == '__main__':
    number1 = int(input(" Please Enter the First number : "))
    number2 = int(input(" Please Enter the Second number : "))
    print("Before Swapping two Number",(number1, number2))
    swapnumbers(number1, number2)