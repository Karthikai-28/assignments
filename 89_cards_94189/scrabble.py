# -*- coding: utf-8 -*-
# 1. import modules and function
import sys
import string
from score_word import score_word

# 2. import scrabble dictionary 
with open("sowpods.txt","r") as infile:
    raw_input = infile.readlines()
    data = [datum.strip('\n') for datum in raw_input]

# 3. take in command line inputs to start the scrabble game
# 4. check if input is valid

try:
    argc = len(sys.argv)
    if argc != 2 and argc != 4:
        raise Exception("Please provide either one or three inputs.")
    else:
        rack = sys.argv[1].lower()
    wild_count = 0
    if rack == "":
        raise Exception("You did not provide any input. Please enter either letters, '*', or '?'.")
    
    if len(rack) > 7 or len(rack) < 2:
        raise Exception("Your input is either too short or too long. Please make sure they are 2 to 7 characters.")
    
    for tile in rack:
        if tile not in list(string.ascii_lowercase) and tile not in ["*","?"]:
            raise Exception("Your input is not valid. Please enter either letter, '*', or '?'. No other special characters or space.")
        
        elif tile in ["*","?"]:
            wild_count += 1
    
    if wild_count > 2:
        raise Exception("You have entered more than 2 wild cards. Please enter no more than 2 wild cards, either '*' or '?'.")
    
    if argc == 4:
        special_letter = sys.argv[2].lower()
        if special_letter not in rack or special_letter in ["*","?"]:
            raise Exception("Speical letter must be in rack and cannot be wildcard.")
        
        if len(special_letter) != 1:
            raise Exception("You should only specify one letter.")
            
        special_spot = sys.argv[3]
        if special_spot not in list(string.digits):
            raise Exception("Special spot should be an integer.")
        else:
            special_spot = int(special_spot)
            if special_spot == 0:
                raise Exception("Special spot should be a greater than zero integer.") 
                # assuming that the starting position is 1 (the 1st letter), although its index is 0.
            if special_spot > len(rack):
                raise Exception("The spot you specify exceeds the length of the rack.")
        
except Exception as e:
    print("An error has occurred: " + str(e))
    sys.exit()
    
# 5. check against data to find list of scrabble words for the input
def check_scrabble(item,rack): 
    rack_list = list(rack)
    real_item = item
    for char in item:
        if char in rack_list:
            rack_list.remove(char)
        elif "*" in rack_list:
            rack_list.remove("*")
            real_item = item.replace(char, "", 1) 
            # in the case of wildcard, the char that replaces the wildcard should not be counted.
        elif "?" in rack_list:
            rack_list.remove("?")
            real_item = item.replace(char, "", 1)
        else:
            return 0
            
    return item,real_item

valid_list = []
for item in data:
    found = check_scrabble(item.lower(),rack)
    if found != 0:
        if argc == 4:
            if len(item) >= special_spot:
                if item.lower()[special_spot - 1] == special_letter:
                    valid_list.append(found)
        else:
            valid_list.append(found)
            
# 6. calculate the score of each srabble word
word_score = [(score_word(valid_word[1]), valid_word[0]) for valid_word in valid_list]

# 7. output the results in sorted order
word_score.sort(key = lambda tup: (tup[0],tup[1]), reverse=True)
for pair in word_score:
    print("(" + str(pair[0]) + ", "+ pair[1] + ")")

print("Total number of words:", len(word_score))