#ifndef REFRESH_H
#define REFRESH_H

#include <cstdlib>
#include <thread>
#include <unistd.h>
#include "Philosopher.h"

using namespace std;

class Refresh{
public:
	int n;
	Philosopher** philosopher;
	Fork** fork;

	Refresh(int n, Philosopher** philosopher, Fork** fork);
	~Refresh();

	void init();
	void draw();
	void drawFrame();
	void drawPhilosophers();
	void drawPhilosophersDetails();
	void drawForks();
	void drawForksDetails();
};

#endif // REFRESH_H