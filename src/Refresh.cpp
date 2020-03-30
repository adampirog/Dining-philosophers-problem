#include "Refresh.h"
#include <cstdlib>
#include "ncurses.h"
#include <thread>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;


Refresh::Refresh(int n, Philosopher** philosopher, Fork** fork){
	this->n = n;
	this->philosopher = philosopher;
	this->fork = fork;

	initscr();
	noecho();
	curs_set(0);
	init();
}

Refresh::~Refresh(){
	endwin();
}

void Refresh::init(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

	//bkgd(COLOR_PAIR(1));
}

void Refresh::draw(){
	int c;
	nodelay(stdscr, TRUE);


	while((c = getch()) != 27){
		drawFrame();
		drawPhilosophers();
		drawPhilosophersDetails();
		drawForks();

		refresh();
		timeout(125);
	}

	for(int i = 0; i < 5; i++)
		philosopher[i]->setAlive(false);

	endwin();
}

void Refresh::drawFrame(){
	move(0, 0);
	printw("Wizualizacja:");

	for(int i = 0; i < 23; i++){
		move(i, 20);
		addch('|');
		if(i < 21){
			move(10, i);
			addch('-');
		}
	}

	move(0, 21);
	printw("Filozofowie:");

	for(int i = 0; i < 5; i++){
		move(3 + i * 3, 21);
		addch(i + 48);

		move(2 + i * 3, 24);
		printw("----------------------");
		move(4 + i * 3, 24);
		printw("----------------------");
		move(3 + i * 3, 24);
		addch('|');
		move(3 + i * 3, 45);
		addch('|');
	}

	move(11, 0);
	printw("Legenda:");
	move(13, 0);
	printw("'-', '/', '\\' - rece");
	move(14, 0);
	printw("'O' - filozofowie");
	move(15, 0);
	printw("'Y' - widelce");
	move(16, 0);
	printw("'+' - jedzenie");
	move(17, 0);
	printw("'z' - rozmyslanie");
	move(19, 0);
	printw("Filozofowie sa ");
	move(20 ,0);
	printw("numerowani wedlug");
	move(21, 0);
	printw("wskazowek zegara");
	move(22, 0);
	printw("liczac od godziny 12");
}

void Refresh::drawPhilosophers(){
	for (int i = 0; i < n; i++){
		int state = philosopher[i]->getState();
		int id = i;
		int left;
		int right;

		if(state == 0){
			left = 0;
			right = 0;
		}
		else if(state == 1){
			left = 2;
			right = 2;
		}
		else if(state == 2){
			left = 1;
			right = 1;
		}
		else if(state == 3){
			left = 1;
			right = 2;
		}
		else {
			left = 2;
			right = 1;
		}

		int philosophersSeatsX[] = {10, 15, 13, 7, 5};
		int philosophersSeatsY[] = {2,  4 , 7, 7, 4};

		char philosophersLeftHandsView[] = {'\\', '-', '\\', '\\', '-'};
		int philosophersLeftHandsX[] = {11, 15, 12, 6, 5};
		int philosophersLeftHandsY[] = {2,  5,  7, 7, 3};

		int philosophersRightHandsX[] = {9, 15, 14, 8, 5};
		int philosophersRightHandsY[] = {2 , 3 , 7, 7, 5};
		char philosophersRightHandsView[] = {'/', '-', '/', '/', '-'};

		move(philosophersSeatsY[id], philosophersSeatsX[id]);
		addch('O');

		 //0 nie ma, 1 czeka, 2 ma
		 move(philosophersLeftHandsY[id], philosophersLeftHandsX[id]);
		 if(left == 0)
		 	addch(' ');
		 else if(left == 1)
		 	addch(philosophersLeftHandsView[id]);
		 else
		 	addch('Y');

		 move(philosophersRightHandsY[id], philosophersRightHandsX[id]);
		 if(right == 0)
		 	addch(' ');
		 else if(right == 1)
		 	addch(philosophersRightHandsView[id]);
		 else
		 	addch('Y');
	}
}

void Refresh::drawPhilosophersDetails(){
	for(int i = 0; i < 5; i++){
		int progress = philosopher[i]->getProgress();
		int state = philosopher[i]->getState();
		char c;

		if(state == 0)
			c = 'z';
		else
			c = '+';


		if(state == 2){
			move(3 + i * 3, 25);
			printw("Czeka na widelce   ");
		}
		else{
			for(int j = 0; j < 20; j++){
				move(3 + i * 3, 25 + j);

				if(progress > j)
					addch(c);
				else
					addch(' ');
			}
		}
	}
}

void Refresh::drawForks(){
	int philosophersLeftHandsX[] = {11, 15, 12, 6, 5};
	int philosophersLeftHandsY[] = {2,  5,  7, 7, 3};

	int philosophersRightHandsX[] = {9, 15, 14, 8, 5};
	int philosophersRightHandsY[] = {2 , 3 , 7, 7, 5};

	int forkX[] = {13, 13, 10, 7, 7};
	int forkY[] = {3, 5, 6, 5, 3};


	for(int i = 0; i < 5; i++){
		if(fork[i]->isOccupied()){
			int philId = fork[i]->getPhilisopherId();
			int forkId = fork[i]->getId();

			move(forkY[i], forkX[i]);
			addch(' ');
			
			if(philId == forkId)
				move(philosophersLeftHandsY[philId], philosophersLeftHandsX[philId]);
			else
				move(philosophersRightHandsY[philId], philosophersRightHandsX[philId]);
			addch('Y');
		}
		else{
			move(forkY[i], forkX[i]);
			addch('Y');
		}
	}
}