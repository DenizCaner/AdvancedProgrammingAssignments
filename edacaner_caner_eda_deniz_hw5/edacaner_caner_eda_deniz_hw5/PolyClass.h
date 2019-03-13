#ifndef _POLYCLASS_H
#define _POLYCLASS_H
#include <string>

using namespace std;

class Polynomial
{
private:
	int order;
	double * top;
public:

	Polynomial(); //Default Constructor
	Polynomial(int & a); //Constructor with order parameter
	~Polynomial();//Destructor
	Polynomial(const Polynomial & a);//Deep Copy Constructor

	Polynomial & Polynomial::operator=(const Polynomial & rhs);
	Polynomial & Polynomial::operator+=(const Polynomial & rhs);
	Polynomial Polynomial::operator+(const Polynomial & rhs);
	Polynomial Polynomial::operator/(double a);
	Polynomial & Polynomial::operator~();
	double Polynomial::operator()(double value);
	//Helper Member Functions
	double * createClone () const; //generates the clone of the list and return the clone's head
	double * Polynomial::GetTop()const;
	int Polynomial::GetOrder()const;
	void Polynomial::SetOrder();
	void deleteList ();
};
	//Free Functions
	ostream & operator<<(ostream & os, const Polynomial & p);
	istream & operator>>(istream & is, Polynomial & p);
	bool operator<(Polynomial & lhs, Polynomial & rhs);
	bool operator>(Polynomial & lhs, Polynomial & rhs);

#endif