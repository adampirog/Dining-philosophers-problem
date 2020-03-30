#include "Fork.h"

using namespace std;

Fork::Fork(int id)
{
	this->forkID = id;
	this->busy = false;
	this->philID = -1;
}

int Fork::getId()
{
	return forkID;
}

void Fork::setId(int forkID)
{
	this->forkID = forkID;
}

void Fork::setBusy(bool busy, int philID)
{
	if (busy)
	{
		unique_lock<mutex> l(lock);
		cv.wait(l, [this]() { return this->busy == false; });
		this->philID = philID;
		this->busy = busy;
		l.unlock();
	}
	else
	{
		unique_lock<mutex> l(lock);
		this->philID = -1;
		this->busy = busy;
		l.unlock();
		cv.notify_all();
	}
}

bool Fork::isBusy()
{
	return busy;
}

void Fork::setPhilID(int philID)
{
	this->philID = philID;
}

int Fork::getPhilID()
{
	return philID;
}