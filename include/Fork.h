#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

class Fork
{
private:
	int forkID;
	atomic<bool> busy;
	int philID;

	mutex lock;
	condition_variable cv;

public:
	Fork(int id);
	int getId();
	void setId(int id);
	void setBusy(bool occupied, int id);
	bool isBusy();
	void setPhilID(int philosopherID);
	int getPhilID();
};
