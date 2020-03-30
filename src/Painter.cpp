#include "Painter.h"
#include "ncurses.h"

using namespace std;
extern int PHILOSOPHERS;

Painter::Painter(int nPhils, Philosopher **philosopher, Fork **fork)
{
	this->nPhils = nPhils;
	this->philosopher = philosopher;
	this->fork = fork;

	initscr();
	noecho();
	curs_set(0);
	init();
}

Painter::~Painter()
{
	endwin();
}

void Painter::init()
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);

	//bkgd(COLOR_PAIR(1));
}

void Painter::draw()
{
	int c;
	nodelay(stdscr, TRUE);

	while ((c = getch()) != 27)
	{
		drawFrame();
		drawPhilosophers();
		drawForks();

		refresh();
		timeout(125);
	}

	for (int i = 0; i < nPhils; i++)
		philosopher[i]->setAlive(false);

	endwin();
}

void Painter::drawFrame()
{

	move(1, 15);
	printw("Filozofowie:");
	move(1, 50);
	printw("Widelce:");

	for (int i = 0; i < nPhils; i++)
	{
		move(3 + i * 4, 27);
		addch(i + '0');

		move(3 + i * 4, 30);
		addch('[');
		move(3 + i * 4, 51);
		addch(']');

		move(5 + i * 4, 53);
		addch('W');
		addch(i + '0');
		printw(" Wolny");
	}

	move(8, 0);
	printw("'+' - jedzenie");
	move(9, 0);
	printw("'#' - filozofowanie");
}

void Painter::drawPhilosophers()
{
	for (int i = 0; i < nPhils; i++)
	{
		int progress = philosopher[i]->getProgress();
		int state = philosopher[i]->getState();
		char c;

		if (state == 0)
			c = '#';
		else
			c = '+';

		if (state == 2)
		{
			move(3 + i * 4, 31);
			printw("--------Czeka-------");
		}
		else
		{
			for (int j = 0; j < 20; j++)
			{
				move(3 + i * 4, 31 + j);

				if (progress > j)
					addch(c);
				else
					addch(' ');
			}
		}
	}
}

void Painter::drawForks()
{
	for (int i = 0; i < nPhils; i++)
	{
		if (fork[i]->isBusy())
		{
			int philID = fork[i]->getPhilID();
			move(5 + i * 4, 53);
			addch('W');
			addch(i + '0');
			printw("  zabrany przez: ");
			addch('F');
			addch(philID + '0');
		}
		else
		{
			move(5 + i * 4, 53);
			addch('W');
			addch(i + '0');
			printw(" Wolny             ");
		}
	}
}
