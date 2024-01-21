#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//Name: Emily Xu
//Partners: ufacio2, ehaynes2
//examples from the lab9 presentation and from lecture 16 of ece220 were helpful in making this mp.
//There are four functions in this c file. createMaze takes in a file and finds the correct sizes of space on heap to store the values of this maze. (It'll store space for the columns and rows of 
//the maze). This code will also get the dimensions of the maze. destroyMaze uses the pointer given by createMaze to free up the pointers to the columns and rows of the maze array, as well as the current
//pointer to said maze.
//printMaze loops through the array of the maze and prints it out to be seen.
//Lastly, solveMazeDFS uses recursion to continuously check for ways to complete the maze. It will first ensure that the current spot we are in inside the maze is not out of bounds, on a wall or overriding 
//the current path it is taking. The fucntion will repeat itself for positions to the left of, the right of or above/below to find valid solutions to the maze. If we are in a dead end, it'll denote that such spot was visited 
//and should not be ran through again.
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
	FILE* openFILE = fopen(fileName, "r");   	     				//opens given file to extract information from
   	maze_t* maze_ptr =(maze_t*) malloc(sizeof(maze_t));				//find a location for maze_t in heap. Contains the address of where this "struct" will be
	int  i, j;									//declare variables for looping
	char character;									//declare variable to hold characters being extracted from file
	fscanf(openFILE, "%d %d", &(maze_ptr->width), &(maze_ptr->height));		//takes in the two integers in the file and stores them as width and height respectively of the struct
											//code based off of given examples in lecture 16

	char** row_ptr = (char**) malloc(sizeof(char*) * maze_ptr->height);		//this is meant to locate the address of a section of data full of double pointers.
	maze_ptr->cells = row_ptr;							//Essentially, these pointers act like the "rows" of 
											//a 2D array, so each row will hold another pointer that will have all the
											//elements of that row (all the columns of that row). Hence, we need to
	int row;									//make "maze->height" amounts of locations in heap for the double ptr.
	for (row = 0; row < maze_ptr->height; row++)					//looping through "height" amount of times
	{					
		*(row_ptr+row) = (char*) malloc(sizeof(char)*maze_ptr->width); 		//every spot in the array cell_ptr holds the address to
											//another area in heap. This one will (malloc returns a ptr)
											//contain the address to the columns of said row i that we are on (starting with row '0')
	}										//the code for making the space for cells and the board layout is based off of the code given
											//to us in the lab9 presentation
	for (i = 0; i<maze_ptr->height; i++)						//This will keep track of the rows when filling in the maze structure from the file
	{
		for (j = 0; j<maze_ptr->width; j++)					//keeps track of the columns in the file
		{
			do{								//as we are reading in the file, the do-while loop ensures that the program is only getting "valid" 
				character = fgetc(openFILE);				//characters from said file: if it does not find a valid character (for example, a newline char), it'll read
			}								//continuously until it finds a valid one.
			while(character == '\n');					//if the character isn't a newline, we will check to see if it is a start/end 
			if (character == START)						//coordinate and put the value into the cells array
			{
				maze_ptr->startRow = i;					//start character detected. Save the row index to the struct member "startRow"
				maze_ptr->startColumn = j;				//save the column index of the starting spot
			}			
			else if (character == END)					//end spot is found
			{	
				maze_ptr->endRow = i;					//end spot's row index is saved
				maze_ptr->endColumn = j;				//end spot's column index is saved
			}
		maze_ptr->cells[i][j] = character;					//put the valid character read in into their corresponding location in cells
		}
	}
	
	fclose(openFILE);								//close the file
	return maze_ptr;								//returns the pointer
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    	int i;						//declare variable for looping
	for (i = 0; i < maze->height; i++)		//going through each row of the 2D array
		free(*(maze->cells+i));			//we first free the pointers of the columns that each row in maze->cells has. The offset of 'i' makes it so
							//the code accesses every column ptr that each row stores
	free(maze->cells);				//Since there is only one ptr created that points to the rows, it only needs to free that location
	free(maze);					//maze itself has its location in heap freed
}
/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
   	int i,j;						//declare looping variables
	for (i = 0; i<maze->height; i++)			//loop through the rows
	{
		for (j = 0; j < maze->width; j++)		//loop through the columns
		{
			printf("%c", maze->cells[i][j]);	//print out every cell/spot in the maze
		}
	printf("\n");						//before moving onto the next row, print out a newline for formatting
	}

}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.			//following the pseudocode given to us by the MP9 assignment page:
//base cases
	if (row < 0 || row >= maze->height || col < 0 || col >= maze->width)			//checks that we are in the bounds of the array
		return 0;									//out of bounds --> error so return 0
	if (maze->cells[row][col] == WALL || maze->cells[row][col] == VISITED || maze->cells[row][col] == PATH)		//check to see if the spots around the current location is either a wall, someplace already
		return 0;												//visited or part of the path it just took. If any of those are true, return 0 --> cannot move there
	if (maze->cells[row][col] == END)										//check to see if the maze is completed
		return 1;												//end found


	if ((maze->cells[row][col] != START))							//check to see if we are on the starting tile
		maze->cells[row][col] = PATH;							//because we are not on the starting tile, program marks current spot as the latest tile on its path
	if (maze->cells[row][col] == START)							//check to see if the current tile is the start or not
	{	
		if (maze->cells[row+1][col] == PATH || maze->cells[row-1][col] == PATH || maze->cells[row][col+1] == PATH || maze->cells[row][col-1] == PATH)		//one of the spots to the left/right or above/below the start
			return 0;																	//is part of path. This section helps with the error of not 
																					//marking the visited cells near start by returning 0
	}
	if (solveMazeDFS (maze, col - 1, row))				//check the path to the left of our current spot
		return 1; 
	if (solveMazeDFS (maze, col + 1, row))				//check the path to the right of our current spot
		return 1; 
	if (solveMazeDFS (maze, col, row - 1))				//check the path above our current spot
		return 1; 
	if (solveMazeDFS (maze, col, row + 1))				//check the path below our current spot
		return 1;  
	if ((maze->cells[row][col] != START))				//since the current tile is not a starting tile
		maze->cells[row][col] = VISITED;			//fill current spot as visited since we cannot move further on in solving the maze at this spot
	
	return 0;							//show that this path doesn't work
}
