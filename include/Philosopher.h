#include <string>
#include <atomic>
#include <mutex>

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "Fork.h"

class Philosopher
{
private:
	int id;
	double eatingTime;
	double eatingMargin;
	double philosophizingTime;
	double philosophizingMargin;
	bool alive;
	int progress;
	Fork* forkLeft;
	Fork* forkRight;
	atomic<int> state; //0 rozmysla, 1 je, 2 czeka na widelce, 3 ma lewy, 4 ma prawy

public:
	Philosopher(int id);
	~Philosopher();
	
	int getId();
	void setId(int id);
	double getEatingTime();
	void setEatingTime(double eatingTime);
	double getPhilosophizingTime();
	void setPhilosophizingTime(double philosophizingTime);
	double getEatingMargin();
	void setEatingMargin(double eatingMargin);
	double getPhilosophizingMargin();
	void setPhilosophizingMargin(double philosophizingMargin);
	bool isAlive();
	void setAlive(bool alive);
	int getProgress();
	void setProgress(int progress);
	void setForkLeft(Fork* forkLeft);
	void setForkRight(Fork* forkRight);
	int getState();
	void setState(int state);
	void lifeCycle();
	void takeForks();
	void releaseForks();
};

#endif // PHILOSOPHER_H