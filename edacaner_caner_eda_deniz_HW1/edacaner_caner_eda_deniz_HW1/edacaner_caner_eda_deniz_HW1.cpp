#include <iostream>
#include <fstream>
#include "prompt.h"
#include "strutils.h"
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Eda Deniz CANER - 17915
//This program is designed to read a matrix from a file, gets an input sum from the user and do 
//horizontal and vertical search to find submatrices whose sums are equal to the sum entered by the user.

void MatrixSizeControl(const vector<vector<int>> myMatrix)// this function controls if all the rows of the matrix have the same amount of columns
{
	for(unsigned int t=0 ; t < myMatrix.size() ; t++)
	{
		int numColumn = myMatrix[0].size(); // the number of elements in the first row of the matrix.
		if((myMatrix[t].size() != numColumn)) // enters the if loop if the elements number of the row is not equal to the element number of the first row.
		{
			// displays a message about the error in matrix size.
			cout << "The matrix in the input file is not in correct matrix format" << endl;
			cout << "or matrix contains an unvalid element." << endl;
			cout << "End of execution." <<endl;
			int number1;
			cin >> number1;
		}
	}	
}

void horizontal(const vector<vector<int>> myMatrix, int sum, int & counter)//This function searches the matrix horizontally.
{
	int tempSum = 0;

	for(unsigned int row=0; row < myMatrix.size(); row++ ) // increases the row one by one.
	{
		for (unsigned int column = 0 ; column < myMatrix[0].size(); column++) // increases the starting column one by one.
		{
			for(unsigned int t = column; tempSum <= sum && t < myMatrix[0].size(); t++) // do the search in the selected row from the starting column.
			{
				if(tempSum < sum) // if tempSum is still smaller then the sum entered by the user it adds the new number to the tempSum.
				{
					tempSum = tempSum + myMatrix[row][t] ; 
				}
				if(tempSum == sum) // when it reaches the sum it displays a message, increases the counter by one and makes the tempum 0.
				{
					counter++;
					cout << "Found one horizontally from (" <<row << "," << column << ")" << " to (" <<row << "," << t << ")" << endl ;
					tempSum  = 0;
				}
			}
			tempSum = 0;
		} 
	}
} 

void vertical(const vector<vector<int>> myMatrix, int sum, int &counter)//This function searches the matrix vertically.
{
	int tempSum = 0;

	for (unsigned int column = 0; column < myMatrix[0].size(); column++) // increases the column one by one.
	{
		for(unsigned int row = 0; row < myMatrix.size(); row++) // increases the starting row one by one.
		{
			for(unsigned int t = row; tempSum <= sum && t < myMatrix.size(); t++) // do the search vertically in the selected column from the starting starting row.
			{
				if(tempSum < sum) // if tempSum is still smaller then the sum entered by the user it adds the new number to the tempSum.
				{
					tempSum = tempSum + myMatrix[t][column] ; 
				}
				if(tempSum == sum)  // when it reaches the sum it displays a message, increases the counter by one and makes the tempum 0.
				{
					counter++;
					cout << "Found one vertically from (" << row << "," << column << ")" << " to (" << t << "," << column << ")"<< endl ;
					tempSum = 0;
				}
			}
			tempSum = 0;
		}
	}
}

int main()
{
	vector<vector<int>> myMatrix(0)  ; //Matrix decleration
	ifstream inFile;
	char ch = ' ' ;

	string FileName = PromptString("Please enter the filename:"); //Wants user to enter a file name to open.
	inFile.open(FileName.c_str()); // Tries to open the file.
	while(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		FileName = PromptString("Please enter the filename:"); //Wants user to enter a file name to open.
		inFile.open(FileName.c_str()); // Tries to open the file.
	}

	int row = 0;
	int column = 0;

	while (inFile.get(ch))//Reads the file char by char
	{
		//Controls if the char is a number, space or a new line character.
		if(!(ch =='0' || ch == '1' || ch =='2' || ch =='3' || ch =='4' || ch =='5' || ch =='6' || ch =='7' || ch =='8' || ch =='9'|| ch =='\n' || ch == ' ') )
		{
			cout << "The matrix in the input file is not in correct matrix format" << endl;
			cout << "or matrix contains an unvalid element." << endl;
			cout << "End of execution." <<endl;
			int n;
			cin >> n;
		}
	}
	
	inFile.close(); // closes the file
	ifstream inFile1; 
	inFile1.open(FileName.c_str()); // opens the same file again.
	
	string line;
	while (getline(inFile1,line)) // reads the file line by line.
	{
		istringstream strStream(line);
		vector<int> temp;
		string word;

		while (strStream >> word) // reads every line word by word.
		{	
			int num = atoi(word); // turns every word into an integer
			if(num > 0) // chacks if the integer value is bigger than 0.
			{
				temp.push_back(num);		// adds the value to the temporary vector
			}
			else
			{
				cout << "The matrix in the input file is not in correct matrix format" << endl;
				cout << "or matrix contains an unvalid element." << endl;
				cout << "End of execution." <<endl;
				int a ;
				cin >> a;
			}
		}
		myMatrix.push_back(temp); // adds the temporary vector to the matrix.
	}
	
	// Calls the function that checks the matrix size
	MatrixSizeControl(myMatrix);

	string word;
	cout << "Please enter a sum value that will be searched in the matrix " << endl; // asks user for an input sum value to be searched in the matrix.
	cout << "(anything rather than a positive integer to quit):" ;
	int counter = 0;

	while(cin >> word)
	{
		for (unsigned int i=0 ; i < word.length(); i++)
		{
			char ch;
			ch=word.at(i); // check the input value char by char to see if it consists only of digits.

			if (!(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ))
			{
				cout << "End of execution." << endl;
				int b;
				cin >> b;
			}
		}

		int sum = atoi(word);
		if(sum > 0 )
		{
			horizontal(myMatrix, sum, counter); // do the horizontal search.
			vertical(myMatrix, sum, counter); // do the vertical search.
			cout << "Total number of occurances:" << counter << endl; // displays the counter.
			cout << "Please enter a sum value that will be searched in the matrix " << endl;
			cout << "(anything rather than a positive integer to quit):" ;
			counter = 0;
		}	
	}

return 0;		
}