#include<iostream>
#include<fstream>
#include<stdio.h>
#include <bits/stdc++.h>

using namespace std;

using std::cout; using std::ofstream;
using std::endl; using std::string;

struct Trie {
	bool isEndOfWord;
	unordered_map<char, Trie*> map;
	string meaning;
};

Trie* getNewTrieNode()
{
	Trie* node = new Trie;
	node->isEndOfWord = false;
	return node;
}

void insert(Trie*& root, const string& str,
			const string& meaning)
{

	if (root == NULL)
		root = getNewTrieNode();

	Trie* temp = root;
	for (int i = 0; i < str.length(); i++) {
		char x = str[i];

		if (temp->map.find(x) == temp->map.end())
			temp->map[x] = getNewTrieNode();

		temp = temp->map[x];
	}

	temp->isEndOfWord = true;
	temp->meaning = meaning;
}

string getMeaning(Trie* root, const string& word)
{

	if (root == NULL)
		return "";

	Trie* temp = root;

	for (int i = 0; i < word.length(); i++) {
		temp = temp->map[word[i]];
		if (temp == NULL)
			return "";
	}

	if (temp->isEndOfWord)
		return temp->meaning;
	return "";
}

void removeSpecialCharacter(string s)
{
	int j = 0;
	for (int i = 0; i < s.size(); i++) {
		
		// Store only valid characters
		if ((s[i] >= 'A' && s[i] <= 'Z') ||
			(s[i] >='a' && s[i] <= 'z'))
		{
			s[j] = s[i];
			j++;
		}
	}
	cout << s.substr(0, j);
}

void dictionary()
{
    ifstream inFile;
    ofstream outFile;
    string dictionary[] = inFile.open("dictionary.txt", ifstream::in);
    inFile.open("dictionary.txt", ifstream::in);

    if(inFile.fail())
    {
        cout << "The file was not successfully opened" << endl;
        exit(1);
    }
    vector<string> Dictionary;

    string tempWord;
    while(!inFile.eof()) 
    {
        inFile >> tempWord;    
        Dictionary.push_back(tempWord);
        
    }
    inFile.close();
    outFile.open("dictionary.txt", ofstream::out); 

    if(outFile.fail())
        cout << "Cannot open the file" << endl;
    else
    {
        for(unsigned int i = 0; i < Dictionary.size(); i++) 
        {
        outFile << Dictionary.at(i) << endl;
        }
        outFile.close();
    }
    int size = sizeof(dictionary) / sizeof(dictionary[0]);
	for (int i = 0; i < size; i++)
		if (dictionary[i].compare(word) == 0)
			return true;
	return false;
}

bool wordBreak(string s)
{
	int n = s.size();
	if (n == 0)
		return true;

	vector<bool> dp(n + 1, 0);

	vector<int> matched_index;
	matched_index.push_back(-1);

	for (int i = 0; i < n; i++) {
		int msize = matched_index.size();

		int f = 0;

		for (int j = msize - 1; j >= 0; j--) {

			string sb = s.substr(matched_index[j] + 1,
								i - matched_index[j]);

			if (dictionary(sb)) {
				f = 1;
				break;
			}
		}

		if (f == 1) {
			dp[i] = 1;
			matched_index.push_back(i);
		}
	}
	return dp[n - 1];
}

void wordcheck()
{
    std::string str = "Zoom???@@##$ to#$% friends%$^for$%^&fun";
  
    for (int i = 0, len = str.size(); i < len; i++)
    {

        if (ispunct(str[i]))
        {
            str.erase(i--, 1);
            len = str.size();
        }
    }

    std::cout << str;
    return 0;
}

std::vector<std::string> readFileToVector(const std::string& filename)
{
    std::ifstream source;
    source.open(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(source, line))
    {
        lines.push_back(line);
    }
    file.open(filename.c_str());
  
    while (file >> word)
    {
        cout << word << endl;
    }
  
    return lines;
}

void displayVector(const std::vector<std::string&> v)
{
    for (int i(0); i != v.size(); ++i)
        std::cout << "\n" << v[i];
}

int main(int argc,  char **argv)
{
    Trie* root = NULL;
    char fileName[30], ch;
    fstream fp;
    fp.open("dictionary.txt", ios::in);
    gets(fileName);
    fp.open(fileName, fstream::in);
    if(!fp)
    {
        cout<<"\nError Occurred!";
        return 0;
    }
    std::string charactersFilename(argv[1]);
    std::string matchesFilename(argv[2]);
    std::vector<std::string> characters = readFileToVector(charactersFilename);
    std::vector<std::string> matches = readFileToVector(matchesFilename);

    displayVector(characters);
    displayVector(matches);
    cout<<"\nContent of "<<fileName<<":-\n";
    while(fp>>noskipws>>ch)
        cout<<ch;
    fp.close();
    cout<<endl;
    return 0;
}
