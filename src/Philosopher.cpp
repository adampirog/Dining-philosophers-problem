#include "Philosopher.hpp"

extern std::mutex g_lockprint;
extern bool ready;
extern std::vector<int> circleX;
extern std::vector<int> circleY;

Philosopher::Philosopher(int ID, Fork &l, Fork &r) : philID(ID), leftFork(l), rightFork(r), life(&Philosopher::dine, this)
{
}
Philosopher::~Philosopher()
{
    life.join();
}
const char *Philosopher::getName()
{
    std::string tmp = "Phil ";
    tmp = tmp + std::to_string(philID);
    return tmp.c_str();
}

void Philosopher::print(bool state)
{
    std::lock_guard<std::mutex> cout_lock(g_lockprint);
    //std::cout << philID << "  " << text << std ::endl;
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_RED);

    start_color();
    if (state == false)
    {
        attron(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
    }

    move(circleX[philID * 2], circleY[philID * 2]);
    printw(getName());
    attroff(COLOR_PAIR(1));
    refresh();
    move(0, 0);
}

void Philosopher::think()
{
    static thread_local std::uniform_int_distribution<> wait(1, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(wait(randomDevice) * 1000));

    print(0);
}

void Philosopher::eat()
{
    std::lock(leftFork.mutex, rightFork.mutex);

    std::lock_guard<std::mutex> left_lock(leftFork.mutex, std::adopt_lock);
    std::lock_guard<std::mutex> right_lock(rightFork.mutex, std::adopt_lock);

    print(1);

    static thread_local std::uniform_int_distribution<> dist(1, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(dist(randomDevice) * 1000));

    print(0);
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
