#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

//Name: Emily Xu
//Partners: ufacio2, ehaynes2
//Introduction: This code is meant to solve a sudoku given to the this program. We were tasked to write 5 of the functions for this program. 
//The first function is_val_in_row is tasked to find a specific value (named val) in a specified row (row i) of the sudoku. It will loop through the 9 columns of the specified row and return 1 if the target value is found. 
//The second function called is_val_in_col tries to find the target value (val) in a specific column (column j). It will loop through the 9 rows in that respective column and return 1 if the target value has been detected. 
//The third function called is_val_in_3x3_zone will try to find the target value in one of the 9 pre-determined gridded areas in the sudoku. It will first determine which "grid" the selected cell is located in (the selected cell having
//the coordinates of [i][j]). This is done by checking to see if the cell's coordinates fall between the specifice indices for both the row and column of a respective area. If the cell's coordinate fall between the range given by a grid,
//for example between rows 0-2 and columns 0-2, the function will give it a new set of cooridinates (which is the coordinates for the uppermost left corner of the grid). Each grid has 3 rows and 3 columns in it. Then the function will
//loop through the 3x3 area via a nested for loop: one to loop through the 3 rows and another inner loop to go through the 3 columns. If the target value is found in any spot within its respective grid, it'll return a 1.
//The fourth function is_val_valid will check to see if the number we want to fill in a specific location is found within the same row, column or 3x3 area as the target location. This function calls upon the three previous functions to 
//determine if there are any numbers equal to the target number in the same row, column and 3x3. If any one of those conditions ring true, then the program will return a 0, denoting that location cannot be filled with our target number.
//The last function is solve_sudoku and it is the recursive statement. First, it'll look through the 9x9 array via double nested loop. It will look to see if there are any '0's or empty areas in the sudoku. If it finds any, it'll set
//a variable (preset as 1) to 0 to denote that the sudoku isn't completed yet. Then, it'll save the coordinates of that empty cell and immediately stop looping through the 9x9 by breaking out of the two nested for loops. 
//Then, it'll check the base case: if solve is still equal to 1 even after looping through all cells in the sudoku, that means that there are no empty locations anymore and that the sudoky is complete. This will cause the function to 
//return 1. However, if solve has been set to 0, then that means the sudoku has empty spots. That will lead the function to loop through the numbers 1 to 9 to fill in that space. It'll use the function is_val_valid at the spot recorded 
//down in the previous nested for loops and check if the current number the function is guessing can be put there. If it can be, the function will fill in that location and then call on solve_sudoku again. This time, it'll look at the
//next empty spot and try to fill that it. If at anytime the number filled in makes it so that the sudoku cannot be solved, it'll then refill that first empty cell location with a 0. Otherwise, solve_sudoku would return a 1, denoting 
//that it is completed. After going through all 9 possible numbers, the function will return a 0, meaning that it is not complete.



// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);				//provided code
 int c;						//declare variable c to count through the columns
 for (c = 0; c < 9; c++)			//go through every column in the sudoku
{
	if (sudoku[i][c] == val)		//check to see if there is a column in the selected row i that matches target value "val"
		return 1;			//return 1 becuase target value is detected
} 
  return 0;					//target value is not in this row. Return 0
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);				//provided code
  int r;					//declare variable r to keep track of rows
  for (r = 0; r < 9; r++)			//go through every row in the sudoku
{
	if (sudoku[r][j] == val)		//check to see if any values in the selected column j equal the target value
		return 1;			//target value located in the column
} 	
  return 0;					//target value is not in the column
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);				//provided code
int row, col,a,b;				//declare variables
if (i >=0 && i < 3)				//check to see if the chosen cell is in the top third of rows in the sudoku
	row = 0;				//selected cell is in the top third rows. Begin the loop through the 3x3 at row 0	
else if (i >=3 && i < 6)			//check to see if the chosen cell is in the middle third of rows in the sudoku
	row = 3;				//selected cell is in the middle third rows. Begin the 3x3 loop at row index 3
else if (i >=6 && i < 9)			//check to see if the chosen cell is in the last third of rows in the sudoku
	row = 6;				//selected cell is in the last third of rows. Begin the 3x3 loop at row 6 

if (j >= 0 && j < 3)				//check to see if the chosen cell is in the first third of columns	
	col = 0;				//selected cell is in the first third of columns. Start 3x3 loop at column 0
else if (j >= 3 && j < 6)			//check to see if the chosen cell is in the middle third of columns
	col = 3;				//selected cell is in the middle third of columns. Start 3x3 loop at column 3 
else if (j >= 6 && j < 9)			//check to see if the chosen cell is in the last third of columns 
	col = 6;				//selected cell is in the lower third or columns. Begin 3x3 loop at column 6

for (a = 0; a < 3; a++)				//Goes through 3 rows in the 3x3
{
	for (b = 0; b < 3; b++)			//Goes through 3 columns in the 3x3
	{
		if (val == sudoku[row][col])	//check to see if the current cell equals out target value
		{
			return 1;		//Once the target value is detected, return 1 immediately to end sequence
		}
		col++;				//Go to the next column in the 3x3 to check for the target value
	}
	row++;					//go to the next row
	col -= 3;				//Since the inner for loop has searched through the 3 columns, this statement will reset that counter so that it returns to the first column we are searching
}
 return 0;					//The target value is not within the respective 3x3 area
}
// Function: is_val_valid
// Return true if the val can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

assert(i>=0 && i<9 && j>=0 && j<9);										//provided code
if (is_val_in_row (val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku))	//Check to see if there is a number with the same value as the selected number in either the same row, column or 3x3 area
   return 0;													//The same value is detected in either the same row, column or 3x3. Number is unusable, therefore the code returns 0
 else													
   return 1;													//no number of the same value in the same row, column and 3x3 area as our current number. It is okay to use this number
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {			//code follows the provided pseudo-code given in the MP7 instructions
int i, j, solve = 1, ROW, COL, fill;			//set up the necessary variables. Variable solve is defaulted to 1	
for (i = 0; i < 9; i++)					//Loop through the 9 rows in the sudoku
{
	for (j = 0; j < 9; j++)				//Loop through the 9 columns in the sudoku
	{
		if (sudoku[i][j] == 0)			//check to see if the current cell is empty (0)
		{
			solve = 0;			//Cell is empty. Set variable solve to 0 to denote that the recursive statement is not ending - there are cells that need to be filled with numbers still in the sudoku
			ROW = i;			//Save the row index of that empty cell in ROW
			COL = j;			//Save the column index of that empty cell in COL
		}
	if (solve == 0)					//Once one empty cell is detected, break out the loop through the columns to ensure that we save the right coordinates
		break;
	}
	if (solve == 0)					//Once the empty cell is detected, break out of the row loop as well
		break;
}	
if (solve)						//base case --> This means that there are no empty spots left
{
	return 1;					//done with recursion
}

for (fill = 1; fill < 10; fill++)			//Looping through the possible numbers (1-9) to fill in the cell
{
	if (is_val_valid(fill, ROW, COL, sudoku))	//check to see if the current spot is available to be filled with out current number
	{
		sudoku[ROW][COL] = fill;		//put the number there in that spot
		if (solve_sudoku(sudoku))		//check to see if we need to continue the recursion. If it is 0, that means we are not done filling out the sudoku
		{
			return 1;			//sudoku is done
		}
		sudoku[ROW][COL] = 0;			//Since no '1' has been returned, that means that the sudoku still has empty spots with the current number placed at location [ROW][COL]. Therefore, the code resets the spot and
	}						//goes to the next number to check if that number placement will be more successful
}
 return 0;						//sudoku is not solved yet
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





