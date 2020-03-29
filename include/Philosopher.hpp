#pragma once
#include <thread>
#include "Fork.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>

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
    void think();
    void eat();
    void dine();

    void print(std::string text);
};