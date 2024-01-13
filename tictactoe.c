#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define PLAYER 'O'
#define OPPONENT 'X'
#define EMPTY '_'

//Global variable to declare board size
int bsize = 3;


//method to print the game board
void print_board(char board[bsize][bsize]){
	int i;
	for (i = 0; i < bsize; i++) {
		if(bsize==3){
			printf(" %c | %c | %c", board[i][0], board[i][1], board[i][2]);
		} 
		if(bsize==4){
			printf(" %c | %c | %c | %c ", board[i][0], board[i][1], board[i][2], board[i][3]);
		}
		
		if (i != (bsize-1)) {
			printf("\n---+");
			for(int i=0; i< bsize - 2; i++){
				printf("---+");
			}
			printf("---\n");
		}
	}
	printf("\n"); 

}


//method to check if any moves are left in the board
bool is_moves_left(char board[bsize][bsize])
{
    for (int i = 0; i < bsize; i++)
        for (int j = 0; j < bsize; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}




//method to check who the winner is or if it is a draw 
int evaluate(char board[bsize][bsize]){
		// Checking in the rows
		for(int rows = 0; rows < bsize; rows++){
			int p_count=0;
			int o_count=0;
			for(int cols = 0; cols < bsize; cols++){
				if(board[rows][cols] == PLAYER){
					p_count++;
				}
				if(board[rows][cols] == OPPONENT){
					o_count++;
				}
			}
			if(p_count == bsize){
				return 10;
			}
			else if(o_count == bsize){
				return -10;
			}
			
		}
		
		
		//Checking in the columns
		for(int cols = 0; cols < bsize; cols++){
			int p_count = 0;
			int o_count = 0;
			for(int rows = 0; rows < bsize; rows++){
				if(board[rows][cols] == PLAYER){
					p_count++;
				}
				if(board[rows][cols] == OPPONENT){
					o_count++;
				}
			}
			if(p_count == bsize){
				return 10;
			}
			else if(o_count == bsize){
				return -10;
			}
		}

		
		//Checking in the diagonals
		int	p_count=0;
		int o_count=0;
		for(int rows = 0, cols = 0; rows < bsize; rows++, cols++){
			if(board[rows][cols] == PLAYER){
				p_count++;
			}
			if(board[rows][cols] == OPPONENT){
				o_count++;
			}
		}
		
		if(p_count == bsize){
			return 10;
		}
		else if(o_count == bsize){
			return -10;
		}
		
		p_count=0;
		o_count=0;
		for(int rows = 0, cols = bsize-1; rows < bsize; rows++, cols--){
			if(board[rows][cols] == PLAYER){
				p_count++;
			}
			if(board[rows][cols] == OPPONENT){
				o_count++;
			}
		}
		if(p_count == bsize){
			return 10;
		}
		else if(o_count == bsize){
			return -10;
		}
	
	//draw
	return 0;
}



struct Move {
    int row, col;
};



//method that defines the minimax algorithm
int minimax(char board[bsize][bsize], int depth, bool max_flag){
	int score = evaluate(board);
	if (score == 10){
		return score - depth;
	}

	if(score == -10){
		return score + depth;
	} 

	if(is_moves_left(board) == false){
		return 0;
	}

	if(max_flag){
		int best =-1000;
		for (int i = 0; i < bsize; i++)
	    {
	        for (int j = 0; j < bsize; j++)
	        {
	            if (board[i][j] == '_')
	            {
	                board[i][j] = PLAYER;
	                int value = minimax(board, depth+1, !max_flag);
	                if(best > value){
	                	best = best;
	                } else {
	                	best = value;
	                }
	                board[i][j] = '_';
				}
			}
		}
		return best;		
	}

	else {
		int best = 1000;
		for (int i = 0; i < bsize; i++)
	    {
	        for (int j = 0; j < bsize; j++)
	        {
	            if (board[i][j]=='_')
	            {
	                board[i][j] = OPPONENT;
	                int value = minimax(board, depth+1, !max_flag);
	                if(best < value){
	                	best = best;
	                } else {
	                	best = value;
	                }
	                board[i][j] = '_';
				}
			}
		}
		return best;	
	}
}



//Method to find the best row and column to make the move
struct Move play_best_move(char board[bsize][bsize]){
	int bestval = -100;
	struct Move bestmove;
	bestmove.row = -1;
	bestmove.col = -1;
	int i,j;
	for (i = 0; i < bsize; i++){
		for(j = 0;j < bsize; j++){
			if(board[i][j] == '_'){
				board[i][j]=PLAYER;
				int moveVal = minimax(board, 0, false);
				board[i][j] = '_';
				if (moveVal > bestval)
                {
                  	bestmove.row = i;
                    bestmove.col = j;
                    bestval = moveVal;
                }
			}
		}
	}
	return bestmove;
}




//Method to check if board is empty
int empty(char board[bsize][bsize]){
	for(int i = 0; i < bsize; i++){
		for(int j = 0; j < bsize; j++){
			if(board[i][j] != EMPTY){
				return false;
			} 
		}
		
	}
	print_board(board);
	printf("O: 0 0\n");
	return true;
}




//Method to check if there is a winner or if the game is a draw
bool check_win(char board[bsize][bsize]){
	//rows
	for(int rows = 0; rows < bsize;  rows++){
		int p_count=0;
		int o_count=0;
		for(int cols = 0; cols < bsize; cols++){
			if(board[rows][cols]==PLAYER){
				p_count++;
			}
			if(board[rows][cols]==OPPONENT){
				o_count++;
			}
		}
		if(p_count == bsize){
			printf("O won the game!\n");
			return true;
		}
		else if(o_count == bsize){
			printf("X won the game!\n");
			return true;
		}
	}
	
	
	//columns
	for(int cols=0; cols < bsize; cols++){
		int p_count = 0;
		int o_count = 0;
		for(int rows = 0; rows < bsize; rows++){
			if(board[rows][cols]==PLAYER){
				p_count++;
			}
			if(board[rows][cols]==OPPONENT){
				o_count++;
			}
		}
		if(p_count == bsize){
			printf("O won the game!\n");
			return true;
		}
		else if(o_count == bsize){
			printf("X won the game!\n");
			return true;
		}
	}

	
	//diagonals
	int p_count = 0;
	int o_count = 0;

	for(int rows = 0, cols = 0; rows < bsize; rows++, cols++){
		if(board[rows][cols] == PLAYER){
			p_count++;
		}
		if(board[rows][cols] == OPPONENT){
			o_count++;
		}
	}
	if(p_count == bsize){
		printf("O won the game!\n");
		return true;
	}
	else if(o_count == bsize){
		printf("X won the game!\n");
		return true;
	}

	p_count=0;
	o_count=0;
	for(int rows = 0, cols = bsize-1; rows < bsize; rows++, cols--){
		if(board[rows][cols] == PLAYER){
			p_count++;
		}
		if(board[rows][cols] == OPPONENT){
			o_count++;
		}
	}
	if(p_count == bsize){
		printf("O won the game!\n");
		return true;
	}
	else if(o_count == bsize){
		printf("X won the game!\n");
		return true;
	}

	if(!is_moves_left(board)){
		printf("The game is a draw!\n");
		return true;
	}
	return false;
}





int main(int argc, char* argv[]){
	//Case 1: Output the optimal next move for that board
	if(argc > 9){
		int index=1;
		if(strcmp(argv[1], "-s")==0){
			 bsize = atoi(argv[2]);
			 index = 3; 
		}
		char board[bsize][bsize];
		
		for(int i = 0; i < bsize; i++){
			for(int j = 0; j < bsize; j++){
				board[i][j] = argv[index][0];
				index++;
			}
		}
		if (!empty(board)){
			struct Move move = play_best_move(board);
			print_board(board);
			printf("O: %d %d\n", move.row, move.col);
		} 	
	}


	//Case 2: Loop to play a full game (Human playing 'X', and Computer playing 'O')
	if(argc < 4){
		printf("************************\n");
		printf("Welcome to Tic Tac Toe!\n");
		if(argc==3 && strcmp(argv[1], "-s")==0){
			 bsize = atoi(argv[2]); 
		} 
		char board[bsize][bsize];
		
		for(int i = 0; i < bsize; i++){
			for(int j = 0; j < bsize; j++){
				board[i][j] = '_';
			}
		}
		
		while(!check_win(board)){
			int x_row;
			int x_col;
			printf("X Move: ");
			scanf("%d %d", &x_row, &x_col);
			board[x_row][x_col] = 'X';
			print_board(board);
			printf("\n");
			printf("******************\n\n");
			struct Move move = play_best_move(board);
			board[move.row][move.col] = 'O';
			printf("O Move: %d %d\n", move.row, move.col);
			print_board(board);
			printf("\n");
			printf("******************\n\n");
		}
		
	}
	
	return 0;
}
