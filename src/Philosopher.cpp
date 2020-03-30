#include "Philosopher.h"
#include <unistd.h>
#include <ncurses.h>

using namespace std;

Philosopher::Philosopher(int philID)
{
	this->philID = philID;
	alive = true;
	state = 0;
	progress = 0;
}

Philosopher::~Philosopher()
{
}

int Philosopher::getId()
{
	return philID;
}

void Philosopher::setId(int philID)
{
	this->philID = philID;
}

double Philosopher::getTimer()
{
	return philTimer;
}

void Philosopher::setEatingTime(double eatingTime)
{
	this->eatingTime = eatingTime;
}
double Philosopher::getPhilosophizingTime()
{
	return philosophizingTime;
}

void Philosopher::setPhilosophizingTime(double philosophizingTime)
{
	this->philosophizingTime = philosophizingTime;
}

double Philosopher::getEatingMargin()
{
	return eatingTime;
}

void Philosopher::setEatingMargin(double eatingMargin)
{
	this->eatingMargin = eatingMargin;
}
double Philosopher::getPhilosophizingMargin()
{
	return philosophizingMargin;
}

void Philosopher::setPhilosophizingMargin(double philosophizingMargin)
{
	this->philosophizingMargin = philosophizingMargin;
}

bool Philosopher::isAlive()
{
	return alive;
}

void Philosopher::setAlive(bool alive)
{
	this->alive = alive;
}

int Philosopher::getProgress()
{
	return progress;
}

void Philosopher::setProgress(int progress)
{
	this->progress = progress;
}

void Philosopher::setForkLeft(Fork *forkLeft)
{
	this->forkLeft = forkLeft;
}

void Philosopher::setForkRight(Fork *forkRight)
{
	this->forkRight = forkRight;
}

int Philosopher::getState()
{
	return state;
}

void Philosopher::setState(int state)
{
	this->state = state;
}

//0 filozofuje, 1 je, 2 czeka
void Philosopher::lifeCycle()
{
	while (alive)
	{
		int base = 120000;
		uniform_int_distribution<int> dist(0, 50000);
		philTimer = base + dist(rng);

		state = 0;
		for (int i = 0; i < 21; i++)
		{
			usleep(philTimer);
			progress++;
		}
		progress = 0;
		state = 2;
		takeForks();
		state = 1;
		for (int i = 0; i < 21; i++)
		{
			usleep(philTimer);
			progress++;
		}
		progress = 0;
		releaseForks();
	}

	return;
}

void Philosopher::takeForks()
{
	if (forkLeft->getId() < forkRight->getId())
	{
		forkLeft->setBusy(true, philID);
		forkRight->setBusy(true, philID);
	}
	else
	{
		forkRight->setBusy(true, philID);
		forkLeft->setBusy(true, philID);
	}
}

//0 filozofuje, 1 je, 2 czeka
void Philosopher::releaseForks()
{
	if (forkLeft->getId() > forkRight->getId())
	{
		forkLeft->setBusy(false, philID);
		forkRight->setBusy(false, philID);
	}
	else
	{
		forkRight->setBusy(false, philID);
		forkLeft->setBusy(false, philID);
	}
}