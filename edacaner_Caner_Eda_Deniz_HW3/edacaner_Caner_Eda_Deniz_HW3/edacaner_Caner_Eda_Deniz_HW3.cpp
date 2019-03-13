#include <iostream>
#include <fstream>
#include "strutils.h"
#include <string>
#include <cctype>
#include <sstream>
#include <string>
#include "prompt.h"
#include <iomanip>
#include "wordList.h"

using namespace std;

//EDA DENÝZ CANER - 17915

int main()
{
	wordlist * myWords = new wordlist[26]; // creates a dynamic array consisting of 26 elements each of which is for 26 different letters.
	ifstream inFile;
	string FileName = PromptString("Please enter the name of the file:"); //Wants user to enter a file name to open.
	cout << "    " << endl;
	inFile.open(FileName.c_str()); // Tries to open the file.
	while(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		FileName = PromptString("Please enter the name of the file again:"); //Wants user to enter a file name to open.
		cout << "     " << endl;
		inFile.open(FileName.c_str()); // Tries to open the file.
	}

	string line;
	while (getline(inFile, line)) // reads the file line by line.
	{
		istringstream strStream(line);
		string input;

		while (strStream >> input) // reads every line word by word.
		{	
			StripPunc(input);
			ToLower(input);
			char key = input.at(0);
			if(key > 96 && key < 123) // checks if the input has a valid first letter.
			{
				if(!(myWords[key-'a'].doesExist(input))) //checks whether it already exists in the list.
				{
					myWords[key-'a'].AddWord(input); // calls AddWord member function on the i^th index of array where i is the number of first char of the input.
				}
				else
				{
					myWords[key-'a'].CountUpdate(input); // calls CountUpdate member function on the i^th index of array where i is the number of first char of the input.
				}
			}
		}
	}

	cout << "File " << FileName << " has been read and processed" << endl; //displays a proper message

	while(true)
	{
		//Displays the options to the user.
		cout << endl ;
		cout << "Please select one option:" << endl;
		cout << "1. Display the count of a specific word" << endl;	
		cout << "2. Remove a specific word" << endl;	
		cout << "3. Display words with the same initial letter (in alphabetical order)" << endl;	
		cout << "4. Display words with the same initial letter (in reverse alphabetical order)" << endl;	
		cout << "5. Display all words (in alphabetical order)" << endl;	
		cout << "6. Display all words (in reverse alphabetical order)" << endl;	
		cout << "7. Exit." << endl;	
		cout << endl ;

		int option;
		cout << "Your choice: "; //Wants user to enter his/her option. 
		cin >> option ; 
		cout << "      " << endl;

		switch (option)
		{
		case 1:{
			string wordToBeDisplayed = PromptString("Please enter a word to find out its count: "); //displays a proper message
			cout << "******************************************" << endl;
			ToLower(wordToBeDisplayed); // makes all the letter in the word lower case
			char k = ' '; 
			k = wordToBeDisplayed.at(0);
			if(k > 96 && k < 123 ) // checks if the input has a valid first letter.
			{
				if(myWords[k-'a'].doesExist(wordToBeDisplayed)) //checks whether it already exists in the list.
				{
					myWords[k-'a'].DisplayCount(wordToBeDisplayed); // calls DisplayCount member function on the i^th index of array where i is the number of first char of the input.
				}
				else
				{
					cout << wordToBeDisplayed << " does not exist." << endl;
				}
			}
			else
			{
				cout << "The word contains an invalid first letter." << endl;
			}
			break;}
		case 2: {
			string wordToBeRemoved = PromptString("Please enter the word to remove:");
			cout << "******************************************" << endl;
			ToLower(wordToBeRemoved); // makes all the letter in the word lower case
			char ch = ' ';
			ch = wordToBeRemoved.at(0);
			if(ch > 96 && ch < 123 ) // checks if the input has a valid first letter.
			{
				if(myWords[ch-'a'].doesExist(wordToBeRemoved)) //checks whether it already exists in the list.
				{
					myWords[ch-'a'].RemoveWord(wordToBeRemoved); // calls RemoveWord member function on the i^th index of array where i is the number of first char of the input.
					cout << wordToBeRemoved << " has been deleted." << endl;
				}
				else if(!(myWords[ch-'a'].doesExist(wordToBeRemoved))) //checks whether it already exists in the list.
				{
					cout << wordToBeRemoved << " does not exist." << endl; //displays a proper message
				}
			}
			else
			{
				cout << "The word contains an invalid first letter." << endl; //displays a proper message
			}
			break;}
		case 3: {
			string k;
			cout << "Please enter a letter:" ; //displays a proper message
			cin >> k;
			ToLower(k);
			char ch = k.at(0);
			if(ch > 96 && ch < 123)
			{
				myWords[ch-'a'].PrintList(); // calls printList member function on the i^th index of array where i is the number of first char of the input.
			}
			else
			{
				cout << "Invalid entry!" << endl;
			}
			break;}
		case 4:  {
			string l ;
			cout << "Please enter a letter:" ; //displays a proper message
			cin >> l ;
			ToLower(l); // makes all the letter in the word lower case
			char ch = l.at(0);
			if(ch > 96 && ch < 123)
			{

				myWords[ch-'a'].ReversePrintList(); // calls ReversePrintList member function on the i^th index of array where i is the number of first char of the input.
			}
			else
			{
				cout << "Invalid entry!" << endl;
			}
			break;}
		case 5: {
			for(int i = 0; i<26 ; i++)
			{
				myWords[i].PrintList(); // calls printList member function on the i^th index of array where i is the number of first char of the input.
			}
			break;}
		case 6:{
			for(int i = 25; i >= 0; i--)
			{
				myWords[i].ReversePrintList(); // calls ReversePrintList member function on the i^th index of array where i is the number of first char of the input.
			}
			break;}
		case 7: // if the option entered by the user is 7.
			system("pause");
			exit(0);
		default:// if the value entered by the user is not one of the above.
			cout << "INVALID OPTION!! Try again" << endl; //displays a proper message
		}
	}
	return 0;
}