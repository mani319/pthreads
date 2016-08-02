#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#define NUM_THREADS 5

using namespace std;

void errorDisplay(const int status, const char *msg)
{
    if (status != 0)
    {
        cout << "*** " << msg << " failed with error code: " << status << " ***" << endl;
        exit(status);
    }
}

void *joining(void *thread_id)
{
	int result = 0;
	result = (long)thread_id + 1000;
	cout << "pthread " << (long)thread_id << " have result = " << result << endl;
	pthread_exit(thread_id);
}

int main(int argc, char const *argv[])
{
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int ret;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(long i = 0; i < NUM_THREADS; i++)
	{
		usleep(100);
		cout << "Creating Thread " << i  << "............" << endl; 
		ret = pthread_create(&thread[i], &attr, joining, (void *)i);
		errorDisplay(ret, "Creating thread");
	}

	pthread_attr_destroy(&attr);

	void *status;
	for (long i = 0; i < NUM_THREADS; i++)
	{
		usleep(100);
		pthread_join(thread[i], &status);
		errorDisplay(ret, "Joining thread");
		cout << "joining thread " << i << " with status = " << (long)status << endl;
	}
	pthread_exit(NULL);
}