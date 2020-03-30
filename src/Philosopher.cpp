#include "Philosopher.h"
#include <unistd.h>

using namespace std;

Philosopher::Philosopher(int philID)
{
	this->philID = philID;
	eatingTime = 5;
	eatingMargin = 1;
	philosophizingTime = 5;
	philosophizingMargin = 1;
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

double Philosopher::getEatingTime()
{
	return eatingTime;
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

//0 rozmysla, 1 je, 2 czeka na widelce, 3 otrzymal lewy, 4 otrzymal prawy
void Philosopher::lifeCycle()
{
	srand(time(NULL));
	while (alive)
	{
		int pT = (int)(philosophizingTime * 50000);
		int pMd = 2 * (int)rand() % ((int)(philosophizingMargin * 50000));
		int pMu = (int)(philosophizingMargin * 50000);

		int eT = (int)(eatingTime * 50000);
		int eMd = 2 * (int)rand() % ((int)(eatingMargin * 50000));
		int eMu = (int)(eatingMargin * 50000);

		state = 0;
		for (int i = 0; i < 20; i++)
		{
			usleep(pT + pMd - pMu);
			progress++;
		}
		progress = 0;
		state = 2;
		takeForks();
		state = 1;
		for (int i = 0; i < 20; i++)
		{
			usleep(eT + eMd - eMu);
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

//0 rozmysla, 1 je, 2 czeka na widelce, 3 otrzymal lewy, 4 otrzymal prawy
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