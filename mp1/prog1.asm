;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;Name: Emily Xu
;partners: ufacio2, ehaynes2
;Date: 1/25/22
;Description: This section of the program intends to print out the values stored in the histogram after sorting through the characters
;given in a seperate document. The sorting is implemented in the code provided above. First, it will print out the bin name, going from
;character '@', representing the non-alphabetical characters, to 'Z'. There are a total of 27 bins. Then, it will print out the 4 numbers represented in 
;HEX that signify the amount of times a certain character has appeared in the given string. 
;Approach: First, we initialize the neccessary values (example: initialize with 0, value at a certain memory, the address) and then print out
;the current ASCII character of the bin, followed by a space. Then, we set two counters to 4 in order to loop through the 4 bits in one HEX value (in R4), and
;the four HEX characters in one 16-bit pattern (in R5). First we left shift R0 to make a space for an incoming bit. Then, we take the MSB of the data from the
;appropriate bin address (in R1) and add 1 to another register (R0) if the MSB is 1. Nothing is done if the MSB is 0. We left shift the data in R1 afterwards. 
;This adding (if applicable) then shifting is done 4 times.
;Afterwards, we convert the 4 bits in R0 into their HEX equivalent by adding a fixed number to it. That number depends on whether if the HEX value is a 
;letter ASCII character or number ASCII character. We print that out and then go through the rest of the bits in the bit pattern, converting
;every 4 bits to a HEX character. 
;Afterwards, we print out a new line and then calculate how many bins it has been since the starting histogram bin. This is done by subtracting the 
;address of the non-alphabetic bin from the address of the next bin we are on. This will then be added to the value of the '@' character to 
;get the name of the next ASCII bin. This whole process will repeat until we reach bin Z (go on 27 times).


;R0 holds character printing out to the monitor
;R1 holds the data in the histogram bins
;R2 holds the current address of which histrogram bin we are on
;R3 is the counter for the bins (initialized for the 27 bins)
;R4 is a counter for the 4 bits in one hexidecimal value
;R5 is a counter for the 4 sections of hex values in one 16-bit pattern
;R6 will help calculate the ASCII character name for the bin and be for loading in values
	
		AND R0, R0, #0		;initializes R0 to 0
		LD R3, NUM_BINS		;initializes number of histogram bins (27)
		AND R6, R6, #0		;initialize R6 to 0

		LD R2, HIST_ADDR	;Loads in histogram's starting address
NEW_LINE	LD R0, AT_CHAR		;Loads in the char '@' which is the name of the first histogram bin
		ADD R0, R0, R6		;add in num of bins since the starting bin to the '@' char to get current ASCII bin character
		OUT			;print out ASCII bin name
		LD R0, SPACE_CHAR	;put the ASCII value of a space to R0
		OUT			;print out space character to screen

		LD R5, FOUR		;initializes counter for the 4 hex sections in a bit pattern
		LDR R1, R2, #0		;load in value stored in the memory address of the current histogram bin
NEXT_HEX	AND R0, R0, #0		;clears R0 to 0
		LD R4, FOUR		;initializes counter for 4 digits in one hex value
		
FOUR_BITS	ADD R0, R0, R0		;left shift value in R0
		
		ADD R1, R1, #0		;set cc to R1
		BRzp LEFT_SHIFT		;branch if the MSB of R1 is 0
		ADD R0, R0, #1		;if MSB of R1 is 1, update new bit in R0 with 1
LEFT_SHIFT	ADD R1, R1, R1		;left shift out MSB in R1
		ADD R4, R4, #-1		;decrement counter in R4
		BRp FOUR_BITS		;if counter is not 0, check next bit in hex section

		ADD R0, R0, #-9		;subtract value of 9 from R0
		BRnz NUM_CHAR		;if the value is negative or 0, the value in R0 is between 0 and 9 --> number ASCII

		LD R6, LETTER		;load in value that will get the value in R0 to the right ASCII letter
		BRnzp PRINT
NUM_CHAR	LD R6, NUMBER		;load in value that will get the value in R0 to the right ASCII number
PRINT		ADD R0, R0, R6		;get the right ASCII character to represent the hex value
		OUT			;print out the hex value

		ADD R5, R5, #-1		;decrement counter to get next 4 bits in bit pattern
		BRp NEXT_HEX		;get next hex value

		LD R0, NEW_LINE_CHAR	;get a new line ASCII character
		OUT			;print out new line

		ADD R2, R2, #1		;Go to the next histogram bin
		LD R6, MINUS_HIST	;load in the additive inverse of the starting address of the histogram
		ADD R6, R6, R2		;get value of how many bins since the starting histogram bin
		ADD R3, R3, #-1		;decrement counter for number of bin
		BRp NEW_LINE		;if we haven't reached all the bins (counter didn't reach 0), repeat process
		
	

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

MINUS_HIST	.FILL xc100	;additive inverse of the starting address of the histogram
FOUR		.FILL x0004	;holds the value 4
NUMBER		.FILL x0039	;holds decimal value 57
LETTER		.FILL x0040	;holds decimal value 64
SPACE_CHAR	.FILL x0020	;holds the space ASCII character
NEW_LINE_CHAR	.FILL x000a	;the ASCII value for a new line
AT_CHAR		.FILL x0040	;holds the @ ASCII character


; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
