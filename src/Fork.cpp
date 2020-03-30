#include "Fork.h"
#include <string>

using namespace std;

Fork::Fork(int id){
	this->id = id;
	this->occupied = false;
	this->philosopherId = 0;
}

Fork::~Fork(){
}

int Fork::getId(){
	return id;
}

void Fork::setId(int id){
	this->id = id;
}

void Fork::setOccupied(bool occupied, int philosopherId){
	if(occupied){
		unique_lock<mutex> l(lock);
		cvOccupied.wait(l, [this](){return this->occupied == false;});
		this->philosopherId = philosopherId;
		this->occupied = occupied;
		l.unlock();
	}
	else{
		unique_lock<mutex> l(lock);
		this->philosopherId = -1;
		this->occupied = occupied;
		l.unlock();
		cvOccupied.notify_all();
	}
}

bool Fork::isOccupied(){
	return occupied;
}

void Fork::setPhilosopherId(int philosopherId){
	this->philosopherId = philosopherId;
}

int Fork::getPhilisopherId(){
	return philosopherId;
}

void Fork::setState(int state){
	this->state = state;
}

int Fork::getState(){
	return state;
}