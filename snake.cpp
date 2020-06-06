#include "snake.h"

/*
TODO LIST

-make a menu 
-toplist 
-colors

*/


gamePc::gamePc()
{
	x = 0;
	y = 0;
}

gamePc::gamePc(int col, int row)
{
	x = col;
	y = row;
}

snakeClass::snakeClass()
{
	initscr();								// clear and initialize terminal screen
	nodelay(stdscr,true);   				// getch will not wait for the user to press a key
	keypad(stdscr,true);					// initialize keyboard so we can use arrow keys
	noecho();								// does not display pressed characters on screen
	curs_set(0);							// remove cursor
	getmaxyx(stdscr,maxHeight,maxWidth); 	// get maxHeight and maxWidth of screen

	// intialize class variables

	snakeChar 	= 'x';
	borderChar 	= (char)219;
	foodChar 	= '*';
	food.x 		= 0;
	food.y 		= 0;
	
	for (int idx=0; idx<5;idx++)
		snake.push_back(gamePc(40+idx,10));
	
	points 		= 0;
	del 		= 110000; 					// delay in macroseconds
	get 		= false;
	direction 	= 'l';
	
	srand(time(NULL));
	
	placeFood();
	
	// game board
	// top border
	for(int idx=0; idx<maxWidth-1;idx++)
	{
		move(0,idx);                       // move function moves cursor to y,x position     
		addch(borderChar);
	}
	// bottom border
	for(int idx=0; idx<maxWidth-1;idx++)
	{
		move(maxHeight-2,idx);
		addch(borderChar);
	}
	// left border
	for(int idx=0; idx<maxHeight-1;idx++)
	{
		move(idx,0);
		addch(borderChar);
	}
	// right border
	for(int idx=0; idx<maxHeight-1;idx++)
	{
		move(idx,maxWidth-2);
		addch(borderChar);
	}

	// draw the snake
	for(int idx = 0; idx < snake.size(); idx++)
	{
		move(snake[idx].y, snake[idx].x);
		addch(snakeChar);
	}

	// print score
	move(maxHeight-1,0);
	printw("%d", points);

	move(food.y, food.x);
	addch(foodChar);
	refresh();
}											

snakeClass::~snakeClass()
{
	nodelay(stdscr,false);
	getch();
	endwin();
}

void snakeClass::placeFood()
{
	while(1)
	{
		int tmpx=rand() % maxWidth + 1;
		int tmpy=rand() % maxHeight + 1;
		for(int idx = 0; idx < snake.size(); idx++)
			if(snake[idx].x == tmpx && snake[idx].y == tmpy)
				continue;
		if(tmpx >= maxWidth-2 || tmpy >= maxHeight-3)
			continue;		
		food.x = tmpx;
		food.y = tmpy;
		break;
	}	
	move(food.y,food.x);
	addch(foodChar);
	refresh();
}

bool snakeClass::collision()
{
	if(snake[0].x == 0 || snake[0].x == maxWidth-1 || snake[0].y == 0 || snake[0].y == maxHeight - 2 )
		return true;

	for(int idx = 2; idx < snake.size(); idx++)
		if(snake[0].x == snake[idx].x && snake[idx].y == snake[0].y)
			return true;

	if(snake[0].x == food.x && snake[0].y == food.y)
	{
		get = true;
		placeFood();
		points+=10;
		move(maxHeight-1,0);
		printw("%d", points);
		if(points % 100 == 0)
			del-=10000;
	}else
		get = false;
	return false;
}

void snakeClass::moveSnake()
{
	int temp = getch();
	switch(temp)
	{
		case KEY_LEFT:
			if(direction != 'r')
				direction = 'l';
			break;
		case KEY_UP:
			if(direction != 'd')
				direction = 'u';
			break;
		case KEY_DOWN:
			if(direction != 'u')
				direction = 'd';
			break;
		case KEY_RIGHT:
			if(direction != 'l')
				direction = 'r';
			break;
		case KEY_BACKSPACE:
			direction = 'q';
			break;	
	}
	if(!get)
	{
		move(snake[snake.size()-1].y,snake[snake.size()-1].x);
		addch(' ');
		refresh();
		snake.pop_back();
	}
	if(direction == 'l')
		snake.insert(snake.begin(),gamePc(snake[0].x-1, snake[0].y));
	else if(direction == 'r')
		snake.insert(snake.begin(),gamePc(snake[0].x+1, snake[0].y));
	else if(direction == 'd')
		snake.insert(snake.begin(),gamePc(snake[0].x, snake[0].y+1));
	else if(direction == 'u')
		snake.insert(snake.begin(),gamePc(snake[0].x, snake[0].y-1));
	move(snake[0].y, snake[0].x);
	addch(snakeChar);
	refresh();
}

void snakeClass::start()
{
	bool menu = true;
	int yMax, xMax, yWindow, xWindow;
	getmaxyx (stdscr, yMax, xMax);
	string choices[2] = {"Start Game", "Exit Game"};
	int choice;
	int highlight = 0;


	while(menu)
	{
		WINDOW* menuWin = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
		keypad(menuWin, true);
		getmaxyx(menuWin, yWindow, xWindow);
		box(menuWin,0,0);
		mvwprintw(menuWin, 2, xWindow/2 -9, "Welcome to Snake!");
		wrefresh(menuWin);
		while(1)
		{
			for (int idx = 0; idx < 2; idx++)
			{
				if(idx == highlight)
					wattron(menuWin, A_REVERSE);
					mvwprintw(menuWin, yWindow/2+idx, xWindow/2-5, choices[idx].c_str());
					wattroff(menuWin, A_REVERSE);
			}

			choice = wgetch(menuWin);

			switch(choice)
			{
				case KEY_UP:
					highlight--;
					if(highlight == -1)
						highlight = 0;
					break;
				case KEY_DOWN:
					highlight++;
					if(highlight == 2)
						highlight = 1;
					break;
				default:
					break;
			}

			if (choice == 10)
				break;
		}	

		menu = false;	
		wclear(menuWin);
		wrefresh(menuWin);
		refresh();
 	}	
		if(highlight == 0)
		{
			while(1)
			{
				refresh();
				if(collision())
				{
					move((maxWidth/2)-4, maxHeight/2);
					printw("game over");
					break;
				}
		
				moveSnake();
				if(direction == 'q')
					break;
				usleep(del);
			}	
		}
		clear();
		refresh();

}