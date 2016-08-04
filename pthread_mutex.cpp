#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#define NUM_THREADS 5

using namespace std;

pthread_t thread[NUM_THREADS];
pthread_attr_t attr;
pthread_mutex_t fn_mutex;

void errorDisplay(const int status, const char *msg)
{
    if (status != 0)
    {
        cout << "*** " << msg << " failed with error code: " << status << " ***" << endl;
        exit(status);
    }
}

void *fn(void *thread_id)
{
	pthread_mutex_lock(&fn_mutex); // lock mutex
	cout << "Thread " << (long)thread_id << " started" << endl;

	for(int i = 0; i < 1000000; i++);

	cout << "Thread " << (long)thread_id << " ended" << endl;
	pthread_mutex_unlock(&fn_mutex); // unlock mutex

	pthread_exit((void *)0);
}

int main(int argc, char const *argv[])
{
	int ret;

	// Initializing and Setting detach state for attribute
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// Initializing mutex variable
	ret = pthread_mutex_init(&fn_mutex, NULL);
	errorDisplay(ret, "Mutex Initialization");

	// Creating threads
	for(long i = 0; i < NUM_THREADS; i++)
	{
		cout << "Creating Thread " << i  << "............" << endl; 
		ret = pthread_create(&thread[i], &attr, fn, (void *)i);
		errorDisplay(ret, "Creating thread");
	}

	// destroying the attribute
	pthread_attr_destroy(&attr);
	
	// Joining threads using status variable
	void *status;
	for (long i = 0; i < NUM_THREADS; ++i)
	{
		usleep(100);
		ret = pthread_join(thread[i], &status);
		errorDisplay(ret, "Joining thread");
		cout << "joining thread " << i << " with status = " << (long)status << endl;
	}
	pthread_exit(NULL);
}