#include "game.h"


/*Name: Emily Xu
	partners : ehaynes2, ufacio2
	Introduction: there are a total of 8 functions needed to be implemented for this MP.
	The make_game uses the arguments given to it and sets them appropriately to the members inside the struct. With the pointer given to us, we will use that pointer and the "->" to access the members in 
	the struct that the pointer contains. We will also initialize the score to 0 and all the cells to -1 to denote that it is a clean slate.
	The remake_game function does the same thing as make_game but we are given a pointer value that points to the structure we are modifying. It will set the new rows and columns given to it in its argument
	to the members. 
	The get_cell function gives the address of a cell denoted by the coordinates [row][col]. It will first check to see if the bounds are valid, and then return the address of it
	The code for move_w, move_a, move_s, and move_d are all adapted/stemed from the algorithm/pseudocode provided in lab8
	discussion section. Depending on what direction the game is moving in, it will compare different cells with a current
	cell that we are on. In all of the move functions, it is comprised of two for loops, one to loop through either the rows first or columns first. Then, it will set a compare cell and then get a current
	cell. The program will check the current cell with the cell at the compare cell. First, it will see if these two cells have the same value. If so, they will combine them, and then adjust the coordinates
	so that we will check the next cells in the line. For example, if we are checking move_a, we will check row by row, and then column by column with the first compare cell being the leftmost one. Then
	we will check as it goes to the right. This will be reversed for move_d. For move_w, it'll loop through the columns as an outer loop and the row as an inner loop. It will start with the upper most row
	work down the rows. For move_s, it'll compare with the bottom-most row and work its way up. 
	legal move check looks looks to see if there are any empty cells left or any cells with the same value as it right above, below, to the left or to the right of the current cell. If any of these are true,
	the game can still continue. It does this by looping through the whole array and if it finds any of the above conditions to be true, it will return 1. Else, it will return 0, meaning no moves can be 		made.
 */

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions. */

{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows; //set rows
    mygame->cols = cols; //set the columns from argument
    mygame->score = 0; //init score to 0
    int i;
    for (i = 0; i < rows*cols; i++) //loop through all the cells and init to -1 (empty)
    {
	mygame->cells[i] = -1;
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;		//*_cur_game_ptr is the address of the struct. New rows are now initialized from argument to its correct member
	(*_cur_game_ptr)->cols = new_cols;		//new columns are initialized
	(*_cur_game_ptr)->score = 0;			//score is init to 0
	int i;
	for (i = 0; i < new_rows*new_cols; i++)		//loop through all the cells in the game and set them to -1 (empty)
	{
		(*_cur_game_ptr)->cells[i] = -1;
	}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
//pointer to the struct game is called cur_game
{
    //YOUR CODE STARTS HERE 
	if (row < (cur_game->rows) && row >= 0 && col >= 0  && col < (cur_game->cols))  //check to see if coordinates are in bounds
	{
		return ((cur_game->cells) + (row*(cur_game->cols) + col));  //after finding the offset based on current row and col and adding it to the first element of cell, return the address of target cell
	}	
    return NULL;
}


int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
int moveCOL, moveROW, compare, valid = 0;
for (moveCOL = 0; moveCOL < cur_game->cols; moveCOL++) //loop through columns
{ 
	compare = 0;					//init compare coordinates									
	for (moveROW = 1; moveROW < cur_game->rows;moveROW++)		//loop through rows							
	{
		if ( *(get_cell(cur_game, moveROW, moveCOL)) != -1)//check if current cell is not empty								
		{
			if ( *(get_cell(cur_game, compare, moveCOL)) != -1)	//check if current cell is not empty						
			{													
				if ( *(get_cell(cur_game, moveROW, moveCOL)) == *(get_cell(cur_game, compare, moveCOL))) //check if the two cells have the same value
				{												
					valid = 1; //denote that tiles slide
					*(get_cell(cur_game, compare, moveCOL)) *= 2;	//combine cells at compare 					
					*(get_cell(cur_game, moveROW, moveCOL)) = -1;	//empty cell at current place value					
					cur_game->score += *(get_cell(cur_game, compare, moveCOL)); //update score				
					compare++;						//update coordinates	 				
				}
				else												
				{	
					while (*(get_cell(cur_game, compare, moveCOL)) != -1 && compare < moveROW)	//look at move_s for more indepth comments on this section. This is the same part
																//move_s	
					{
						compare++;
					}
					if (compare<moveROW)
                                        {       valid = 1;
                                                *(get_cell(cur_game, compare, moveCOL)) = *(get_cell(cur_game, moveROW, moveCOL)); 
                                                *(get_cell(cur_game, moveROW, moveCOL)) = -1;                                           
                                        }
				}		
			
			}
			else
                        	{
					 valid = 1;
                                         *(get_cell(cur_game, compare, moveCOL)) = *(get_cell(cur_game, moveROW, moveCOL)); 
                                         *(get_cell(cur_game, moveROW, moveCOL)) = -1;                                          
                                }
		}
	}
}
if (!valid)
{
	return 0;
}
return 1;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
int moveCOL, moveROW, compare, valid = 0;			//init variables
for (moveCOL = 0; moveCOL < cur_game->cols; moveCOL++)
{ 
	compare = (cur_game->rows) - 1;							//set one of the coords for the compare cell we are using							
	for (moveROW = compare - 1; moveROW >= 0;moveROW--)			//move from the rows from right to left						
	{
		if ( *(get_cell(cur_game, moveROW, moveCOL)) != -1)		//check if current cell is not empty						
		{
			if ( *(get_cell(cur_game, compare, moveCOL)) != -1)		//check if our compare cell is not empty					
			{													
				if ( *(get_cell(cur_game, moveROW, moveCOL)) == *(get_cell(cur_game, compare, moveCOL))) //two cells we are comparing are equal in value
				{												
					valid = 1;	//tiles were moved in this turn
					*(get_cell(cur_game, compare, moveCOL)) *= 2;	//combine the cells at the location of the compare cell					
					*(get_cell(cur_game, moveROW, moveCOL)) = -1;						//make current cell empty
					cur_game->score += *(get_cell(cur_game, compare, moveCOL));				//update score with combined cell value
					compare--;							 				//update coord or compare cell to not combine twice
				}
				else	//cells don't have the same value											
				{	
					while (*(get_cell(cur_game, compare, moveCOL)) != -1 && compare > moveROW) //move compare cell until it is in an empty space or until it is at the current cell		
					{
						compare--; //this updates where we move
					}
					if (compare>moveROW) //check to see if we are not past the current cell
                                        {       valid = 1;
                                                *(get_cell(cur_game, compare, moveCOL)) = *(get_cell(cur_game, moveROW, moveCOL)); //move current cell to where compare is
                                                *(get_cell(cur_game, moveROW, moveCOL)) = -1;                    //empty out current cell                       
                                        }
				}		
			
			}
			else //compare cell spot is empty
                        	{
					 valid = 1; //signify we moved tiles
                                         *(get_cell(cur_game, compare, moveCOL)) = *(get_cell(cur_game, moveROW, moveCOL)); //new value is at compare cell location
                                         *(get_cell(cur_game, moveROW, moveCOL)) = -1;                                   //empty cell now        
                                }
		}
	}
}
if (!valid)
{
	return 0;
}
return 1;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int moveCOL, moveROW, compare, valid = 0;					//initialize variables. Valid = 1 if the game slides
for (moveROW = 0; moveROW < cur_game->rows; moveROW++)				//loop through the rows
{ 
	compare = 0;								//set the coordinate of the first value we will compare to whatever current cell/tile we are						
	for (moveCOL = 1; moveCOL < cur_game->cols;moveCOL++)			//loop through the columns. How it moves is through the columns depends on the direction we are moving in						
	{
		if ( *(get_cell(cur_game, moveROW, moveCOL)) != -1)		//check to see if current cell is not empty						
		{
			if ( *(get_cell(cur_game, moveROW, compare)) != -1)	//check to see if the cell we are comparing to is not empty						 
			{													
				if ( *(get_cell(cur_game, moveROW, moveCOL)) == *(get_cell(cur_game, moveROW, compare))) //check to see if comparing cell and current cell have the same value
				{												
					valid = 1;									//tiles have combined, a valid move was made --> set valid to 1
					*(get_cell(cur_game, moveROW, compare)) *= 2;					//combine the tiles at the position the "compare" tile is at	
					*(get_cell(cur_game, moveROW, moveCOL)) = -1;					//make current cell empty	
					cur_game->score += *(get_cell(cur_game, moveROW, compare));			//update the coordinates of the compare tile so that we do not accidentally combine it	
					compare++;							 				
				}
				else			//two cells are not the same									
				{	
					while (*(get_cell(cur_game, moveROW, compare)) != -1 && compare < moveCOL)	//check to see if the comparing cell is empty and also at a position not past the current cell	
					{
						compare++;	//move the location of our compare cell until either it is at the location of our current cell or until it finds 
					}
					if (compare<moveCOL)		//if an empty cell was found and it is not past the current cell, move tiles
                                        {       valid = 1;	//this turn moved tiles
                                                *(get_cell(cur_game, moveROW, compare)) = *(get_cell(cur_game, moveROW, moveCOL)); //our current tiles moves to the empty space at the compare cell
                                                *(get_cell(cur_game, moveROW, moveCOL)) = -1;                       //current cell is now empty                  
                                        }
				}		
			
			}
			else
                        	{
					 valid = 1;
                                         *(get_cell(cur_game, moveROW, compare)) = *(get_cell(cur_game, moveROW, moveCOL));
                                         *(get_cell(cur_game, moveROW, moveCOL)) = -1;                                      
                                }
		}
	}
}
if (!valid) //if pressing this key doesn't change anything, return a 0
{
	return 0;
}
return 1; //pressing this key moved tiles
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

    int moveCOL, moveROW, compare, valid = 0;					//initialize variables. Valid = 1 if the game slides
for (moveROW = 0; moveROW < cur_game->rows; moveROW++) 				//loop through the rows
{ 
	compare = (cur_game->cols) - 1;						//set the coordinate of the first value we will compare to whatever current cell/tile we are one					
	for (moveCOL = compare - 1; moveCOL >= 0 ;moveCOL--)			//loop through the columns. How it moves is through the columns depends on the direction we are moving in
	{
		if ( *(get_cell(cur_game, moveROW, moveCOL)) != -1)		//check to see if current cell is not empty						
		{
			if ( *(get_cell(cur_game, moveROW, compare)) != -1)	//check to see if the cell we are comparing to is not empty						
			{													
				if ( *(get_cell(cur_game, moveROW, moveCOL)) == *(get_cell(cur_game, moveROW, compare))) //check to see if comparing cell and current cell have the same value
				{												
					valid = 1;									//tiles have combined, a valid move was made --> set valid to 1
					*(get_cell(cur_game,moveROW, compare)) *= 2;					//combine the tiles at the position the "compare" tile is at
					*(get_cell(cur_game, moveROW, moveCOL)) = -1;					//make current cell empty
					cur_game->score += *(get_cell(cur_game, moveROW, compare));			//update score with the value of the combined tile
					compare--;							 		//update the coordinates of the compare tile so that we do not accidentally combine it again
				}
				else						//two cells are not the same												
				{	
					while (*(get_cell(cur_game, moveROW, compare)) != -1 && compare > moveCOL)	//check to see if the comparing cell is empty and also at a position not past the current cell
					{
						compare--;								//move the location of our compare cell until either it is at the location of our current cell or until it finds 
				
					}
					if (compare>moveCOL)								//if an empty cell was found and it is not past the current cell, move tiles
                                        {       valid = 1;								//tile was moved in this turn
                                                *(get_cell(cur_game, moveROW, compare)) = *(get_cell(cur_game, moveROW, moveCOL)); 	//move the current tile to the location of the compare cell
                                                *(get_cell(cur_game, moveROW, moveCOL)) = -1;                                          	//current cell is made empty
                                        }
				}		
			
			}
			else												//the "compare" cell does not have a value in it. The current cell can move to this location
                        	{
					 valid = 1;									//this turn moved tiles
                                         *(get_cell(cur_game,moveROW, compare)) = *(get_cell(cur_game, moveROW, moveCOL)); //our current tiles moves to the empty space at the compare cell
                                         *(get_cell(cur_game, moveROW, moveCOL)) = -1;                                      //current cell is now empty
                                }
		}
	}
}
if (!valid)		//if pressing this key doesn't change anything, return a 0
{
	return 0;
}
return 1;		//pressing this key moved tiles
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
	{
    //YOUR CODE STARTS HERE
	int i, j, current_spot;
	for (i = 0; i < cur_game->rows; i++) //loop through rows
	{
		for (j = 0; j < cur_game->cols; j++) //loop through cols
		{	current_spot = *(get_cell(cur_game, i, j)); //get the value at the specified cell
			if (current_spot == -1) //check to see if it is empty
			{
				return 1; //empty so still playable
			}
			else
			{
				if (i - 1 >= 0 && current_spot == *(get_cell(cur_game, i-1, j))) //check the spot right above current cell
				{	return 1;}	//same values. Can still play
				else if (j - 1 >= 0 && current_spot == *(get_cell(cur_game, i, j-1))) //check the spot to the left of the cell
				{	return 1;}		//same values --> can still play
				else if (j + 1 < cur_game->cols && current_spot == *(get_cell(cur_game, i, j+1))) //check the spot to the right of it
				{	return 1;} //same values and still playable
				else if (i + 1 < cur_game->rows && current_spot == *(get_cell(cur_game, i+1, j))) //check the spot below current cell
				{	return 1;} //same values so it is still playable
			}
					
		}
	}
	 return 0; //no more moves can be made. Denote game's end
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
