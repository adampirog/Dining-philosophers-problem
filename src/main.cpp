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

int main(){
	int n = 5;
	Philosopher** philosopher = new Philosopher*[n];
	Fork* fork[n];
	thread* threads = new thread[n];

	for (int i = 0; i < n; i++){
		fork[i] = new Fork(i);
	}

	for (int i = 0; i < n; i++){
		philosopher[i] = new Philosopher(i);
		philosopher[i]->setForkLeft(fork[i]);
		if(i == 0)
			philosopher[i]->setForkRight(fork[n - 1]);
		else
			philosopher[i]->setForkRight(fork[i - 1]);

		threads[i] = thread(&Philosopher::lifeCycle, philosopher[i]);
	}

	Refresh refresh = Refresh(n, philosopher, fork);
	refresh.draw();

	for(int i = 0; i < 5; i++)
		threads[i].join();

	return 0;
}

