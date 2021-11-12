#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <set>
using std::set;

#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

using std::pair;

//debug
#include <sstream>

void print();
// TODO: Your Sudoku class goes here:
class Sudoku : public Searchable {
private:
	int size;
    int boxCount;
	vector<vector<set<int>>> solution;

	/* Idea is that there will not be more than 3 same size two cells.
	 * This removes the need for Map<pair<int, int>, int> and counter
	 */
    void removeValuesFromOtherGrid(int i, int j, int value) {
        // deleting all the other squares on that column
		set<pair<int, int>> erased;
        for (int x = 0; x < size; x++) {
            if (x != j && solution[i][x].erase(value)) {
				erased.emplace(i, x);
			}
        // deleting all the other squares on that row
            if (x != i && solution[x][j].erase(value)) {
				erased.emplace(x, j);
			}
        }
		/*
		 * Finding a set that just became 1..
		 * But this actually decrease test pass down to 24 from 67...
		 */
		//checker(erased);
        //print();
		//
        int xBox = (i / boxCount);
        int yBox = (j / boxCount);
        for (int x = xBox * boxCount; x < (xBox + 1) * boxCount; x++) {
            for (int y = yBox * boxCount; y < (yBox + 1) * boxCount; y++){
                if (x != i && y != j && solution[x][y].erase(value)) {
					erased.emplace(x, y);
				}
            }
        }
		checker(erased);
    }

	void checker(set<pair<int, int>> & erased) {
		/* prioritising size 1 
		for (const auto & elem : erased) {
			int setSize = solution[elem.first][elem.second].size();
			if (setSize == 1) {
				removeValuesFromOtherGrid(elem.first, elem.second, *(solution[elem.first][elem.second].begin()));
			}
		}
		for (const auto & elem : erased) {
			int setSize = solution[elem.first][elem.second].size();
			if (setSize > 1 && setSize < 4) {
				removeSameSizeSetCellsColRow(elem.first, elem.second, setSize);
			}
		}
		*/
		for (auto elem : erased) {
			hiddenSingle(elem.first, elem.second);
			int setSize = solution[elem.first][elem.second].size();
			if (setSize == 1) {
				removeValuesFromOtherGrid(elem.first, elem.second, *(solution[elem.first][elem.second].begin()));
			} else if (setSize > 1 && setSize < 4) {
				removeSameSizeSetCellsColRow(elem.first, elem.second, setSize);
			}
		}
	}

	//individual one - improvement from diagonal scanning
    void removeSameSizeSetCellsColRow(int row, int col, int duplicateSize) {
		bool rowFlag = false;
		bool colFlag = false;
		int rowCounter = 1;
		int colCounter = 1;
		for (int i = 0; i < size; i++) {
			if (i != col && solution[row][i] == solution[row][col]) {
				rowCounter++;
			}

			if (rowCounter == duplicateSize) {
				rowFlag = true;
				if (colFlag) break;
			}

			if (i != row && solution[i][col] == solution[row][col]) {
				colCounter++;
			}

			if (colCounter == duplicateSize) {
				colFlag = true;
				if (rowFlag) break;
			}
		}

		set<pair<int, int>> erased;
		if (rowFlag || colFlag) {
			for (int i = 0; i < size; i++) {
				if (rowFlag && solution[row][i] != solution[row][col]) {
					for (int removing : solution[row][col]) { 
						if(solution[row][i].erase(removing)) erased.emplace(row, i);
					}
				}
				if (colFlag && solution[i][col] != solution[i][col]) {
					for (int removing : solution[row][col]) { 
						if(solution[i][col].erase(removing)) erased.emplace(i, col);
					}
				}
			}
		}
		set<pair<int, int>> gridErased = betterSetSquareGrid(row, col, duplicateSize);
		erased.insert(gridErased.begin(), gridErased.end());

		checker(erased);
	}

	set<pair<int, int>> betterSetSquareGrid(int i, int j, int duplicateSize) {
        int xBox = (i / boxCount);
		int yBox = (j / boxCount);
		int counter = 1;
		bool flag = false;
        for (int x = xBox * boxCount; x < (xBox + 1) * boxCount; x++) {
            for (int y = yBox * boxCount; y < (yBox + 1) * boxCount; y++){
				if ((x != i || y != j) && solution[x][y] == solution[i][j]) {
					counter++;
				}
				if (counter == duplicateSize) {
					flag = true;
					break;
				}
			}
        }
        
		set<pair<int, int>> erased;
		if (flag) {
			for (int x = xBox * boxCount; x < (xBox + 1) * boxCount; x++) {
				for (int y = yBox * boxCount; y < (yBox + 1) * boxCount; y++){
					if (solution[x][y] != solution[i][j]) {
						for (int removing : solution[i][j]) {
							if (solution[x][y].erase(removing)) erased.emplace(x, y);
						}
					}
				}
			}
		}
		return erased;
	}

	//https://www.learn-sudoku.com/hidden-singles.html
	void hiddenSingle(int row, int col) {
		//row
		for (int number = 1; number <= size; number++) {
			int xCoordinate;
			int yCoordinate;
			int rowCounter = 0;
			int colCounter = 0;
			for (int i = 0; i < size; i++) {
				if (solution[row][i].find(number) != solution[row][i].end()) {
					rowCounter++;
					if (rowCounter == 1) yCoordinate = i;
				}

				if (solution[i][col].find(number) != solution[i][col].end()) {
					colCounter++;
					if (colCounter == 1) xCoordinate = i;
				}
			}

			if (rowCounter == 1) {
				if (solution[row][yCoordinate].size() != 1) {
					// calling setSquare is error
					// cout << "hiddenSingle y " << yCoordinate << endl;
					setSquare(row, yCoordinate, number);
				}
			}

			if (colCounter == 1) {
				if (solution[xCoordinate][col].size() != 1) {
					// cout << "hiddenSingle x " << xCoordinate << endl;
					setSquare(xCoordinate, col, number);
				}
			}
		}
		
		int xBox = (row / boxCount);
		int yBox = (col / boxCount);
    	for (int number = 1; number <= size; number++) {
			int xCoordinate;
			int yCoordinate;
			int counter = 0;
			for (int x = xBox * boxCount; x < (xBox + 1) * boxCount; x++) {
				for (int y = yBox * boxCount; y < (yBox + 1) * boxCount; y++) {
					if (solution[x][y].find(number) != solution[x][y].end()) {
						counter++;
						if (counter == 1) {
							xCoordinate = x;
							yCoordinate = y;
						}
					}
				}
			}

			if (counter == 1) {
				if (solution[xCoordinate][yCoordinate].size() != 1) {
					setSquare(xCoordinate, yCoordinate, number);
					//cout << "hiddenSingle xy " << xCoordinate << "," << yCoordinate << " "  << endl;
				}
			}
		}
    }

public:
	Sudoku(int _size) : size(_size) {
        solution = vector<vector<set<int>>>(size);
        set<int> temp;  // copy
        for (int i = 1; i <= size; i++) {
            temp.insert(i);
        }
        
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				solution[i].push_back(temp);
			}
		}
        boxCount = sqrt(size);
        //print();
	}

	int getSquare(int row, int col) const {
		if (row >= size || col >= size || col < 0 || row < 0) return -1;
		if((solution[row])[col].size() == 1) {
            //cout << "getSqure returns " << *((solution[col])[row].begin())<< endl;
			return *((solution[row])[col].begin());
		}
		return -1;
	}

	bool setSquare(int row, int col, int value) {
        boxCount = sqrt(size);
		if (row < size && col < size && col >= 0 && row >= 0) {
			solution[row][col].clear();
			solution[row][col].insert(value);
            
            removeValuesFromOtherGrid(row, col, *(solution[row][col].begin()));
           
            for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (solution[i][j].size() == 0) {
//                      cout << "return false no possible sol" << endl;
//						print();
                        return false;
                    }
                }
            }
        }
        //print intermidiate stage
        //cout << "final" << endl;
        //print();
        //std::ostringstream o;
        //write(o);
        return true;
	}
    
    virtual bool isSolution() const override {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j].size() != 1) {
                    return false;
                }
            }
        }
        return true;
    }
    
    virtual void write(ostream & o) const override {
        //print intermidiate stage
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j].size() != 1) {
                    o << " ";
                } else {
                    o << *(solution[i][j].begin());
                }
                
                if (j == size - 1) o << "\n";
            }
        }
    }
    
    virtual vector<unique_ptr<Searchable>> successors() const override {
        vector<unique_ptr<Searchable>> successor;
        
        int firstRow = -1;
        int firstCol = -1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j].size() != 1) {
                    firstRow = i;
                    firstCol = j;
                    break;
                }
            }
        }
        
        if (firstRow != -1 && firstCol != -1) {
            for (auto elem : solution[firstRow][firstCol]) {
                //cout << elem << " value" << endl;
                Sudoku* copy = new Sudoku(*this);
                if(copy->setSquare(firstRow, firstCol, elem)) {
                    //cout << "added new successor" << endl;
                    successor.emplace_back(copy);
                } else {
                    delete copy;
                }
            }
        }
// NEW part
        if (successor.size() == 1 && !(successor[0]->isSolution())) {
			//cout << " new successor part " << endl;
			//(successor[0]) -> write(cout);
            return successor[0]->successors();
        }
		//end
        return successor;
    }
    
    virtual int heuristicValue() const override {
        int num = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j].size() > 1) {
                    num++;
                }
            }
        }
        return num;
    }
    
    void print() const {
        //print intermidiate stage
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                if (y != 0 && y % boxCount == 0) cout << "\t";
                cout << "{";
                for (auto elem : solution[x][y]) {
                    cout << elem << ",";
                }

				for (int i = 0; i < size - solution[x][y].size(); i++) {
					cout << "  "; 
				}
                cout << "},";
                
            }
            cout << endl;
            cout << endl;
        }
    }
};

#endif
