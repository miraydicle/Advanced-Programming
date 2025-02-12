// written by Miray Dicle
// used Visual Studio 2012 version

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <time.h>
#include <ctime>
#include <iomanip>
#include "PrintQueue_class.h"

using namespace std;

//global variables
PrintQueue myQueue;
mutex myMutex1,myMutex2,coutMutex;
int maxPrintJobs, minpage, maxpage, mintime, maxtime;

//random number generator
int random_range(const int & min, const int & max)
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

//function for printer thread
void printer()
{
	int id, numofpages;
	int counter = 0;

	while(counter!=maxPrintJobs)
	{
		myMutex1.lock();
		if(!myQueue.isEmpty())
		{
			myQueue.dequeue(id,numofpages);
			counter++;//tracks the number of print jobs
		    myMutex1.unlock();
		    int size = myQueue.getCurrentSize();
		    coutMutex.lock();
			//reads current time
		    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
		    struct tm *ptm = new struct tm; 
		    localtime_s(ptm, &tt);
		    cout<<"The printer started to print the job with ID:"<<id<<", number of pages: "<<numofpages<<" (queue size is: "<<size<<" ) "<<put_time(ptm,"%X")<<endl;
		    coutMutex.unlock();
		    this_thread::sleep_for(chrono::seconds(numofpages)); //processes print jobs per second
		    coutMutex.lock();
			//reads current time
		    tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
		    localtime_s(ptm, &tt);
		    cout<<"The printer finished printing the job with ID:"<<id<<", number of pages: "<<numofpages<<" "<<put_time(ptm,"%X")<<endl;
	        coutMutex.unlock();
		}
		else
		{
			myMutex1.unlock(); //unlocks mutex if queue is not empty
		}
	}
}

//function for user threads
void user(int consId)
{
	
	int id;
	static int next_id = 1;
	int dur = random_range(mintime,maxtime); //creates random duration time for sleep

	this_thread::sleep_for(chrono::seconds(dur)); //sleeps before first print job

	while(next_id<=maxPrintJobs)
	{

		int numberofpages = random_range(minpage,maxpage); //creates random number of pages per print job
		myMutex2.lock(); //mutex for user enqueue
		myMutex1.lock(); //mutex for printer dequeue
		if(next_id<=maxPrintJobs)
		{

		id = next_id; //ids for print jobs
		next_id++;
		myQueue.enqueue(id,numberofpages);
		myMutex1.unlock();
		myMutex2.unlock();
		int size = myQueue.getCurrentSize();
		coutMutex.lock();
		//reads current time
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt);
		cout<<"User "<<consId<<" sent new print job with ID "<<id<<" sent to the printer queue, number of pages: "<<numberofpages<<" (print queue size: "<<size<<") "<<put_time(ptm,"%X")<<endl;
		coutMutex.unlock();
		this_thread::sleep_for(chrono::seconds(dur)); //sleeps after each print job
		}
		else
		{
			//unlocks mutexes if queue is not empty
			myMutex1.unlock();
			myMutex2.unlock();
		}
	}
}

int main()
{
	
	cout<<"Please enter the max number of print jobs: ";
	cin>>maxPrintJobs;
	cout<<"Please enter the min and max values for the waiting time period (in seconds) after creating a print job: "<<endl;
    cout<<"Min: ";
	cin>>mintime;
	cout<<"Max: ";
	cin>>maxtime;
	cout<<"Please enter the min and max values for the number of pages in a print job: "<<endl;
	cout<<"Min number of pages: ";
	cin>>minpage;
	cout<<"Max number of pages: ";
	cin>>maxpage;

	//reads current time
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt);

	cout<<"Simulation starts "<<put_time(ptm,"%X")<<endl;

	//threads
	thread thr1(user, 1);
	thread thr2(user, 2);
	thread thr3(user, 3);
	thread thr4(printer);

	//handles time gaps for the end of simulation
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();

	//reads current time
	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	localtime_s(ptm, &tt);
	cout<<"End of the simulation ends "<<put_time(ptm,"%X")<<endl;

	cin.get();
	cin.ignore();
	return 0;
}
