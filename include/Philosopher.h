#pragma once
#include "Fork.h"
#include <random>

class Philosopher
{
public:
	std::mt19937 rng{std::random_device{}()};
	int philID;
	double philTimer;
	bool alive;
	int progress;
	Fork *forkLeft;
	Fork *forkRight;
	//0 filozofuje, 1 je, 2 czeka
	atomic<int> state;

public:
	Philosopher(int id);
	~Philosopher();

	int getId();
	void setId(int id);
	double getTimer();
	bool isAlive();
	void setAlive(bool alive);
	int getProgress();
	void setProgress(int progress);
	void setForkLeft(Fork *forkLeft);
	void setForkRight(Fork *forkRight);
	int getState();
	void setState(int state);
	void life();
	void takeForks();
	void releaseForks();
};