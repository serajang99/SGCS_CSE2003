#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define KEY_SPACE ' ' // not defined in ncurses.h
#define KEY_Enter 10
#define START_ROW 5
#define START_COL 5

int HEIGHT, WIDTH;

void saveGame(int **board, int players, int row, int col, int turn,char *filename){

	FILE *ifp;
	int i,j;
	ifp = fopen(filename,"w");
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			fprintf(ifp,"%c",board[i][j]);
		}
	}
	fprintf(ifp, " ");
	fprintf(ifp,"%d %d %d %d %d %d",row,col,turn,players, HEIGHT,WIDTH);
	fclose(ifp);
	/*
		Save current game with given name 
	*/
	// TODO 
}//save current game with given name

int** readSavedGame(int **board, int *players, int *row, int *col, int *turn, char *filename){
	
	FILE *ofp=NULL;
	int i,j;
	int res=0;
	int dx=0;
	char tmp[400];
	
	ofp = fopen(filename,"r");
	res = fscanf(ofp,"%s %d %d %d %d %d %d",tmp, row, col, turn, players, &HEIGHT, &WIDTH);
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			if(tmp[dx]=='O'||tmp[dx]=='X'||tmp[dx]=='Y')
				board[i][j]=tmp[dx];
			dx++;
		}
	}
	fclose(ofp);

	return board;

	/*
		Read the existing game
	*/
	// TODO 
}//read the existing game

void readSavedHW(char *filename){
	FILE *ofp;
	char tmp[400];
	int tmp1,tmp2,tmp3,tmp4;
	int res;
	ofp = fopen(filename,"r");
	res = fscanf(ofp,"%s %d %d %d %d %d %d",tmp,&tmp1,&tmp2,&tmp3,&tmp4,&HEIGHT,&WIDTH);
	fclose(ofp);
}//read the existing game

int** initBoard(int **board, int *row, int *col, int *turn, int load){
	board = (int**)malloc(sizeof(int*)*HEIGHT);
	for(int i=0; i<HEIGHT; i++){
		board[i] = (int*)malloc(sizeof(int)*WIDTH);
	}

	printf("%d %d\n", HEIGHT, WIDTH);
	board[0][0] = ACS_ULCORNER;//'┌'
	for (int i=1; i < WIDTH-1; i++)
		board[0][i] = ACS_TTEE;//'┬'
	board[0][WIDTH-1] = ACS_URCORNER; //'┐'

	for (int i=1; i<HEIGHT-1; i++){
		board[i][0] = ACS_LTEE; // '├'
		for (int j=1; j < WIDTH-1; j++)
			board[i][j] = ACS_PLUS; //'┼'
		board[i][WIDTH-1] = ACS_RTEE; //'┤'
	}

	board[HEIGHT-1][0] = ACS_LLCORNER; //'└'
	for (int i=1; i < WIDTH-1; i++)
		board[HEIGHT-1][i] = ACS_BTEE; //'┴'
	board[HEIGHT-1][WIDTH-1] = ACS_LRCORNER; // '┘'

	return board;
}//Initiating the board

void paintBoard(int **board, WINDOW *win, int row, int col){

	wmove(win,0,0);//cursor move to win 0,0
	int i,j;
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			waddch(win,board[i][j]);
		}
	}//painting the board
	wmove(win,row,col);//move cursor to row,col

}

void paintMenu(int players, int turn,char cturn,WINDOW *win,int row, int col){

	if(players==2){
	if(turn==1){
		cturn='O';
		turn=2;
	}
	else if(turn==2){
		cturn='X';
		turn=1;
	}
	}//when players=2, current turn change
	else if(players==3){
	if(turn==1){
		cturn='O';
		turn=2;
	}
	else if(turn==2){
		cturn='X';
		turn=3;
	}
	else if(turn==3){
		cturn='Y';
		turn=1;
	}
	}//when players=3, current turn change
	/*1player's stone is 'O'
	  2player's stone is 'X'
	  3player's stone is 'Y'*/
	mvprintw(HEIGHT+10,6,"Current Turn : %c",cturn);
	mvprintw(HEIGHT+11,6,"1. Press 1 to save");
	mvprintw(HEIGHT+12,6,"2. Exit without save");//painting the menu
	wmove(win,row,col);
}

int checkWin(int **board, int turn,int players){ // parameters and return type can be modified with any form. 

	int i,j;
	/*players=2 check omok*/
	if(players==2){
	for(i=0;i<HEIGHT;i++){
		for(j=2;j<WIDTH-2;j++){
			if(
			board[i][j-2]=='O'&&
			board[i][j-1]=='O'&&
			board[i][j]=='O'&&
			board[i][j+1]=='O'&&
			board[i][j+2]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i][j-2]=='X'&&
			board[i][j-1]=='X'&&
			board[i][j]=='X'&&
			board[i][j+1]=='X'&&
			board[i][j+2]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+1);
				return 1;
			}
		}
	}//width_omok_check when players=2

	for(j=0;j<WIDTH;j++){
		for(i=2;i<HEIGHT-2;i++){
			if(
			board[i-2][j]=='O'&&
			board[i-1][j]=='O'&&
			board[i][j]=='O'&&
			board[i+1][j]=='O'&&
			board[i+2][j]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i-2][j]=='X'&&
			board[i-1][j]=='X'&&
			board[i][j]=='X'&&
			board[i+1][j]=='X'&&
			board[i+2][j]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+1);
				return 1;
			}
		}
	}//height_omok_check when players=2

	for(i=2;i<HEIGHT-2;i++){
		for(j=2;j<WIDTH-2;j++){
			if(
			board[i-2][j-2]=='O'&&
			board[i-1][j-1]=='O'&&
			board[i][j]=='O'&&
			board[i+1][j+1]=='O'&&
			board[i+2][j+2]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i-2][j-2]=='X'&&
			board[i-1][j-1]=='X'&&
			board[i][j]=='X'&&
			board[i+1][j+1]=='X'&&
			board[i+2][j+2]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+1);
				return 1;
			}
			else if(
			board[i-2][j+2]=='O'&&
			board[i-1][j+1]=='O'&&
			board[i][j]=='O'&&
			board[i+1][j-1]=='O'&&
			board[i+2][j-2]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i-2][j+2]=='X'&&
			board[i-1][j+1]=='X'&&
			board[i][j]=='X'&&
			board[i+1][j-1]=='X'&&
			board[i+2][j-2]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+1);
				return 1;
			}

		}
	}
	}
	//diagonal_line_omok_check when players=2



	/*3players 4mok*/
	if(players==3){
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH-3;j++){
			if(
			board[i][j]=='O'&&
			board[i][j+1]=='O'&&
			board[i][j+2]=='O'&&
			board[i][j+3]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i][j]=='X'&&
			board[i][j+1]=='X'&&
			board[i][j+2]=='X'&&
			board[i][j+3]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}
			else if(
			board[i][j]=='Y'&&
			board[i][j+1]=='Y'&&
			board[i][j+2]=='Y'&&
			board[i][j+3]=='Y'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+2);
				return 1;
			}

		}
	}//width_4mok check when players=3
	
	for(j=0;j<WIDTH;j++){
		for(i=0;i<HEIGHT-3;i++){
			if(
			board[i][j]=='O'&&
			board[i+1][j]=='O'&&
			board[i+2][j]=='O'&&
			board[i+3][j]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i][j]=='X'&&
			board[i+1][j]=='X'&&
			board[i+2][j]=='X'&&
			board[i+3][j]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}
			else if(
			board[i][j]=='Y'&&
			board[i+1][j]=='Y'&&
			board[i+2][j]=='Y'&&
			board[i+3][j]=='Y'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+2);
				return 1;
			}

		}
	}//height_4mok check when players=3
	
	for(j=0;j<WIDTH-3;j++){
		for(i=0;i<HEIGHT-3;i++){
			if(
			board[i][j]=='O'&&
			board[i+1][j+1]=='O'&&
			board[i+2][j+2]=='O'&&
			board[i+3][j+3]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i][j]=='X'&&
			board[i+1][j+1]=='X'&&
			board[i+2][j+2]=='X'&&
			board[i+3][j+3]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}
			else if(
			board[i][j]=='Y'&&
			board[i+1][j+1]=='Y'&&
			board[i+2][j+2]=='Y'&&
			board[i+3][j+3]=='Y'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+2);
				return 1;
			}
		}
	}//diagonal_line 4mok check when players=3

	for(i=2;i<HEIGHT;i++){
		for(j=1;j<WIDTH;j++){
			if(
			board[i-2][j+2]=='O'&&
			board[i-1][j+1]=='O'&&
			board[i][j]=='O'&&
			board[i+1][j-1]=='O'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}

			else if(
			board[i-2][j+2]=='X'&&
			board[i-1][j+1]=='X'&&
			board[i][j]=='X'&&
			board[i+1][j-1]=='X'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn-1);
				return 1;
			}
			else if(
			board[i-2][j+2]=='Y'&&
			board[i-1][j+1]=='Y'&&
			board[i][j]=='Y'&&
			board[i+1][j-1]=='Y'
			){
				mvprintw(HEIGHT+9,6,"PLAYER%d WIN !! Press any button two times to terminate the program",turn+2);
				return 1;
			}
		}
	}//anti_diagonal_line 4mok check when players=3
	//if someone win return 1

	}
	return 0;//else return 0
	/*
		Check if the game is over. 
	*/
	// TODO
}

int Action(WINDOW *win, int **board, int keyin, int *row, int *col, int *turn, int players){

	char *filename;
	char file[100];
	filename = file;
	
	int check,tmp;
	
	switch(keyin){//according to keyin, following actions act

		case KEY_RIGHT : *col += 1;
				 wmove(win,*row,*col);//move cursor to 1 time right
				 if(*col>=WIDTH) *col-=1; //cursor cannot move to outside the board
				 break;

		case KEY_LEFT : *col -= 1;
				wmove(win,*row,*col);//move cursor to 1 time left
				if(*col<0) *col+=1;//cursor cannot move to outside the board
				break;
				
		case KEY_UP : *row -= 1;
			      wmove(win,*row,*col);//move cursor to 1 time up
			      if(*row<0) *row+=1;//cursor cannot move to outside the board
			      break;

		case KEY_DOWN: *row += 1;
			       wmove(win,*row,*col);//move cursor to 1 time down
			       if(*row>=HEIGHT) *row-=1;//cursor cannot move to outside the board
			       break;
		case KEY_SPACE:
		case KEY_Enter:
			       wmove(win,*row,*col);
			       if(players==2){
			       if(board[*row][*col]!='O' && board[*row][*col]!='X'){
			       		if (*turn==1){
				       		board[*row][*col]='O';
				       		*turn=2;
			       		}
			       		else if(*turn==2){
					        board[*row][*col]='X';
				       		*turn=1;
			       		}
					else *turn=*turn;
					mvprintw(HEIGHT+7,6,"\t\t\t\t\t\t\t");
			       }//when players=2, put the player1's stone 'O' and player2's stone 'X'and turn change
			       else if(board[*row][*col]=='O'||board[*row][*col]=='X'){
				      		mvprintw(HEIGHT+7,6,"STONE ALREADY THERE");
						break;//if you click the place stone already places, print "STONE ALREADY THERE"
			       }
			       }

			       else if(players==3){
			       if(board[*row][*col]!='O' && board[*row][*col]!='X' && board[*row][*col]!='Y'){
			       		if (*turn==1){
				       		board[*row][*col]='O';
				       		*turn=2;
			       		}
			       		else if(*turn==2){
					        board[*row][*col]='X';
				       		*turn=3;
			       		}
					else if(*turn==3){
						board[*row][*col]='Y';
						*turn=1;
					}
					else *turn=*turn;
					mvprintw(HEIGHT+7,6,"\t\t\t\t\t\t\t");
			       }//when players=3, put the player1's stone 'O', player2's stone 'X', and player3's stone 'Y' and turn change
			       else if(board[*row][*col]=='O'||board[*row][*col]=='X'||board[*row][*col]=='Y'){
				      		mvprintw(HEIGHT+7,6,"STONE ALREADY THERE");
				       		wmove(win,*row,*col);
				       		break;//if you click the place stone already places, print "STONE ALREADY THERE"
			       }
			       }
			       
			       refresh();
			       wrefresh(win);
			       
			       check = checkWin(board,*turn,players);//check win whenever we put the stone
			       refresh();
			       wrefresh(win);
			       break;
		case '1':
			       mvprintw(HEIGHT+7,6,"ENTER FILE NAME : ");
			       echo();
			       scanw("%s",filename);
			       noecho();
			       mvprintw(HEIGHT+7,6,"\t\t\t\t\t\t\t");//enter the filename(echo allows typing and noecho means not allow the typing)
			       saveGame(board,players,*row,*col,*turn,filename);
			       break;
			       /*menu 1 is save file -> if keyin is 1 enter the file name and save the game*/
			       
		case '2': 
			       return 2;
			       break;/*return 2*/

	}
	return check;
	/*
		following right after the keyboard input,
		perform a corresponding action. 
	*/
	// TODO 
}


void gameStart(WINDOW *win, int load, int players){
	int **board;
	int row = 0;
	int col = 0;
	int keyin;
	wmove(win, row, col); 
	int turn=1;
	char cturn;
	int tmp,check;

	board = initBoard(board, &row, &col, &turn, load); // Initiating the board
	if(load =='n'){
		row=0;
		col=0;
		turn = 1;
		board = initBoard(board, &row, &col, &turn, load);
	}

	while(1){
		/* 
			This While loop constantly loops in order to 
			draw every frame of the WINDOW.
		*/

		// TODO LIST
		paintBoard(board,win,row,col); 
		refresh();
		wrefresh(win);// PAINT THE BOARD
		paintMenu(players,turn,cturn,win,row,col);
		refresh();
		wrefresh(win);
		keyin = getch();
		
		// PAINT MENU
		// MOVE CURSOR TO THE LAST POINT 
		// GET KEYBOARD INPUT
		
		checkWin(board,turn,players);
		refresh();
		wrefresh(win);
		
		if(check == 1){
			tmp=getch();
			break;
		}
		//press any key->exit the game
		
		check = Action(win,board,keyin,&row,&col,&turn,players);
		
		if(check == 2){
			mvprintw(HEIGHT+8,6,"Are you sure to exit the game?[y/n]");
			tmp=getch();
			if(tmp=='y') break;
			else if(tmp=='n'){
				mvprintw(HEIGHT+8,6,"\t\t\t\t\t\t");
			}
		}//in func Action return=2 -> check=2

		refresh();
		wrefresh(win);// DO ACTION ACCORDING TO THAT INPUT
		  // update WINDOW 
	}

	return;
}

int main(){
	char load;
	int players;
	
	char *filename;
	char file[100];

	int **board, row, col, turn;

	filename = file;
	
	printf("Want to load the game?[y/n]: ");
	scanf("%c",&load);

	if(load=='n'){
		printf("Enter the HEIGHT of the board : ");
		scanf("%d",&HEIGHT);
		printf("Enter the WIDTH of the board : ");
		scanf("%d",&WIDTH);
		printf("Enter the number of players[2/3] : ");
		scanf("%d",&players);
	}//if you dont want to load the game and want to get a new game, ask the options of the game
	initscr();//initiate the standard screen
	noecho();
	if(load=='y'){
		printw("PLEASE ENTER THE FILE NAME : ");
		echo();
		getstr(file);
		noecho();
		mvprintw(0,0,"\t\t\t\t\t\t");
		refresh();
		readSavedHW(filename);
		board = initBoard(board,&row,&col,&turn,load);	
		board = readSavedGame(board,&players,&row,&col,&turn,filename);
	}//if you want to load the game, enter the file name and read the file
	
	WINDOW *win=newwin(HEIGHT,WIDTH,5,5);//make the new window(define the window) 

	keypad(stdscr,TRUE);
	keypad(win,TRUE);//if bf is TRUE, you can use the keypad(the keyboard of the computer)
			//to use the arrow keys and etc. you need it.

	// TODO 
	/*
		Prompts to ask options of the game
	*/

	// TODO LIST
	  // define a window
	  // terminate the window safely so that the terminal settings can be restored safely as well. 

	gameStart(win,load,players);

	endwin();//end the window
	return 0;
}

