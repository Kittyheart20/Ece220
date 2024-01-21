/*Name: Emily Xu
Partners: ufacio2, ehaynes2
Introduction: This program is meant to implement three functions integral to the game "Game of Life." This program has the functions "countLiveNeighbor," "updateBoard," and "aliveStable."
In countLiveNeighbor, after taking in the array, the number of rows and columns, and a chosen cell's row and column value, we check all the cells surrounding the chosen cell. This is done by checking rows from one above the
chosen cell's row to the row right below the chosen cell's row. Then, it checks the columns from one to the left of the chosen cell's column to the one on the right of the chosen cell's column. For example, If the chosen cell's row is
called r and its column is called c, we would loop through from row (r-1) to (r+1) and from columns (c-1) to (c+1). The cell's own location will not be considered when counting the number of live neighbors. To do this, we implement a
double nested loop: the outer loop goes through the selected rows while the inner loop goes through the selected columns. At every cell, the program will first determine if the values it calcuated for its row and column are in the bounds
of the array. It does this through an if statement by checking if the row and column it is on are both greater than or equal to 0 and less then given total rows or total columns. If the row and column satisfies these preliminary checks,
then it will check the value stored at that location. Since we are dealing with a 1-D array, we cannot use the coordinate system [row][column]. Therefore, the current index of the element can then be calcuated as its row*(number of 
total columns) + its column. To factor out the chosen cell's position, an if statement is used to see if the looped row and looped column equals the chosen cell's coordinates and skips any actions if it matches. For other cases, if the
value there is a 1, then a counter will be updated to keep track of all the live cells near our chosen one. After going through the two nested loops, the function will return how many live cells it has counted.

In the function updateBoard, we follow the rules established in the "Game of Life" to update the status of the cells depending on the neighbors around a chosen cell. In general, live cells stay alive when they are surrounded by 2 or 3
other live cells. Otherwise, it dies. A dead cell is dead unless they have three living neighbors. Dead cells are represented as zeros while the live ones are represented as ones. This function updates the board by first creating a 
replica of the current board. This is done by making another 1-D array with the same dimensions and, going element by element, storing the same values at the same locations from array board to our replica. Then, we loop through all the
elements of the array board via two nested for loops to keep track of the row and column of each cell and to access all the cells. At every cell, this function calls upon countLiveNeighbor to find the number of alive cells near that
specific cell and store it in a variable called 'status.' Then, following the guidelines for a cell being dead or alive, the function then checks the status and updates the cells in the replicated array. That way, the original board 
stays intact and all the cells in it will calculate its status based on untampered values. After checking all the cells, the values in the replica array will be copied over to board to officially update the game board. The nested loops 
will get the index of the array by using the same formula as seen in countLiveNeighbor. 

In the last function aliveStable, its purpose is to give a return value of 1 if the board and its next iteration will have the same values at every cell. It will return 0 if the board changes in any way from one iteration to another. 
To do this, the program makes another copy of the array board by initializing an array with the same number of elements. This can be determined by muliplying the total number of rows and the total number of columns of board together
to get the total elements. Then, the function copies all of the values in board to that new array by looping through all the elements and storing each one of them in the new array at the same location. Afterwards, aliveStable calls on 
updateBoard with the array copy being the array passed into that function's arguments. Therefore, our current board stays intact while also getting the updated values. Afterwards, the function uses one last for loop to go through
all the elements in board and to compare the value at the same index in both of the arrays. If they differ in any way, the function immediately returns 0. If no change is detected, then a 1 is returned.
 */



/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int count = 0, r = row - 1, c, a, b;							//initialize/declare the necessary variables
	for (a = 0; a < 3; a++)									//check three rows to see the status of all the chosen cell's neighbors
	{ 
		c = col-1;                                                    			//for every new row we check, we need to reset the column to be (col-1) so we can check the next consecutive three cells  
		for (b = 0; b < 3; b++)								//in each row, check three columns to see the status of the cell's neighbors
		{
			if (r >= 0 && r < boardRowSize && c >= 0 && c < boardColSize)		//check to see if the row or column of the cell we are checking is in the bounds of the array or not
			{
				if (!(r == row && c == col))	 				//check to see if the cell we are checking is a neighbor or not
				{
					if (board[r*boardColSize + c] == 1)			//since this cell is a neighbor, check to see if the cell is alive or not
					{
						count++;					//increment count of live neighbors
					}
				}
			}
			c++;									//check the next column over
		}
		r++;										//finished with all the columns in this row. Increment r to check new row
	}
	return count;										//this function find out how many neighbors around our chosen cell is still alive
} 
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */

void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int r, c, status, i;									//declare the necessary variables
	int update[boardRowSize*boardColSize];							//create another array to hold values after the board has been updated
	for (r = 0; r < boardRowSize; r++)							//loop through all the rows in the board
	{	
		for (c = 0; c < boardColSize; c++)						//for every row, loop through every column in the board
		{
			status = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);    //get a count of the number of live neighbors and store it in a variable called status	
			if (board[r*boardColSize + c] == 1) {				
				if (status < 2 || status > 3)					//if the cell is alive, check to see if there is over/underpopulation
				{
					update[r*boardColSize + c] = 0;				//overpopulation or underpopulation is detected. Cell is now dead. Store 0 in the new array in the same spot as it was in board
				}
				else								//there are 2 or 3 neighbors
				{
					update[r*boardColSize + c] = 1;				//cell is still alive --> store a 1 in the new array
				}
			}
			else									//current cell is dead
			{
				if (status == 3)						//check to see if the cell can be revived or not (3 neighbors)
				{
					update[r*boardColSize + c] = 1;				//three neighbors detected --> cell is revived so store a 1 in the new array
				}
				else								//cell is not surrounded by three neighbors. Cell stays dead 
				{
					update[r*boardColSize + c] = 0;				//cell stays dead --> store a 0 in the new array
				}
			}
		}
	}
	for (i = 0; i < boardRowSize * boardColSize; i++) 					//loop through all the cells in board
	{
		board[i] = update[i];								//move all values in array "update" to the board to officially update the game board
	}
}

/*
 * aliveStable
* Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int copy, i;								//declare variables to help us copy the board down to another array and to keep track of our placement
	int next_b[boardRowSize*boardColSize];					//create a new array to hold the status of the board after one iteration (same size)
	for (copy = 0; copy <boardRowSize*boardColSize; copy++)			//go through every element in the array named "board"
	{
		next_b[copy] = board[copy];					//next_b array gets the same values at the same spots as the elements in board 
	}
	updateBoard(next_b, boardRowSize, boardColSize);			//get the next iteration of our board and store that in next_b
	for (i = 0; i < boardRowSize*boardColSize; i++)				//go through all the elements of the two arrays
	{
		if (next_b[i] != board[i])					//check to see if the values are the same in both arrays at a certain spot i
		{
			return 0;						//changes were made after updating the board. Board is not stable --> return 0 to denote its instability
		}
	}	
	return 1;								//board is stable and doesn't change anymore. Return 1 to denote its stability
	
}

				
				
			

