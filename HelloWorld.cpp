#include <pthread.h>
#include <stdlib.h>
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

void *HelloWorld(void *thread_id)
{
	cout << "Hello World!! This is thread " << (long)thread_id << endl;
	pthread_exit(NULL);
}

int main()
{
	pthread_t thread[NUM_THREADS];
	int ret;

	for(long i = 0; i < NUM_THREADS; i++)
	{
		cout << "Creating Thread " << i << endl;
		ret = pthread_create(&thread[i], NULL, HelloWorld, (void *)i);
		errorDisplay(ret, "Creating Thread");
	}
	pthread_exit(NULL);
}