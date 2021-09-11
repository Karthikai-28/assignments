#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include <string>
#define INF INT_MAX

using namespace std;
using std::cout; using std::ofstream;
using std::endl; using std::string;

const int ALPHABET_SIZE = 26;

int printSolution (int p[], int n);
 
void solveWordWrap (int l[], int n, int M)
{
    int extras[n+1][n+1];

    int lc[n+1][n+1];
 
    int c[n+1];
 
    int p[n+1];
 
    int i, j;
 
    for (i = 1; i <= n; i++)
    {
        extras[i][i] = M - l[i-1];
        for (j = i+1; j <= n; j++)
            extras[i][j] = extras[i][j-1] - l[j-1] - 1;
    }
 
    for (i = 1; i <= n; i++)
    {
        for (j = i; j <= n; j++)
        {
            if (extras[i][j] < 0)
                lc[i][j] = INF;
            else if (j == n && extras[i][j] >= 0)
                lc[i][j] = 0;
            else
                lc[i][j] = extras[i][j]*extras[i][j];
        }
    }
 
    c[0] = 0;
    for (j = 1; j <= n; j++)
    {
        c[j] = INF;
        for (i = 1; i <= j; i++)
        {
            if (c[i-1] != INF && lc[i][j] != INF &&
                           (c[i-1] + lc[i][j] < c[j]))
            {
                c[j] = c[i-1] + lc[i][j];
                p[j] = i;
            }
        }
    }
 
    printSolution(p, n);
}
 
int printSolution (int p[], int n)
{
    int k;
    if (p[n] == 1)
        k = 1;
    else
        k = printSolution (p, p[n]-1) + 1;
    cout<<"Line number "<<k<<": From word no. "<<p[n]<<" to "<<n<<endl;
    return k;
}


class Graph
{
	int V;

	list<int> *adj;

	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
	Graph(int V);

	void addEdge(int v, int w);

	void topologicalSort();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); 
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
{
	visited[v] = true;

list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	Stack.push(v);
}

void Graph::topologicalSort()
{
	stack<int> Stack;

	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	while (Stack.empty() == false)
	{
		cout << (char) ('a' + Stack.top()) << " ";
		Stack.pop();
	}
}

int min(int x, int y)
{
	return (x < y)? x : y;
}


void printOrder(string words[], int n, int alpha)
{
	Graph g(alpha);

	for (int i = 0; i < n-1; i++)
	{
		string word1 = words[i], word2 = words[i+1];
		for (int j = 0; j < min(word1.length(), word2.length()); j++)
		{
			if (word1[j] != word2[j])
			{
				g.addEdge(word1[j]-'a', word2[j]-'a');
				break;
			}
		}
	}

	g.topologicalSort();
}

vector<int> encoding(string s1)
{
    cout << "Encoding\n";
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }
  
    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            cout << p << "\t" << table[p] << "\t\t" 
                 << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}
  
void decoding(vector<int> op)
{
    cout << "\nDecoding\n";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s1 = table[old];
    string c = "";
    c += s1[0];
    cout << s1;
    int count = 256;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s1 = table[old];
            s1 = s1 + c;
        }
        else {
            s1 = table[n];
        }
        cout << s1;
        c = "";
        c += s1[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
}

void removeSpaces(char *str1)
{
    int count = 0;

    for (int i = 0; str1[i]; i++)
        if (str1[i] != ' ')
            str1[count++] = str1[i]; 
    str1[count] = '\0';
    
}

void removeDupWord(string str)
{
    string word = "";
    for (auto x : str) 
    {
        if (x == ' ')
        {
            cout << word << endl;
            word = "";
        }
        else {
            word = word + x;
        }
    }
    cout << word << endl;
}

void removeSpecialCharacter(string s)
{
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < 'A' || s[i] > 'Z' &&
            s[i] < 'a' || s[i] > 'z')
        {  
            s.erase(i, 1);
            i--;
        }
    }
    cout << s;
}

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
  
    bool isEndOfWord;
};
  
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
  
    pNode->isEndOfWord = false;
  
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
  
    return pNode;
}
  
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
  
        pCrawl = pCrawl->children[index];
    }
  
    pCrawl->isEndOfWord = true;
}
  
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
  
        pCrawl = pCrawl->children[index];
    }
  
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

int dictionaryContains(string &word)
{
    string dictionary[] = {"mobile","samsung","sam","sung",
                            "man","mango", "icecream","and",
                            "go","i","love","ice","cream"};
    // ofstream dictionary;
    // dictionary.open("dictionary.txt")
    // dictionary.close()
    int n = sizeof(dictionary)/sizeof(dictionary[0]);
    for (int i = 0; i < n; i++)
        if (dictionary[i].compare(word) == 0)
            return true;
    return false;
}

void wordBreakUtil(string str, int size, string result);
 
void wordBreak(string str)
{
    wordBreakUtil(str, str.size(), "");
}
 
void wordBreakUtil(string str, int n, string result)
{
    for (int i=1; i<=n; i++)
    {
        string prefix = str.substr(0, i);
 
        if (dictionaryContains(prefix))
        {
            if (i == n)
            {
                result += prefix;
                cout << result << endl;
                return;
            }
            wordBreakUtil(str.substr(i, n-i), n-i,
                                result + prefix + " ");
        }
    }     
}

int main()
{
    string keys[] = {"the", "a", "there",
                    "answer", "any", "by",
                     "bye", "their" };
    int n = sizeof(keys)/sizeof(keys[0]);
  
    struct TrieNode *root = getNode();
  
    // Construct trie
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);
  
    // Search for different keys
    search(root, "the")? cout << "Yes\n" :
                         cout << "No\n";
    search(root, "these")? cout << "Yes\n" :
                           cout << "No\n";
    string s = "$Zo*o;m..wi, th'fr^iends?";
    removeSpecialCharacter(s);
    char line[100], alphabetString[100];
    int j = 0;
    cout << "Enter a string: ";
    cin.getline(line, 100);
    for(int i = 0; line[i] != '\0'; ++i)
    {
        if ((line[i] >= 'a' && line[i]<='z') || (line[i] >= 'A' && line[i]<='Z'))
        {
            alphabetString[j++] = line[i]; 
        }
    }
    alphabetString[j] = '\0';
    cout << "Output String: " << alphabetString; 
    int l[] = {3, 2, 2, 5};
    int n1 = sizeof(l)/sizeof(l[0]);
    int M = 6;
    solveWordWrap (l, n1, M);
    string str = "King of the Jungle";
    removeDupWord(str);
	string words[] = {"caa", "aaa", "aab"};
	printOrder(words, 3, 3);
    string s1 = "WYS*WYGWYS*WYSWYSG";
    vector<int> output_code = encoding(s);
    cout << "Output Codes are: ";
    for (int i = 0; i < output_code.size(); i++) {
        cout << output_code[i] << " ";
    }
    cout << endl;
    decoding(output_code);
    char str1[] = "a  nimals   are  in dan  ger  ";
    removeSpaces(str1);  
    cout << str1;
	return 0;
}
