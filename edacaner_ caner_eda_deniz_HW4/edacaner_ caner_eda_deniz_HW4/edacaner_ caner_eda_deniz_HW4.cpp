#include <iostream>
#include <fstream>
#include "strutils.h"
#include <string>
#include <cctype>
#include <sstream>
#include <string>
#include "prompt.h"
#include <iomanip>
#include "DynStack.h"

using namespace std;

// Eda Denizz CANER -17915

struct cellStruct // construct a cell struct in order to form a dynamic array. 
{
	char bit;
	bool flag;
};

void printStack(DynStack &, string); // printStack function prototype

void matrixSearch(cellStruct** , DynStack &, string, int , int, bool, bool); // matrixSearch function prototype

int main()
{
	int numRow, numCol;
	DynStack myStack;
	// wants user to enter a number of rows and columns to create a dynamic array
	cout << "Please enter the number of rows:" ;
	cin >> numRow ;
	cout <<  "Please enter the number of columns:" ;
	cin >> numCol;
	
	ifstream inFile;
	string FileName = PromptString("Please enter the name of the file:"); //Wants user to enter a file name to open.
	cout << "    " << endl;
	inFile.open(FileName.c_str()); // Tries to open the file.
	while(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		FileName = PromptString("Please enter the name of the file again:"); //Wants user to enter a file name to open.
		inFile.open(FileName.c_str()); // Tries to open the file.
	}

	cellStruct** myArray = new cellStruct*[numRow]; // creates a dynamic array with row*col cells
	for(int i = 0; i < numRow; ++i)
	{
		myArray[i] = new cellStruct[numCol];
	}

	int lineNum = 0;
	string line;
	while (getline(inFile, line)) // reads the file line by line.
	{
		istringstream strStream(line);
		char input;
		int num = 0;

		while (strStream >> input) // reads every line.
		{
			myArray[lineNum][num].bit = input ; 
			myArray[lineNum][num].flag = false ;
			num++;
		}
		lineNum++;
	}
	//for(int i = 0; i < numRow; i++) // for debugging purposes
	//{
	//	for(int k = 0; k < numCol; k++ )
	//	{
	//		cout << myArray[i][k].bit ;
	//	}
	//	cout << endl;
	//}
	bool status = false; // to check if the result is found either when the search is finished when the inputstring is over
	bool status2 = false; // to check if the result can not be found when the serach should be terminated
	string bitString; // input to be searched from the user
	cout <<"---------------------------------------------------------"<< endl;
	cout << "Please enter a string of bits to search(CTRL+Z to quit):" ;
	while (cin >> bitString) // as long as user enters a data
	{
		if(bitString.length() < (numRow + numCol)) // checks if it is possible to find the given data sequence in matrix
		{
			if(bitString.length() == 1 ) // chack is the legth of the given data sequence is 1
			{
				if( bitString.at(0) == myArray[0][0].bit) //check if the first characters match
				{
					myStack.push(0,0);
					cout << "The bit string " << bitString << " is found following these coordinates:" << endl;
					printStack(myStack, bitString);
				}
				else if(bitString.at(0) != myArray[0][0].bit)
				{
					cout << "The bit string " << bitString << " could not be found." << endl;
					cout <<"---------------------------------------------------------"<< endl;
				}
			}
			else
			{
				if( bitString.at(0) == myArray[0][0].bit) //check if the first characters match
				{
					myStack.push(0,0); // pushes the first coordinates since the value of the first coordinate and the values of the first index of bitStrin match
					matrixSearch(myArray, myStack, bitString, numRow, numCol, status, status2); // calls matrixSearch function to search the entire matrix
				}
				else if(bitString.at(0) != myArray[0][0].bit)
				{
					cout << "The bit string " << bitString << " could not be found." << endl;
					cout <<"---------------------------------------------------------"<< endl;
				}
			}
		}
		else
		{
			cout << "The bit string " << bitString << " could not be found." << endl;
			cout <<"---------------------------------------------------------"<< endl;
		}
		for(int i = 0; i < numRow; ++i) // clears the flag values of the matrix in order to search the matrix again for a diferent input value
		{
			for(int j = 0; j < numCol; ++j)
			{
				myArray[i][j].flag = false;
			}
		}

		cout << endl;
		cout << "Please enter a string of bits to search(CTRL+Z to quit):" ; 
	}

	for(int i = 0; i < numRow; ++i) // it deletes the dynamically allocated memory 
	{
		delete[]myArray[i];
	}
	delete[] myArray;

	cin.get();
	cin.ignore();
	return 0;
}

void printStack(DynStack & myStack, string bitString) // print the stack
{
	DynStack tempStack;
	int a, b;
	while(!myStack.isEmpty()) // empties the stach and transform it to a temp stack in order to put them in order
	{
		myStack.pop(a,b);
		tempStack.push(a,b);
	}
	while(!tempStack.isEmpty()) // print out the input values in the temp stack
	{
		tempStack.pop(a,b);
		cout << "( " << a << " , " << b << " )" << "     " ;
	}
	cout << endl;
	cout <<"---------------------------------------------------------"<< endl;
}

void matrixSearch(cellStruct** myArray, DynStack & myStack, string bitString, int numRow, int numCol, bool status, bool status2)
{
	int col = 0;
	int row = 0;

	while(status == false && status2 == false)  // checks if we need to go on searching the matrix
	{
		//first check the down cell
		if( row+1 < numRow && myArray[row+1][col].flag == false &&  myArray[row+1][col].bit == bitString.at(col+row+1))
		{
			row++;
			myStack.push(row, col);
			if(col + row == bitString.length()-1)
			{
				status = true;
			}
		}//check the rght cell if the value in the down cell is not right
		else if( col+1 < numCol && myArray[row][col+1].flag == false && myArray[row][col+1].bit == bitString.at(col+row+1))
		{
			col++;
			myStack.push(row, col);
			if(col + row == bitString.length()-1)
			{
				status = true;
			}	
		}//checks if the values of both cells is not correct adn set their flags true in order to avoid visiting them again
		else if(row+1 < numRow && col+1 < numCol && myArray[row+1][col].bit != bitString.at(col+row+1) && myArray[row][col+1].bit != bitString.at(col+row+1) )
		{
			myArray[row][col].flag = true;
			myArray[row][col+1].flag = true;
			myArray[row+1][col].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		} // checks if there are more rows to check below and the value of the right cell is correct or not
		else if(row+1 >= numRow && col+1 < numCol && myArray[row][col+1].bit != bitString.at(col+row+1) )
		{
			myArray[row][col].flag = true;
			myArray[row][col+1].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		}// checks if there are more cols to check below and the value of the below cell is correct or not
		else if(row+1 < numRow && col+1 >= numCol && myArray[row+1][col].bit != bitString.at(col+row+1) )
		{
			myArray[row][col].flag = true;
			myArray[row+1][col].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		}// checks if there are more rows and columns to check
		else if(row+1 >= numRow && col+1 >= numCol  )
		{
			myArray[row][col].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		} // checks if the value of the below cell is correct or not and the flag of the right cell is true or not
		else if(row+1 < numRow && col+1 < numCol && myArray[row+1][col].bit != bitString.at(col+row+1)  && myArray[row][col+1].flag == true )
		{
			myArray[row][col].flag = true;
			myArray[row+1][col].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		} // checks if the value of the right cell is correct or not and the flag of the below cell is true or not
		else if(row+1 < numRow && col+1 < numCol && myArray[row][col+1].bit != bitString.at(col+row+1) && myArray[row+1][col].flag == true )
		{
			myArray[row][col].flag = true;
			myArray[row][col+1].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		}
		else if(row+1 < numRow && col+1 < numCol && myArray[row+1][col].flag == true && myArray[row][col+1].flag == true )
		{
			myArray[row][col].flag = true;

			myStack.pop(row, col);
			if(!myStack.isEmpty())
			{
				myStack.pop(row, col);
				myStack.push(row, col);
			}
			if(myArray[0][0].flag == true) // if we get back to the (0,0) it means that we could not find the input value
			{
				status2 = true;
			}
		}
	}
	if(status == true) // checks if the input string is found or not
	{
		cout << "The bit string " << bitString << " is found following these coordinates:" << endl;
		printStack(myStack, bitString);
	}
	else if(status2 == true)
	{
		cout << "The bit string " << bitString << " could not be found." << endl;
		cout <<"---------------------------------------------------------"<< endl;
	}
}