from random import randint

varities = ["Rock", "Paper", "Scissor"]

def menu():
    print("1. Throw Rock")
    print("2. Throw Paper")
    print("3. Throw Scissor")
    print("4. Quit")
    print(" ")

    
def rules():
    print("Rules of the game:")
    print("==================")
    print("Rock beats Scissors")
    print("Paper beats Rock")
    print("Scissor beats paper")
    print(" ")
    
def main():
    menu()
    
    AI = varities[randint(0,2)]
    
    Human = False
    
    i = 0
    j = 0
    a = 0
    b = 0
       
    while Human == False:
        Human = input("Select your option: ")
        if Human == AI:
            print(" ")
            print("==Results==")
            print("Tie")
            print(" ")
            
        elif Human in ("1", "Rock", "rock", "ROCK", "r"):
            if AI == "Paper":
                print(" ")
                print("==Results==")
                print(" ")
                print("You Lose!, Rock was covered by your Paper")
                j = j+1
                Human_ = False
            else:
                print(" ")
                print("==Results==")
                print(" ")
                print("You win!, Rock samshes the Scissor")
                i = i+1
                Human_ = True
                
        elif Human in ("2", "Paper", "PAPER", "paper", "p"):
            if AI == "Scissors":
                print(" ")
                print("==Results==")
                print(" ")
                print("You lose! Scissor is Cutting out the Paper")
                j = i+1
                Human_ = False
            else:
                print(" ")
                print("==Results==")
                print(" ")
                print("You win! Paper Covers the entire Rock")
                i = i+1
                Human_ = True
                
        elif Human in ("3", "Scissor", "scissor", "SCISSOR", "s"):
            if AI == "Rock":
                print(" ")
                print("==Results==")
                print(" ")
                print("You lose!, Rock Smashes your Paper")
                j = j+1
                Human_ = False
            else:
                print(" ")
                print("==Results==")
                print(" ")
                print("You win!, Scissor is Cutting out the paper")
                i = i+1    
                Human_ = True  
                
        elif Human in ("4", "Quit", "quit", "q"):
            print("Bye! See you again...")
            exit()
            
        else:
            print("That option entered by Human is not correct")
            main()
            break
        
        
        if (Human_ == True):
            b = 0
            a = a+1
        else:
            a = 0
            b = b+1
        
        print("Wins..................: ", i)
        print("Losses................: ", j)
        print("Longest Win Streak....: ", a)
        print("Longest Lose Streak...: ", b)
        print(" ")
        
        
        Human = False
        AI = varities[randint(0,2)]
    
if __name__ == "__main__":
    rules()
    main()