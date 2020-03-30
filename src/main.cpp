
#include "Philosopher.h"
#include "Fork.h"
#include "Painter.h"
#include <thread>

using namespace std;

int main()
{
	//----ZMIANA LICZBY WATKOW
	int nPhils = 6;
	//---------------------

	Philosopher **philosophers = new Philosopher *[nPhils];
	Fork *fork[nPhils];
	thread *threads = new thread[nPhils];

	for (int i = 0; i < nPhils; i++)
	{
		fork[i] = new Fork(i);
	}

	for (int i = 0; i < nPhils; i++)
	{
		philosophers[i] = new Philosopher(i);
		philosophers[i]->setForkRight(fork[i]);
		if (i == 0)
			philosophers[i]->setForkLeft(fork[nPhils - 1]);
		else
			philosophers[i]->setForkLeft(fork[i - 1]);

		threads[i] = thread(&Philosopher::lifeCycle, philosophers[i]);
	}

	Painter painter = Painter(nPhils, philosophers, fork);
	painter.draw();

	for (int i = 0; i < nPhils; i++)
		threads[i].join();

	return 0;
}
