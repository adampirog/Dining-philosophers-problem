#pragma once
#include <thread>
#include "Fork.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>
#include <ncurses.h>

class Philosopher
{
private:
    int philID;
    Fork &leftFork;
    Fork &rightFork;
    std::thread life;
    std::mt19937 randomDevice{std::random_device{}()};

public:
    Philosopher(int ID, Fork &l, Fork &r);
    ~Philosopher();
    void think();
    void eat();
    void dine();
    const char *getName();

    void print(bool state);
};