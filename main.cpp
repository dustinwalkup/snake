#include "snake.h"

int main()
{
	// bool menu = true;
	// while(menu){
	// 	initscr();
	// 	noecho();
	// 	cbreak();
	// 	curs_set(0);
	// 	// char snakeChar = 'x';
	// 	int yMax, xMax;
	// 	getmaxyx (stdscr, yMax, xMax);


	// 	WINDOW* menuWin = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
	// 	string choices[2] = {"Start Game", "Exit Game"};
	// 	int choice;
	// 	int highlight = 0;
	// 	keypad(menuWin, true);
	// 	while(1)
	// 	{
	// 		for (int idx = 0; idx < 2; idx++)
	// 		{
	// 			if(idx == highlight)
	// 				wattron(menuWin, A_REVERSE);
	// 			mvwprintw(menuWin, idx+1, 1, choices[idx].c_str());
	// 			wattroff(menuWin, A_REVERSE);
	// 		}

	// 		choice = wgetch(menuWin);

	// 		switch(choice)
	// 		{
	// 			case KEY_UP:
	// 				highlight--;
	// 				if(highlight == -1)
	// 					highlight = 0;
	// 				break;
	// 			case KEY_DOWN:
	// 				highlight++;
	// 				if(highlight == 2)
	// 					highlight = 1;
	// 				break;
	// 			default:
	// 				break;
	// 		}

	// 		if (choice == 10)
	// 			break;
	// 	}	


	// 	menu = false


	// 	//box(menuWin, 0,0);
	// 	// std::vector<gamePc> snake;
	// 	// for (int idx=0; idx<5;idx++)
	// 	// 	snake.push_back(gamePc(xMax/4+idx,yMax/4-1));	

	// 	// for(int idx = 0; idx < snake.size(); idx++)
	// 	// {
	// 	// 	move(snake[idx].y, snake[idx].x);
	// 	// 	addch(snakeChar);
	// 	// }
	// 	refresh();
	// 	wrefresh(menuWin); 
	// 	getch();
	// 	endwin();
	// }	
	snakeClass s;
	s.start();
	return 0;
}