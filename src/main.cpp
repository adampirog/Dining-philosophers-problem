#include <iostream>
#include "Philosopher.h"
#include "Fork.h"
#include "Refresh.h"
#include <cstdlib>
#include <ncurses.h>
#include <thread>
#include <unistd.h>
#include <atomic>
#include <mutex>

using namespace std;

int main()
{
	int nPhils = 6;
	Philosopher **philosopher = new Philosopher *[nPhils];
	Fork *fork[nPhils];
	thread *threads = new thread[nPhils];

	for (int i = 0; i < nPhils; i++)
	{
		fork[i] = new Fork(i);
	}

	for (int i = 0; i < nPhils; i++)
	{
		philosopher[i] = new Philosopher(i);
		philosopher[i]->setForkLeft(fork[i]);
		if (i == 0)
			philosopher[i]->setForkRight(fork[nPhils - 1]);
		else
			philosopher[i]->setForkRight(fork[i - 1]);

		threads[i] = thread(&Philosopher::lifeCycle, philosopher[i]);
	}

	Refresh refresh = Refresh(nPhils, philosopher, fork);
	refresh.draw();

	for (int i = 0; i < nPhils; i++)
		threads[i].join();

	return 0;
}
