#include <iostream>
#include <iomanip>
#include "Fork.hpp"
#include "Philosopher.hpp"

bool ready = false;
std::mutex g_lockprint;

int main()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Dinner started!" << std::endl;

    {
        std::array<Fork, 5> forks;
        std::array<Philosopher, 5> philosophers{
            {
                {0, forks[0], forks[1]},
                {1, forks[1], forks[2]},
                {2, forks[2], forks[3]},
                {3, forks[3], forks[4]},
                {4, forks[4], forks[0]},
            }};

        ready = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        ready = false;
    }

    std::cout << "Dinner done!" << std::endl;
}