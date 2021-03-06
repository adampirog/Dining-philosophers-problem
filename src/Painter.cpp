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
	init_colors();
	noecho();
	curs_set(0);
}

Painter::~Painter()
{
	endwin();
}

void Painter::init_colors()
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, COLOR_WHITE, COLOR_CYAN);
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
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
		//timeout(125);
	}

	for (int i = 0; i < nPhils; i++)
		philosopher[i]->setAlive(false);

	endwin();
}

void Painter::drawFrame()
{

	move(1, 37);
	printw("Filozofowie");
	move(1, 66);
	printw("Widelce");

	for (int i = 0; i < nPhils; i++)
	{

		move(3 + i * 4, 27);
		addch(i + '0');

		attron(COLOR_PAIR((i % 6) + 1));
		move(3 + i * 4, 30);
		addch('[');
		move(3 + i * 4, 51);
		addch(']');
		attroff(COLOR_PAIR((i % 6) + 1));

		attron(COLOR_PAIR(7));
		move(5 + i * 4, 59);
		addch('W');
		addch(i + '0');
		printw(" Wolny");
		attroff(COLOR_PAIR(7));
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
		attron(COLOR_PAIR((i % 6) + 1));
		int progress = philosopher[i]->getProgress();
		int state = philosopher[i]->getState();
		double timer = philosopher[i]->getTimer();
		char c;

		if (state == 0)
			c = '#';
		else
			c = '+';

		if (state == 2)
		{
			move(3 + i * 4, 31);
			printw("--------Czeka-------");
			move(3 + i * 4, 52);
			printw("%1.2f%s", 0.00, "s");
		}
		else
		{
			for (int j = 0; j < 20; j++)
			{
				move(3 + i * 4, 31 + j);

				if (progress > j)
				{
					addch(c);
				}
				else
				{
					addch(' ');
				}
				move(3 + i * 4, 52);
				double timeLeft = ((21 - progress) * timer) / 1000000;
				printw("%1.2f%s", timeLeft, "s");
			}
		}
		attroff(COLOR_PAIR((i % 6) + 1));
	}
}

void Painter::drawForks()
{
	for (int i = 0; i < nPhils; i++)
	{
		if (fork[i]->isBusy())
		{
			int philID = fork[i]->getPhilID();
			attron(COLOR_PAIR((philID % 6) + 1));
			move(5 + i * 4, 59);
			addch('W');
			addch(i + '0');
			printw("  zabrany przez: ");
			addch('F');
			addch(philID + '0');
			attroff(COLOR_PAIR((philID % 6) + 1));
		}
		else
		{
			attron(COLOR_PAIR(7));
			move(5 + i * 4, 59);
			addch('W');
			addch(i + '0');
			printw(" Wolny             ");
			attroff(COLOR_PAIR(7));
		}
	}
}
