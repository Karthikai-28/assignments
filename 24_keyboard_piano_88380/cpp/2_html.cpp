#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main ()
{
        const char TAG = '<', //marks the beginning of a tag
        LINK = 'a',     //marks the beginning of a link
        COMMENT = '!';  //marks the beginning of a comment

        char fileChar;  //individual characters from the file
        int charNum=0, //total characters in the file
        tagNum=0,       //total tags in the file
        linkNum=0,      //total links in the file
        commentNum=0,   //total comments in the file
        tagChars=0, //number of chars in tags
        lineNum=0, //number of lines in file
        charPercent=0; //percent of chars in tags


        int count = 0; //for counting

        string fileName; //name of file

        ifstream inFile;

//take in user input

cout << "========================================" << endl;
cout << "   Welcome to the HTML File Analyzer!" << endl;
cout << "========================================" << endl << endl;

  cout << "Please enter a valid file name (with no spaces): " << endl;
  cin >> fileName;

  inFile.open(fileName.c_str());         //opens the file

if(inFile)                //tests if file is open
 cout << "file IS open" << endl;
else
 cout << "file NOT open" << endl;

  while (!inFile) //error checking to ensure file exists
{
    inFile.clear(); //clear false file
    cout << endl << "Re-enter a valid filename: " << endl;
    cin >> fileName;
    inFile.open (fileName.c_str());
}

//display contents of file

cout << "========================================" << endl;
cout << "         Contents of the File           " << endl;
cout << "========================================" << endl << endl;

std:string line;

while(inFile)   //print out contents of the file
{
        getline(inFile, line);
        cout << line <<  endl;
        lineNum++; //add to line counter

        const int size=line.length();
        charNum = charNum + size;
        cout << "The total number of characters entered is: " << charNum << endl;

}

inFile.open(fileName.c_str()); //reopen file

while (inFile) {
  inFile >> fileChar;
  if (inFile != TAG)  
  {
      continue; // We are only interested in potential tag or comment starts.
  }

  inFile >> fileChar;
  if (fileChar == '!') {
    char after1, after2;
    inFile >> after1 >> after2;
    if (after1 == '-' && after2 == '-') {
       // This is the start of a comment.
       // We start eating chars until we see '-->' pass by.
       std::string history = "  ";
       while (inFile) {
         inFile >> fileChar;
         if (history == "--" && fileChar == '>') {
            // end of comment, stop this inner loop.
            commentNum++;
            break;
         }

         // Shift history and copy current character to recent history
         history[0] = history[1];
         history[1] = fileChar;
       }
    }
  } else if (fileChar == '/') {
     // This is a closing tag. Do nothing.
  } else {
     // This is the start of a tag. Read until the first non-letter, non-digit.
     std::string tagName;
     while (inFile) {
       inFile >> fileChar;
       if (std::isalnum(fileChar)) {
         tagName.append(1, fileChar);
       } else {
         tagNum++;
         if (tagName == "a") linkNum++;
       }
     }
  }
}


cout << "========================================" << endl;
cout << "        End of Contents of File         " << endl;
cout << "========================================" << endl << endl;

inFile.open(fileName.c_str());

while(inFile) //count chars
{
         charNum = charNum + 1;
}
cout << "========================================" << endl;
cout << "            Content Analysis            " << endl;
cout << "========================================" << endl << endl;

cout << "Number of Lines: " << lineNum << endl;
cout << "Number of Tags: " << tagNum << endl;
cout << "Number of Comments: " << commentNum << endl;
cout << "Number of Links: " << linkNum << endl;
cout << "Number of Chars in File: " << charNum << endl;
cout << "Number of Chars in Tags: " << tagChars << endl;
cout << "Percent of Chars in Tags: " << charPercent << endl;
inFile.close ();

return (0);

}
