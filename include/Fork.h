#ifndef FORK_H
#define FORK_H

#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

class Fork{
private:
	int id;
	atomic<bool> occupied;
	int philosopherId;
	int state;

	mutex lock;
	condition_variable cvOccupied;

public:
	Fork(int id);
	~Fork();
	int getId();
	void setId(int id);
	void setOccupied(bool occupied, int id);
	bool isOccupied();
	void setPhilosopherId(int philosopherID);
	int getPhilisopherId();
	void setState(int state);
	int getState();
};

#endif //FORK_H