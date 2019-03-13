#include <iostream>
#include <fstream>
#include "strutils.h"
#include <string>
#include <cctype>
#include <sstream>
#include <string>
#include "prompt.h"
#include <iomanip>

using namespace std;

//EDA DENÝZ CANER - 17915

struct movie // it creates a movie struct with four properties.
{
	string movieName;
	double totalRating;
	double numberOfRatings;
	movie * next;
};

//These are the function prototypes which will be defined after the main function.
void addFromFile(ifstream & inFile, string & movieNameFile, int & ratingInt, movie *& movieHead, string & FileName);
void addinOrder(string & a, int & b, movie *& movieHead);
bool doesExist(string & a, movie * movieHead);
void addRatingManually(	string & movieNameInput, int & ratingInput, movie *& movieHead);
void removeMovie(string & movietobeRemoved, movie *& movieHead);
void display(movie *& movieHead);
void deleteList(movie *& movieHead);


int main()
{
	movie * movieHead = NULL;  // creates a new head pointer for movie type and equalize it to the nullptr.
	ifstream inFile;
	string movieNameFile = " ", movieNameInput = " ", movietobeRemoved, FileName;
	int  ratingInt = 0, ratingInput = 0;

	while(true)
	{
		//Displays the options to the user.
		cout << endl ;
		cout << "		Movie Rating System" << endl;
		cout << "-----------------------------------" << endl;
		cout << "1. Load movie ratings from a file." << endl;	
		cout << "2. Add a new rating manually." << endl;	
		cout << "3. Remove an existing movie." << endl;	
		cout << "4. Display the list of movies and rating information." << endl;	
		cout << "5. Exit." << endl;	
		cout << endl ;

		int option;
		cout << "Your choice: "; //Wants user to enter his/her option. 
		cin >> option ; 
		cout << "      " << endl;

		switch (option)
		{
		case 1:{ // if the option entered by the user is 1.
			// Load movie ratings from a file
			FileName = PromptString("Please enter the name of the file:"); //Wants user to enter a file name to open.
			cout << "    " << endl;
			inFile.open(FileName.c_str()); // Tries to open the file.
			while(inFile.fail()) // Enters the loop if the file can not be opened.
			{
				cout << "File cannot be opened." << endl; //Displays a message
				FileName = PromptString("Please enter the name of the file again:"); //Wants user to enter a file name to open.
				cout << "     " << endl;
				inFile.open(FileName.c_str()); // Tries to open the file.
			}

			addFromFile(inFile, movieNameFile, ratingInt, movieHead, FileName);
			inFile.close();
			break;}
		case 2: // if the option entered by the user is 2.
			//Add a new rating manually.
			addRatingManually(movieNameFile, ratingInt, movieHead);
			cout << movieHead->movieName;
			break;
		case 3: // if the option entered by the user is 3.
			//Remove an existing movie.
			removeMovie(movietobeRemoved, movieHead);
			break;
		case 4: // if the option entered by the user is 4.
			//Display the list of movies and rating information.
			display(movieHead);
			break;
		case 5: // if the option entered by the user is 5.
			{
				deleteList(movieHead);
				system("pause");
				exit(0);
			}
		default:// if the value entered by the user is not one of the above.
			cout << "INVALID OPTION!! Try again" << endl;
		}
	}
	return 0;
}

void addFromFile(ifstream & inFile, string & movieNameFile, int & ratingInt,movie *& movieHead, string & FileName)
{   //This function reads the movie names and their rating from the file input received from the user.
	string line;
	while (getline(inFile, line)) // reads the file line by line.
	{
		int len = line.length(); // finds the length of the line.
		int s1 = line.find(' '); // find the character ' ' in the line.
		movieNameFile = line.substr(0, s1); //subtract the ID number from the line.
		StripWhite(movieNameFile); // clears the gaps.

		string rating = line.substr(s1+1, len - s1 - 1); // redefines the line.
		StripWhite(rating);
		int ratingInt = atoi(rating);// transforms the string valu into integer.
		if(ratingInt > 0 && ratingInt < 11)
		{
			if(doesExist( movieNameFile, movieHead)) // checks if the movies already exists in the linked list.
			{
				movie * ptrm = movieHead; // creates a new loop pointer and equalizes it to a head pointer.
				while (ptrm->movieName != movieNameFile) 
				{    
					ptrm = ptrm->next;
				}  // it updates the existing movie.
				ptrm->numberOfRatings++;
				ptrm->totalRating = (ptrm->totalRating+ratingInt);
				cout << movieNameFile << " has been updated." << endl; //it displays a proper message.
			}
			else// if the movie does not exist in the linked list, this adds it to the list.
			{
				addinOrder(movieNameFile, ratingInt, movieHead); 
				cout <<movieNameFile << " has been added to the list." << endl; //it displays a proper message.
			}
		}
		else
		{
			cout << "Movie " <<movieNameFile << " does not have a valid rating." << endl;	// if the rating value is not between 1 and 11 it does not add the movies to the list.
		}
	}
	cout << "    " << endl;
	cout << "Movies from " << FileName << " file have been loaded." <<endl; //it displays a proper message.
}

void addinOrder(string & a, int & b, movie *& movieHead)
{ 
	if (movieHead == NULL)  // checks if the list is empty.
	{   // creates a new node and equalizes head pointer to it.
		movie* tmp = new movie;
		tmp->movieName = a;
		tmp->totalRating = b;
		tmp->numberOfRatings = 1;
		tmp->next = NULL;
		movieHead = tmp;
		return;
	}

	if( a < movieHead->movieName) // check if new movies should be added before the head of the list.
	{//creates a new node and makes it a head pointer and connects to the rest of the link list.
		movie * temp = new movie;  //node to be inserted 
		temp->movieName = a;
		temp->totalRating = b;
		temp->numberOfRatings = 1;
		temp->next = movieHead; //connect the rest
		movieHead = temp;
		return;

	}

	movie * ptr = movieHead;   // loop variable

	while (ptr->next && ptr->next->movieName < a) //search the linked list until the end or the place to insert the new movie.
	{    
		ptr = ptr->next;
	} 

	movie * temp = new movie;  //node to be inserted is created.
	temp->movieName = a;
	temp->totalRating = b;
	temp->numberOfRatings = 1;
	temp->next = ptr->next; //connects the rest
	ptr->next = temp;

}

bool doesExist(string & a, movie * movieHead)// check if the movie already exists in the list.
{
	movie * ptrTemp = movieHead; // creates a new loop pointer and equalizes it to the head pointer.
	while (ptrTemp)
	{
		if(ptrTemp->movieName == a) //it returns true if the movie already exists in the list.
		{
			return true;
		}
		else // goes to the next pointer in the linked list.
		{
			ptrTemp = ptrTemp->next;
		}

	}
	return false; // returns false if the movie does not exist in the linked list.
}

void addRatingManually(	string & movieNameInput, int & ratingInput, movie *& movieHead) // add movie and rating from the keyboard.
{
	cout << "Please enter the name of the movie you wish to rate: ";
	cin >> movieNameInput; // gets the movie name from the user.
	cout << "Please enter the rating you wish to submit (1..10): ";
	cin >> ratingInput; //gets the rating from the user.

	if(ratingInput < 0 || ratingInput > 10) // if rating is not valid, displays a proper message and does not add it to the list.
	{
		cout << "You have entered an invalid rating."<< endl;
	}
	else
	{
		if(doesExist(movieNameInput, movieHead)) // checks if the movies already exists in the linked list and updates the existing movie.
		{
			movie * ptr = movieHead;
			while(ptr->movieName != movieNameInput)
			{
				ptr = ptr->next;
			}
			ptr->totalRating = ptr->totalRating + ratingInput;
			ptr->numberOfRatings++;
			cout << movieNameInput << "has been updated." << endl;
		}
		else //add the movie to the linked list.
		{
			addinOrder(movieNameInput, ratingInput, movieHead);
			cout << movieNameInput << " has been added to the list." << endl;
		}

	}
}

void removeMovie(string & movietobeRemoved, movie *& movieHead) // removes the stated movie from the linked list and connects the list.
{

	cout << "Please enter the name of the movie you wish to remove: " ;
	cin >> movietobeRemoved;
	if(doesExist(movietobeRemoved, movieHead)) // chechs if the movies to be removed exists in the linked list.
	{
		movie * ptrToBeRemoved = movieHead;
		while(ptrToBeRemoved->movieName != movietobeRemoved)
		{
			ptrToBeRemoved = ptrToBeRemoved->next;
		}
		if(ptrToBeRemoved == movieHead) // if the movie to be romoved equals to the head, it removes it makes the next pointer head pointer. 
		{
			movieHead = movieHead->next;
			delete ptrToBeRemoved;
		}
		else // if it is not a head pointer, it finds the movies node to be removed and remove it. Then connects the rest of the linked list.
		{
			movie * ptr = movieHead;
			while(ptr->next != ptrToBeRemoved)
			{
				ptr = ptr->next;
			}
			ptr->next = ptrToBeRemoved->next;
			delete ptrToBeRemoved;
		}
		cout << "The movie " << movietobeRemoved << " has been removed from the file." << endl;
	}
	else
	{
		cout << "Movie " << movietobeRemoved << " does not exist." << endl;
	}
}

void display(movie *& movieHead) // it displays all the movies with their numbmer of ratings and average rating.
{
	movie * ptr = movieHead;
	if(movieHead==NULL) // checks if the linked list is empty.
	{
		cout << "The movie list is empty." << endl;
	}
	else
	{
		cout << "Movie Name"      << setw(30) <<           "Ratings Received"     << setw(20) <<         "Avg. Rating" << endl;
		while(ptr != NULL) //displays every movie in the linked list in this loop.
		{
			int a = ptr->movieName.length();
			cout << ptr->movieName   << setw(30-a) <<     ptr->numberOfRatings      << setw(25) <<     ptr->totalRating/ptr->numberOfRatings << endl;
			ptr = ptr->next;
		}
	}
}

void deleteList(movie *& movieHead)
{
	if (movieHead != nullptr) 
	{
		deleteList(movieHead->next);
		delete movieHead;
	}
}