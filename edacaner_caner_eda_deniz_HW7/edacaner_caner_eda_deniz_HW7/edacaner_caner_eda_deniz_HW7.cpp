#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "HW7IntQueue.h"
#include "randgen.h"

using namespace std;

// Eda Deniz Caner - 17915

//global variables in order to avoid sending them to threads as a reference variable

mutex myMutex, coutMutex;
int arrivalMax, arrivalMin;
int checkoutMax, checkoutMin;
int customerNumber ;
int total_customer_count;
int queue1size, queue2size ;
bool isBusyA = false, isBusyB = false;
int arrivalRange;
int counterA = 1, counterB = 1;

HW7IntQueue myQueue1;
HW7IntQueue myQueue2;

void customer() //produces customer and add them to the queues of the cashiers
{
	RandGen randgen; 
	arrivalRange = randgen.RandInt (arrivalMin, arrivalMax); // generates a random number between the entered values to decide the frequency of customers coming to the line

	for( customerNumber = 1; customerNumber <= total_customer_count; customerNumber++) // generates a specifired number of customer 
	{
		myMutex.lock(); // locks the mutex in order to perform a change 

		if(myQueue1.getQueueSize() > myQueue2.getQueueSize() ) // if there are less people in cashier B's line the new customer goes into that line
		{
			myQueue2.enqueue(customerNumber);
			queue2size = myQueue2.getQueueSize();
			myMutex.unlock();
			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"Customer "<< customerNumber << " has arrived at cashier B's line (queue size is " << queue2size <<  " ): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();//unlocks the mutex
		}
		else if(myQueue1.getQueueSize() < myQueue2.getQueueSize())  // if there are less people in cashier A's line the new customer goes into that line
		{
			myQueue1.enqueue(customerNumber);
			queue1size = myQueue1.getQueueSize();
			myMutex.unlock();//unlock the mutex after performing a change
			coutMutex.lock();// locks the mutex to cout the unchanged version
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"Customer "<< customerNumber << " has arrived at cashier A's line (queue size is " << queue1size <<  " ): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();//unlocks the mutex
		}
		else if(myQueue1.getQueueSize() == myQueue2.getQueueSize()) // if there are equal number of people in both lines
		{
			if(isBusyA == false) // if cashier A is not busy he/she goes to cashier A
			{
				myQueue1.enqueue(customerNumber);
				queue1size = myQueue1.getQueueSize();
				myMutex.unlock(); //unlock the mutex after performing a change
				coutMutex.lock();// locks the mutex to cout the unchanged version
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout <<"Customer "<< customerNumber << " has arrived at cashier A's line (queue size is " << queue1size <<  " ): "<< put_time(ptm,"%X") <<endl;
				coutMutex.unlock();//unlocks the mutex
			}
			else // if cashier A is busy he/she goes to cashier B
			{
				myQueue2.enqueue(customerNumber);
				queue2size = myQueue2.getQueueSize();
				myMutex.unlock();//unlock the mutex after performing a change
				coutMutex.lock();// locks the mutex to cout the unchanged version
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout <<"Customer "<< customerNumber << " has arrived at cashier B's line (queue size is " << queue2size <<  " ): "<< put_time(ptm,"%X") <<endl;
				coutMutex.unlock(); //unlocks the mutex
			}
		}
		this_thread::sleep_for(chrono::seconds(arrivalRange)); // simulation for consume
	}
}

void cashierA()
{
	int item;
	int checkoutRange;

	while(counterA + counterB <= total_customer_count+1 )
	{	
		RandGen randgen; 
		checkoutRange = randgen.RandInt (checkoutMin, checkoutMax); // generates a random number to decide the frequency of a cashier to deal with a customr

		myMutex.lock(); // locks the mutex to perform a change
		if (!myQueue1.isEmpty()) 
		{  
			myQueue1.dequeue(item);
			counterA++;
			queue1size =  myQueue1.getQueueSize();
			myMutex.unlock(); //unlock the mutex after performing a change

			coutMutex.lock();// locks the mutex to cout the unchanged version
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout << "Cashier A started transaction with Customer "<< item <<"(queue size is " << queue1size <<" ) " << put_time(ptm,"%X") <<endl;
			isBusyA = true;
			coutMutex.unlock();//unlocks the mutex

			this_thread::sleep_for(chrono::seconds(checkoutRange)); // simulation for consume

			coutMutex.lock();// locks the mutex to cout the unchanged version
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 
			cout << "Cashier A finished transaction with Customer "<< item <<" :" << put_time(ptm,"%X") <<endl;
			isBusyA = false;
			coutMutex.unlock();//unlocks the mutex
		}
		else 
		{
			myMutex.unlock(); //unlock the mutex without performing any change
		}
	}
}

void cashierB()
{
	int item;
	int checkoutRange;

	while(counterA + counterB <= total_customer_count + 1 )
	{	
		RandGen randgen; 
		checkoutRange = randgen.RandInt (checkoutMin, checkoutMax);

		myMutex.lock(); // locks the mutex to perform a change
		if (!myQueue2.isEmpty()) 
		{  
			myQueue2.dequeue(item);
			counterB++;
			queue2size =  myQueue2.getQueueSize();
			myMutex.unlock();  //unlock the mutex after performing a change

			coutMutex.lock();// locks the mutex to cout the unchanged version
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout << "Cashier B started transaction with Customer "<< item <<"(queue size " << queue2size <<" ) " << put_time(ptm,"%X") <<endl;
			isBusyB = true;
			coutMutex.unlock();//unlocks the mutex

			this_thread::sleep_for(chrono::seconds(checkoutRange)); // simulation for consume

			coutMutex.lock();// locks the mutex to cout the unchanged version
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt); 
			cout << "Cashier B finished transaction with Customer "<< item <<" :" << put_time(ptm,"%X") <<endl;
			isBusyB = false;
			coutMutex.unlock();//unlocks the mutex
		}
		else
		{
			myMutex.unlock(); //unlock the mutex without performing any change
		}
	}
}

int main()
{
	//asks user to enter a number as a total_customer_count
	cout << "Please enter the total number of customers to be served:" ;
	cin >> total_customer_count ;
	cout << endl;

	myQueue1.allocateCapacity(total_customer_count/2); // allocate enough memory for the queue1
	myQueue2.allocateCapacity(total_customer_count/2); // allocate enough memory for the queue2

	//asks user to enter two numbers to generate a random numbet between them
	cout << "Please enter the inter-arrival time range between two customers" << endl;
	cout << "min:"; cin >> arrivalMin; cout << endl;
	cout << "max:"; cin >> arrivalMax; cout << endl;

	//asks user to enter two numbers to generate a random numbet between them
	cout << "Please enter the checkout time range of cashiers" << endl ;
	cout << "min:"; cin >> checkoutMin; cout << endl;
	cout << "max:"; cin >> checkoutMax; cout << endl;

	coutMutex.lock();
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout <<"Simulation begins at "<< put_time(ptm,"%X") <<endl;
	coutMutex.unlock();

	thread thr0(customer); //creates a thread with customer function
	thread thr1(cashierA); //creates a thread with cashierA function
	thread thr2(cashierB); //creates a thread with cashierB function

	//joins the threads
	thr0.join();
	thr1.join();
	thr2.join();

	coutMutex.lock();
	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout <<"Simulation ends at "<< put_time(ptm,"%X") <<endl;
	coutMutex.unlock();

	return 0;
}