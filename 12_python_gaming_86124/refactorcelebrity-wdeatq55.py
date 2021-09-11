def generateQuote(quote, accentName):
    '''
Transform the quote to a script for the accent provided
   quote - the quote to change
   accentName - the name of the accent to generate
 return the modified quote
    '''
    out = ""
    tokens = quote.split(" ")
    if accentName =="Canadian":
        out = quote + ", eh?";
    elif accentName =="Shatner":
        for token in tokens:
            out = out + token + "...\n"
    elif accentName =="Valley Girl":
        for count, token in enumerate(tokens):
            out = out + "like ";
            out = out + token;
            if count < len(tokens) - 1:
                out = out + " ";
    elif accentName =="Pirate":
        for count, token in enumerate(tokens):
            for char in token:
                if char == 'r' or char == 'R':
                    out = out + "RRR";
                out = out + char
            if count < len(tokens) - 1:
                out = out + " ";
    elif accentName =="Zatanna":
        for count, token in enumerate(tokens):
            out = out + token[::-1];
            if count < len(tokens) - 1:
                out = out + " ";
    elif accentName =="Yoda":
        write = False
        save = ""
        for count, token in enumerate(tokens):
            if (write):
                write = False
                out = out + token + " " + save
                if count < len(tokens) - 1:
                    out = out + " ";
            else:
                write = True
                save = token
        if write:
            out = out + save + "\n";
    return out
    
TESTS = [["Canadian", "Four score and seven years ago, eh?"],
         ["Valley Girl", "like Four like score like and like seven like years like ago"],
         ["Shatner", "Four...\nscore...\nand...\nseven...\nyears...\nago...\n"],
         ["Pirate", "FouRRRr scoRRRre and seven yeaRRRrs ago"],
         ["Zatanna", "ruoF erocs dna neves sraey oga"],
         ["Yoda", "score Four seven and ago years"]]
    
def main():
    quote = "Four score and seven years ago"
    print("Original Quote: \"" + quote + "\"");
    for test in TESTS:
        print(".....................................")
        print("Testing ", test[0], ":")
        answer = generateQuote(quote, test[0])
        if answer == test[1]:
            print("Success")
        else:
            print("Your code returned the quote:...")
            print(answer)
            print("but I expected: ")
            print(test[1])
main()
