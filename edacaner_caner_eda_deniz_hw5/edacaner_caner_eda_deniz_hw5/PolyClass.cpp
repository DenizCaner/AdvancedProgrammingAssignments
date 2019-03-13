#include <iostream>
#include <cctype>
#include <string>
#include "PolyClass.h"

using namespace std;

Polynomial::Polynomial() // Default constructor
{
	double * ptr =new double[1];
	top = ptr;
	order = 0;
}

Polynomial::Polynomial(int & a)  //Constructor with order parameter
{
	order = a;
	double * ptr = new double[a+1];
	top = ptr;
}

Polynomial::~Polynomial() //Destructor
{
	delete [] top;
}

Polynomial::Polynomial(const Polynomial & a) // Deep Copy Constructor
{
	top = a.createClone();
	order = a.order;
}

//Helper Fuctions (MEmber Functions)

double * Polynomial::createClone () const // creates the clone in order make a deep copy
{
	if (top == NULL)  //if list is empty
		return NULL;   //clone is empty as well

	int a = this->order ;
	double * cloneTop = new double [a+1]; // creates the firt node of the clone
	for(int i = 0; i < a+1 ; i++) 
	{
		cloneTop[i] = top[i]; // equalizes the values 
	}
	return cloneTop;
}

void Polynomial::deleteList () // Deletes the array pointed by top pointer
{
	delete [] top;
}

int Polynomial::GetOrder() const // returns the order of the polynomial
{
	return this->order;
}

double * Polynomial::GetTop() const //Returns the top pointer of the polynomial
{
	return this->top;
}

void Polynomial::SetOrder() // checks if the coefficients with the biggest order is zero or not if so increments the order value
{
	int a = this->order;
	while(top[a] == 0 && this->order > 0)
	{
		this->order--;
		a--;
	}
	if(top[a] == 0 && this->order == 0)
	{
		top[0] = 0;
	}
}


//Operators

Polynomial & Polynomial::operator=(const Polynomial & rhs) //Assignment operator
{
	if (this != &rhs)
	{
		deleteList(); // same as this->deleteList()
		top = rhs.createClone();
		order = rhs.order;
	}
	return *this;
}

Polynomial & Polynomial::operator+=(const Polynomial & rhs)  // add the right hand side value to the left hand side value and retuns the lhs
{		
	if(this->order == rhs.order) // checks if their orders are the same
	{
		for (int i = 0; i < (this->order)+1 ; i++)
		{
			this->top[i] = this->top[i] + rhs.top[i];
		}
		this->SetOrder();
	}
	else if(this->order > rhs.order) // checks if the order of the lhs is larger than the order of rhs
	{
		int i = 0;
		int j = this->order - rhs.order + 1;
		for (i; i < rhs.order+1 ; i++)
		{
			this->top[i] = this->top[i] + rhs.top[i];
		}
		for(int a = 1; a < j ; a++)
		{
			this->top[i+a] = this->top[i+a];
		}
	}
	else if(this->order < rhs.order) // checks if the order of the lhs is smaller than the order of rhs
	{
		Polynomial temp(rhs);
		int i = 0;
		int j = rhs.order - this->order + 1;
		for (i; i < this->order+1 ; i++)
		{
			temp.top[i] = this->top[i] + rhs.top[i];
		}
		*this = temp;
	}
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial & rhs)  // adds two values and assign the resulting value to a new one
{
	Polynomial sumPoly(*this);
	sumPoly += rhs;
	return sumPoly;
}

Polynomial Polynomial::operator/(double a) //divides all the coefficients of the polynomial by double a 
{
	Polynomial p = *this;
	for(int i = 0; i < this->order+1 ; i++)
	{
		p.top[i] = this->top[i]/a;
	}
	return p;
}

Polynomial & Polynomial::operator~() // takes the derivative of the given polynomial
{
	for(int i = 0; i < this->order + 1; i++) // multiplies every coefficient by the power 
	{
		this->top[i] = this->top[i] * i;
	}
	for(int k = 0; k < this->order ; k++) 
	{
		this->top[k] = this->top[k+1];
	}
	this->top[this->order] = 0;
	this->SetOrder();
	return *this;
}

double Polynomial::operator()( double value) //calculates the value of the polynomial at given double values
{
	double sum = 0;
	double tempSum = 0;
	for(int i = 0; i < this->order+1 ; i++)
	{
		if(i == 0)
		{
			tempSum= this->top[i];
		}
		else
		{
			tempSum = value;
			for (int j = 1 ; j < i ; j++)
			{
				tempSum = tempSum*value;
			}
			tempSum = tempSum * this->top[i];
		}
		sum = sum + tempSum;
		tempSum = 0;
	}
	value = 0;
	return sum;
}

bool operator>(Polynomial & lhs, Polynomial & rhs) // checks if the order of the lhs is larger than the order of rhs
{
	bool status;
	if(lhs.GetOrder() > rhs.GetOrder())
		status = true;
	else
		status = false;
	return status;

}

bool operator<(Polynomial & lhs, Polynomial & rhs) // checks if the order of the lhs is smaller than the order of rhs
{
	bool status;
	if(lhs.GetOrder() < rhs.GetOrder())
		status = true;
	else
		status = false;
	return status;
}

ostream & operator<<(ostream & os, const Polynomial & p) //output stream operator: prompts the polynomial mathematically
{
	double * temp = p.GetTop();
	int k = p.GetOrder();
	for(k; k > 1; k--)
	{
		if(temp[k] != 0)
		{
			if (temp[k] < 0)
			{
				if(temp[k] == -1)
					cout << "-x^" << k << " ";
				else
					cout << temp[k] << "x^" << k << " ";
			}
			else if (temp[k] > 0)
			{
				if(temp[k] == 1)
					cout << "x^" << k << " ";
				else
					cout << "+" << temp[k] << "x^" << k << " ";
			}
		}
	}
	if(k == 1)
	{
		if(temp[k] != 0)
		{
			if (temp[k] < 0)
			{
				cout << temp[k] << "x" << " ";
			}
			else if (temp[k] > 0)
			{
				cout << "+" << temp[k] << "x" << " " ;
			}
		}
		k--;
	}
	if(temp[k] != 0)
	{
		if (temp[k] < 0)
		{
			cout << temp[k] <<  " ";
		}
		else if (temp[k] > 0)
		{
			cout << "+" << temp[k] << " " ;
		}		
	}
	if(p.GetOrder() == 0 && temp[0] == 0)
	{
		cout << temp[0] ;
	}
	return os;
}

istream & operator>>(istream & is, Polynomial & p) // assigns the given coefficient values to the polynomial array
{
	double *ptr = p.GetTop();
	int pOrder = p.GetOrder();
	double ch;
	while ( pOrder >= 0 && is >> ch )
	{
		ptr[pOrder] = ch;
		pOrder--;
	}
	p.SetOrder();
	return is;
}