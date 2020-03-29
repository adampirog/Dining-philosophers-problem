#include "Philosopher.hpp"

extern std::mutex g_lockprint;
extern bool ready;

Philosopher::Philosopher(int ID, Fork &l, Fork &r) : philID(ID), leftFork(l), rightFork(r), life(&Philosopher::dine, this)
{
}

void Philosopher::print(std::string text)
{
    std::lock_guard<std::mutex> cout_lock(g_lockprint);
    std::cout << philID << "  " << text << std ::endl;
}

void Philosopher::think()
{
    static thread_local std::uniform_int_distribution<> wait(1, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(randomDevice) * 150));

    print(" is thinking ");
}

void Philosopher::eat()
{
    std::lock(leftFork.mutex, rightFork.mutex);

    std::lock_guard<std::mutex> left_lock(leftFork.mutex, std::adopt_lock);
    std::lock_guard<std::mutex> right_lock(rightFork.mutex, std::adopt_lock);

    print(" started eating.");

    static thread_local std::uniform_int_distribution<> dist(1, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(randomDevice) * 50));

    print(" finished eating.");
}

void Philosopher::dine()
{
    while (!ready)
        ;

    do
    {
        think();
        eat();
    } while (ready);
}
