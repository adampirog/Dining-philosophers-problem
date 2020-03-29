#include <iostream>
#include <math.h>
#include <ncurses.h>
#include "Fork.hpp"
#include "Philosopher.hpp"

bool ready = false;
std::mutex g_lockprint;
std::vector<int> circleX;
std::vector<int> circleY;
const int PI = 3.14159265359;
const int PHILOSOPHERS = 10;

//150x44
void drawCircle()
{
    int centerX = 22;
    int centerY = 75;
    int radius = 13;

    for (int degree = 0; degree < 360; degree += (360 / PHILOSOPHERS))
    {
        float radians = degree * PI / 180.0f;
        int x = radius * cos(radians) + centerX;
        int y = 2 * radius * sin(radians) + centerY;
        circleX.push_back(x);
        circleY.push_back(y);
    }
}

int main()
{

    initscr();

    drawCircle();
    std::cout << circleY.size() << std::endl;
    for (int i = 0; i < circleY.size(); i++)
    {
        move(circleX[i], circleY[i]);
        printw("ADAM");
        move(0, 0);
    }

    /*
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
     */

    getch();
    endwin();
}