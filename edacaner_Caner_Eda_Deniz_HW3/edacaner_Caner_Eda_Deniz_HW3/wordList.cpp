#include <iostream>
#include <cctype>
#include <string>
#include "wordList.h"

using namespace std;

wordlist::wordlist()
{
	head = NULL; //equalizes head pointer to null
	tail = NULL; //equalizes tail pointer to null
}

void wordlist::AddWord(string & a) // this function is created to add a word to a sorted doubly linked list.
{
	if (head == NULL)  // checks if the list is empty.
	{   // creates a new node and equalizes head pointer to it.
		node* tmp = new node;
		tmp->word = a;
		tmp->count = 1;
		head = tmp; //equalizes head pointer to tmp
		tail = tmp; //equalizes tail pointer to tmp
		tail->previous = NULL; //equalizes tail->previous to null
		tail->next = NULL; //equalizes tail->next to null
		head->previous = NULL; //equalizes head->previous to null
		head->next = NULL; //equalizes head->next to null
		return;
	}
	if( a < head->word) // check if new nodes should be added before the head of the list.
	{//creates a new node and makes it a head pointer and connects to the rest of the link list.
		node * temp = new node;  //node to be inserted 
		temp->word = a;
		temp->count = 1;
		temp->next = head;
		head->previous = temp;
		head = temp;
		head->previous = NULL; //equalizes head->previous to null
		return;
	}
	node * ptr = head;   // loop variable
	while (ptr->next != NULL && ptr->next && ptr->next->word < a) //search the linked list until the end or the place to insert the new node.
	{    
		ptr = ptr->next;
	} 
	if(ptr->next)
	{
		node * temp = new node;  //node to be inserted is created.
		temp->word = a;
		temp->count = 1;
		ptr->next->previous = temp;
		temp->next = ptr->next; //connects the rest
		ptr->next = temp;
		temp->previous = ptr;
	}
	else
	{
		node * temp = new node;  //node to be inserted is created.
		temp->word = a;
		temp->count = 1;
		ptr->next = temp;
		tail = temp;
		tail->previous = ptr;
		tail->next = NULL;
	}
}

bool wordlist::doesExist(string & a) //checks whether it already exists in the list.
{
	node * ptrTemp = head; // creates a new loop pointer and equalizes it to the head pointer.
	while (ptrTemp != NULL)
	{
		if(ptrTemp->word == a) //it returns true if the word already exists in the list.
		{
			return true;
		}
		else // goes to the next pointer in the linked list.
		{
			ptrTemp = ptrTemp->next;
		}
	}
	return false; // returns false if the node does not exist in the linked list.
}

void wordlist::CountUpdate(string & a)
{
	node * ptr = head;   // loop variable
	while (ptr->next && ptr->word != a) //search the linked list until the end or the place to insert the new node.
	{    
		ptr = ptr->next;
	} 
	ptr->count++; // updates the count of the node
}

void wordlist::DisplayWord(string & a)
{
	node * ptr = head;   // loop variable
	while (ptr->next && ptr->next->word != a) //search the linked list until the end or the place to insert the new node.
	{    
		ptr = ptr->next;
	} 
	cout << a << "  " << ptr->count << endl;
}

void wordlist::RemoveWord(string & a)
{
	if(head != NULL) // checks whether the list is empty
	{
		node * ptr = head; 
		while (ptr != NULL  && ptr->word != a) //search the linked list until the end or the place to insert the new node.
		{    
			ptr = ptr->next;
		} 
		if(ptr->word == a) 
		{

			if(ptr->word == head->word) // if node to be removed is head
			{
				if(head->next == NULL) // check if it is the last element to be removed from the list
				{
					head = NULL;
					tail = NULL;
					delete ptr;
				}
				else{
					head = head->next; // updates the head
					delete ptr;
				}
			}
			else if(ptr->word == tail->word) // if node to be removed is tail
			{
				tail = ptr->previous;
				tail->next = NULL; // equalizes tail->next to null
				delete ptr;
			}
			else
			{
				ptr->previous->next = ptr->next;
				ptr->next->previous = ptr->previous;
				delete ptr;
			}
		}
		else
		{
			cout << a << "does not exist in the list." << endl;
		}
	}
}

void wordlist::PrintList() // prints the sorted list
{
	node * temp = head; // creates a lopp pointer
	while(temp != NULL) 
	{
		cout << temp->word << "   " << temp->count << endl;
		temp = temp->next;
	}
}

void wordlist::ReversePrintList() // prints the list in the reverse order
{
	node * ptr = tail; // creates a loop pointer

	while(ptr!= NULL)
	{
		cout << ptr->word << "   " << ptr-> count << endl;
		ptr = ptr->previous ;
	}

}

void wordlist::DisplayCount(string & a) // dipslays the count of a specific word
{
	node * ptr = head;
	while(ptr != NULL && ptr->word != a)
	{
		ptr = ptr->next;
	}
	cout << a << "  "<< ptr->count << endl;
}