#include<iostream>
#include<vector>
#include<ncurses.h>
#include<cstdlib>
#include<unistd.h>
#ifndef SNAKE_H
#define SNAKE_H

using namespace std;

// creats snake and food object
struct gamePc{ 					 
	gamePc();
	gamePc(int col, int row);
	int 	x,y;
};

class snakeClass{
	private:
		// game points
		int points;
		// delay in macroseconds
		int del; 
		// max height and width of terminal window
		int maxWidth, maxHeight;
		// indicates the current direction of the snake
		char direction;
		// indicates if the snake eats food and gets longer
		bool get;  
		// character symbols 
		char snakeChar,borderChar, foodChar;
		// food object		
		gamePc food;
		// snake object
		std::vector<gamePc> snake;
		// places food on screen
		void placeFood();
		// checks if snake collides with iteself or the walls
		bool collision();
		// gets character from user, up-down-left-right arrows
		void moveSnake();	
		// start menu
		void startMenu();

	public:
		// constructor
		snakeClass();
		// destructor
		~snakeClass();
		// game	
		void start();

};

#endif
