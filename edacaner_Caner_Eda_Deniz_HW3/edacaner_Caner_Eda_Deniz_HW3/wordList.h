#ifndef _WORDLIST_H
#define _WORDLIST_H
#include <string>

using namespace std;

struct node // creates a node struct with 4 values
{
	string word ;
	int count ;
	node * next ;
	node * previous ;
};

class wordlist // class definition
{
public:
	wordlist(); //constructor
	void AddWord(string & a);
	void RemoveWord(string & a);
	void DisplayWord(string & a);
	void PrintList();
	void ReversePrintList();
	void DeleteList();
	bool doesExist(string & a);
	void CountUpdate(string & a);
	void DisplayCount(string & a);
private:
	node * head;
	node * tail;
};

#endif