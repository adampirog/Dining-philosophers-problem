#pragma once
#include "Fork.h"
#include <random>

class Philosopher
{
public:
	std::mt19937 rng{std::random_device{}()};
	int philID;
	double philTimer;
	double eatingTime;
	double eatingMargin;
	double philosophizingTime;
	double philosophizingMargin;
	bool alive;
	int progress;
	Fork *forkLeft;
	Fork *forkRight;
	atomic<int> state; //0 filozofuje, 1 je, 2 czeka

public:
	Philosopher(int id);
	~Philosopher();

	int getId();
	void setId(int id);
	double getTimer();
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
	void setForkLeft(Fork *forkLeft);
	void setForkRight(Fork *forkRight);
	int getState();
	void setState(int state);
	void lifeCycle();
	void takeForks();
	void releaseForks();
};