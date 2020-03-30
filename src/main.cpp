
#include "Philosopher.h"
#include "Fork.h"
#include "Painter.h"
#include <thread>
#include <iostream>
#include <curses.h>

using namespace std;

int main()
{
	int nPhils = 5;
	cout << "Podaj liczbę wątków: ";
	cin >> nPhils;

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

	cout << "Zamykam wątki..." << endl;
	for (int i = 0; i < nPhils; i++)
		threads[i].join();

	return 0;
}
