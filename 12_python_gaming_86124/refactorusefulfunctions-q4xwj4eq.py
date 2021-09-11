# Annotate this code to identify what each segment is doing.  Identify places where
#   you could split the code into multiple functions
# Using your analysis, refactor this code to simplify and make it resuable by
#   making additional functions
def main():
    file = open("refactorUsefulFunctions.py", 'r')

    linesOfCode = []
    for line in file:
        linesOfCode.append(line)

    totalLinesOfCode = len(linesOfCode)

    for line in linesOfCode:
        if len(line.strip()) == 0:
            linesOfCode.remove(line)
    totalNonBlankLinesOfCode = len(linesOfCode)
    totalBlankLines = totalLinesOfCode - totalNonBlankLinesOfCode;

    '''
      Avoid picking up # in block comments too
    '''
    REALLY_TRICKY_TEST = "\"#"
    totalComments = 0
    findMe = "#"
    inBlockQuote = False
    for line in linesOfCode:
        #The challenges is when you have a full quote before the comment
        # so you have to check if you are in a quote before you count any character
        inQuote = False
        inComment = False
        for index in range(len(line) - len(findMe)):
            if line[index] == "#":
                inComment = True

            # This logic is not perfect, as if you have ''''' it will get confused
            if not inQuote and not inComment and \
               index + 3 < len(line) and line[index:index + 3] == "'''":
                inBlockQuote = not inBlockQuote
                
            # This logic is also flawed, as it does not look for ' and " strings 
            if not inBlockQuote and line[index] == "\"":
                if inQuote and line[index - 1] == "\\":
                    pass # it is a quote character literal
                else:
                    inQuote = not inQuote

            if not inQuote and not inBlockQuote and \
               index + len(findMe) < len(line) and line[index:index + len(findMe)] == findMe:
                totalComments = totalComments + 1
                break # can't have a second on a line

    
    numberOfFunctions = 0
    findMe = "def"
    inBlockQuote = False
    for line in linesOfCode:
        #The challenges is when you have a full quote before the comment
        # so you have to check if you are in a quote before you count any character
        inQuote = False
        inComment = False
        for index in range(len(line) - len(findMe)):
            if line[index] == "#":
                inComment = True

            # This logic is not perfect, as if you have ''''' it will get confused
            if not inQuote and not inComment and \
               index + 3 < len(line) and line[index:index + 3] == "'''":
                inBlockQuote = not inBlockQuote
                
            # This logic is also flawed, as it does not look for ' and " strings 
            if not inBlockQuote and line[index] == "\"":
                if inQuote and line[index - 1] == "\\":
                    pass # it is a quote character literal
                else:
                    inQuote = not inQuote

            if not inQuote and not inBlockQuote and \
               index + len(findMe) < len(line) and line[index:index + len(findMe)] == findMe:
                numberOfFunctions = numberOfFunctions + 1
                break # can't have a second on a line
    
    print("This code has a total of", totalLinesOfCode, "of which", totalBlankLines, \
          "were blank and", totalNonBlankLinesOfCode, "had content")

    print("The author included", numberOfFunctions, "functions and", totalComments, "comments")
main()
