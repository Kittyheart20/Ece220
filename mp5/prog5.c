/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */


//Name: Emily Xu
//Partners: ehaynes2, ufacio2
//Introduction:
//Functions of prog5.c. Within this program, there are three functions. The first function called set_seed asks the user for a potential seed number. In this function, it creates a variable and an array to hold either an
//integer value or a character value ( referred to as "int seed" and "char post[]"). Then, it takes in the user's input, with any integer values being stored to seed and any other characters, such as letters, into the post array. 
//However, the user input can only begin the game by inputting numbers. Therefore, we check to see how many values sscanf has stored. If sscanf is 1, that means only numbers have been inputted, which is what
//the function needs. Hence, we check for the resulting value given by the sscanf statement: if it is a one, the function continues and generates the seed. Then it returns 1 to signify its success. If sscanf is any other value, the input
//is considered "invalid," the user is alerted of the invalid input, and the function returns 0. 
//The second function, start_game, takes in pointer values for each of the four generated numbers in the solution. Then, based on the random seed, it creates 4 random numbers for the four respective values in the solution. That value
//is then modded by 8 to ensure the random value is within 0 to 7, and added with one to put its range of possible generated numbers to 1-8. Then, it initializes the variable counting the number of rounds the user is on to 1.
//Afterwards, it assigns the four different pointers to the locate where the four values of the user's guess will be. They are initialized to the solution of the problem for the time being. 
//The last function, make_guess, starts the guessing program. The user will first type in their guess, and sscanf will try to store 4 integer values to the variables w, x, y, and z. Any other character will be stored into the array post.
//Then, the function checks to see if the user is guessing valid integers. Any integers stored to the integer variables that exceed 8 or are smaller than 1 will immediately result in the function to return 0. This denotes that the input
//is not valid, and such error will be alerted to the user. If the integer values typed in are within range, then the function will check to see if there are any additional, unwanted characters typed in. If sscanf detects that more than
//4 or less than 4 values stored, then the function will alert the user that the input cannot be used and return 0. If only 4 values (all integers)  have been stored by sscanf, then the program progresses. 
//It then intializes the necessary variables: one for counting how many correct values the user has guessed, one for counting the misplaced values guessed, and a couple of status variables. The status variables that have "_g" attached
//shows the status of the user's guess with four total status_g variables. These variables equal 1 if that value has correctly guessed the corresponding value in the solution. The other 4 status variables, marked with "_s" refer to the
//four values in the solution. If any of the user's guesses (either correct guesses or misplaced guesses) equal one of the values in the solution, that value's respective "_s" variable will update to 1. After initializing the variables,
//the function then assigns the user's guess (w,x,y, and z) to their pointer locations (*one, *two, *three and *four) to use it to check answers. First, the function checks to see if the user made any correct
//guesses by checking the first value of the user's guess to the first value of the solution. If it is correct, the status variables will update accordingly and the counter for correct guesses will increment. Then, it'll check the second
//value, the third value and lastly the fourth value. Afterwards, the function will check for misplaced value. It will start by checking the user's first guess (that wasn't correct) against the solution's values in every other place
//except for the first value. If a match is found on any available values in the solution (if the status variable_s is not equal to 1), then the counter for misplaced values will increment, and that value in the solution will have
//its status variable updated so that it cannot be checked again for misplaced values. This misplaced value checking will continue until all of the user's values that haven't correctly guessed anything check with all the other
//solution values that are still available. Once all of this check is done, the function will tell the user their guess round, and the number of correct and misplaced gueses they have made. It will then increment the counter for what 
//round they are on and return 1. 


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;			//contains the static ints provided to us by the mp. The first static int keeps track of how many guesses have been used
static int solution1;				//holds the answer of the first number in the 4 number sequence
static int solution2;				//holds the answer of the second number in the sequence
static int solution3;				//holds the answer of the third number in the sequence
static int solution4;				//holds the answer of the fourth number in the sequence


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 

      int seed;  							//will hold the inputted integer value (this code was provided mp)
      char post[2];							//will hold any other extraneous characters entered (this code was provided by the mp)
      int response = sscanf (seed_str, "%d%1s", &seed, post);		//store the return value of the sscanf statement so we can easily check to see how many "values" it has stored
									//(sscanf code was provided by the mp)
      if (response == 1)						//only an integer was inputted --> usable input
	{
		srand(seed);						//uses input to generate the seed used in this game
	}
      else
	{
		printf("set_seed: invalid seed\n");			//if either no suitable characters are read or additional characters are inputted, tell the user that
									// their answer was invalid 
		return 0;						//since what was inputted could not be considered valid, return 0	
	}
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer.
   
    return 1;								//returns 1 to denote success (one integer received) and exit
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
	solution1 = rand()%8 + 1;			//get a random number and put it into the variable solution1. Mod 8 will ensure that the answer will be in the range 0-7.
							//Adding 1 adjusts the range to 1-8
	solution2 = rand()%8 + 1;			//get the second random number for solution2
	solution3 = rand()%8 + 1;			//get the third random numbe for solution3
	solution4 = rand()%8 + 1;			//get the last random number for solution4
	
	guess_number = 1;				//initiate guess_number to 1 to start keeping track of how many guesses have been made
	
  	*one = solution1;				//set 'one' to hold the address of where solution1 is. *one will hold the value of solution1.
	*two = solution2;				//similarly, 'two' points to address of solution2
	*three = solution3;				//'three' points to the address of solution3
	*four = solution4;				//'four' points to the address of solution4

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
 {
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed


	int w, x, y, z;									//the variables that will hold the user's guesses (code provided to us)
	char post[2];									//will hold the extraneous input characters (code provided to us)
	int valid = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);		//holds the number of inputted values (sscanf provided to us by mp)
	if (w < 1 || w > 8 || x < 1 || x > 8 || y < 1 || y > 8 || z < 1 || z > 8)       //checks to see if the numerical inputs are numbers from 1-8
	{
		printf("make_guess: invalid guess\n");					//inputted number is 0 or less, or it is greater than 8. Notify the user that this is not allowed
		return 0;								//because the guess isn't in the range of 1-8, we return 0
	}

	if (valid == 4)									//4 inputs received signifies that 4 integers have been inputted
	{

		int correct = 0;				//sets up our variables. Correct counts how many of the guesses were correct in this round. Resets to 0 every new round
		int misplaced = 0;				//the amount of numbers in the wrong place
		int one_paired_g = 0;				//checks to see if our guess for the first value is the same as the solution or not. 1 if it is the same. 0 if it isn't
		int one_paired_s = 0;				//mean to check to see if the solution's first value was guessed or not
		int two_paired_g= 0;				//used to check if the user's guess for value 2 is correct or not. 1 if correct. 0 if they didn't guess it at the right place
		int two_paired_s = 0;				//status on whether of not the solution's second value has been guessed or not (1 if guessed)
		int three_paired_g = 0;				//shows if the user guessed the third number correctly or not. 1 -> correct. 0 -> incorrect.
		int three_paired_s = 0;				//status on whether the solution's third value has been guessed or not
		int four_paired_g = 0;				//equals 1 if the user guessed the fourth number right
		int four_paired_s = 0;				//status on whether the solution's fourth value has been guessed or not

		*one = w;				 	//one holds the address of what the user guessed for the 1st number. *one holds the guessed value
		*two = x;					//*two holds the user's guess for the second number
		*three = y;					//*three holds the user's guess for the third value
		*four = z;					//*four holds the user's guess for the fourth value
		
		if (*one == solution1)				//check to see if the user guessed the first number right
		{
			correct++;				//user guessed it right, increment the counter for correct guesses
			one_paired_g = 1;			//update to system that the user's guess for the first number is right
			one_paired_s = 1; 			//the first number of the solution has been guessed correctly. 
		}
		if (*two == solution2)				//check to see if the second number has been guessed
		{					
			correct++;				//second number guessed correctly
			two_paired_g = 1;			//user's second number was correct
			two_paired_s = 1;			//the second number in the solution was guessed correctly
		}
		if (*three == solution3)			//check to see the the 3rd number is guessed correctly
		{
			correct++;				//guessed correctly. increment the counter for correct guesses		
			three_paired_g = 1;			//signifies that the user guessed the third number right
			three_paired_s = 1;			//the third number in the solution was guessed
		}	
		if (*four == solution4)				//check to see if the 4th number is guessed correctly or not
		{
			correct++;				//4th number guessed right
			four_paired_g = 1;			//user's 4th number was right
			four_paired_s = 1;			//solution's fourth number has been guessed
		}
		if (one_paired_g != 1 && two_paired_s != 1 && *one == solution2)		//start checking for misplaced values. Check to see if user's first number equals the
			{									//solution's 2nd number if they haven't been guessed correctly already
				misplaced++;							//user's first value equals solution's second value. Increment 'misplaced' counter
				two_paired_s = 1;						//shows that the solution's second value is guessed, but the user did not have it in the 
												//right place
			}
		else if (one_paired_g != 1 && three_paired_s != 1 && *one == solution3)		//check to see if user's 1st value equals solution's 3rd value if they both haven't been 
			{									//guessed/have guessed correctly
				misplaced++;							//user's 1st value = solution's 3rd value, indicating a misplaced number
				three_paired_s = 1;						//solution's 3rd number has been guessed, but not in the right place by the user
			}
		else if (one_paired_g != 1 && four_paired_s != 1 && *one == solution4)		//does user's 1st value = solution's 4th value? (hasn't guessed a value right yet/hasn't 
			{									//been guessed yet)
				misplaced++;							//user's 1st number = solution's 4th number. Increment counter
				four_paired_s = 1;						//solution's 4th number has been guessed by user, but at a different location
			}
		 if (two_paired_g != 1 && one_paired_s != 1 && *two == solution1)		//is user's 2nd number = solution's 1st number? (both can either still guess or be guessed)
                        {	
                                misplaced++;							//they are equal, increment counter
                                one_paired_s = 1;						//solution's 1st number has been guessed by user at a different spot
                        }
                else if (two_paired_g != 1 && three_paired_s != 1 && *two == solution3)		//is user's 2nd value = solution's 3rd value? Both can either still guess or be guessed. 
                        {
                                misplaced++;							//user's 2nd value = solution's third value. Increment counter for misplaced values
                                three_paired_s = 1;						//solution's 3rd value has been guessed at the wrong location by user
                        }
                else if (two_paired_g != 1 && four_paired_s != 1 && *two == solution4)		//user's 2nd value = solution's fourth value? Both either can still guess or be guessed
                        {
                                misplaced++;							//user's 2nd value = solution's 4th value. Increment number of misplaced values
                                four_paired_s = 1;						//solution's 4th value has been guessed at wrong location by user
                        }
		if (three_paired_g != 1 && one_paired_s != 1 && *three == solution1)		//user's 3rd value = solution's 1st value? Both can either still guess or be guessed	
                        {
                                misplaced++;							//user's 3rd value = solution's 1st value. Increment number of misplaced values
                                one_paired_s = 1;						//solution's 1st value has been guessed at another spot by the user
                        }
                else if (three_paired_g != 1 && two_paired_s != 1 && *three == solution2)	//user's 3rd value = solution's 2nd value? Both can either still guess or be guessed 
                        {
                                misplaced++;							//user's 3rd value = solution's 2nd value. Increment number of misplaced values
                                two_paired_s = 1;						//solution's 2nd value has been guessed at another spot by the user
                        }
                else if (three_paired_g != 1 && four_paired_s != 1 && *three == solution4)	//user's 3rd value = solution's 4th value? Both can either still guess or be guessed 
                        {
                                misplaced++;							//user's 3rd value = solution's 4th value. Increment number of misplaced values
                                four_paired_s = 1;						//solution's 4th value has been guessed at another spot by the user
                        }
		if (four_paired_g != 1 && one_paired_s != 1 && *four == solution1)		//user's 4th value = solution's 1st value? Both can either still guess or be guessed 
                        {
                                misplaced++;							//user's 4th value = solution's 1st value. Increment number of misplaced values
                                one_paired_s = 1;						//solution's 1st value has been guessed at another spot by the user
                        }
                else if (four_paired_g != 1 && two_paired_s != 1 && *four == solution2)		//user's 4th value = solution's 2nd value? Both can either still guess or be guessed
                        {
                                misplaced++;							//user's 4th value = solution's 2nd value. Increment number of misplaced values
                                two_paired_s = 1;						//solution's 2nd value has been guessed at another spot by the user
                        }
                else if (four_paired_g != 1 && three_paired_s != 1 && *four == solution3)	//user's 4th value = solution's 3rd value? Both can either still guess or be guessed
                        {
                                misplaced++;							//user's 4th value = solution's 3rd value. Increment number of misplaced values
                                four_paired_s = 1;						//solution's 3rd value has been guessed at another spot by the user
                        }
		printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, correct, misplaced); //update user on what round they are on, the number of 
															       //correct guesses they have and misplaced guesses they have
		guess_number++; 								//update round number
	}
	else											//for when sscanf gets more/less than 4 values from the user
	{ 
		printf("make_guess: invalid guess\n");						//tell user that their input cannot be used
		return 0;									//return 0 because of un-usable input
	}
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  

    return 1;											//guess went through and feedback was given to user. Return 1 because the round worked
 }


