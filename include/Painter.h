#pragma once
#include "Philosopher.h"

using namespace std;

class Painter
{
public:
	int nPhils;
	Philosopher **philosopher;
	Fork **fork;

	Painter(int n, Philosopher **philosopher, Fork **fork);
	~Painter();

	void init();
	void draw();
	void drawFrame();
	void drawPhilosophers();
	void drawPhilosophersDetails();
	void drawForks();
	void drawForksDetails();
};
