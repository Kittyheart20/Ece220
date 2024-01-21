;Name: Emily Xu
;Date: 2/10/22
;Introduction: The program deals with computating the result of expressions written in postfix form. All values will be outputted onto the 
;screen to see what was entered. However, only numbers (0-9), spaces, and operators (+,-,/,*,^,=) will go through to calculate a result. This
;is done by checking to see if the hex value of the inputted character matches the hex value of characters 0 to 9, the space, or of the above
;specificed operators. We achieve this by getting the negative version of those hex values and adding it to our input character. If that result
;is zero, the input is a valid character. When a number is detected, the program will save the value by pushing it onto a designated stack. 
;If an operator was inputted, the two most 'recent' numbers will be retrieved and the appropriate mathematical operation will be done. Afterwards, the
;answer is saved back to the stack. In the end, if there is only one value left in the stack when '=' is inputted, then that answer will be 
;printed out in hex and the value will be saved to R5. In cases of underflow, invalid characters, or uncomputable equations, the code will
;alert the user and stop.
 
;Subroutines: There is a subroutine for all operators. All will preform their specified tasks using R3 and R4 as values for their computation.
;The evaluate subroutine directs the code to the correct operator subroutines and handles the push/pop functions to get the values to the 
;right locations. The print_hex subroutine correctly displays the result stored in R5 on the screen.

;partners: ehaynes2, ufacio2


;R0 - holds character getting read in
;R1 - holds value to help with comparisons and the addresses of the invalid string that could be printed
;R2 - holds result of computation temporarily
;R5 - holds the result of the postfix equation at the end of the program/holds the value to check if something is invalid or not

.ORIG x3000
	
;your code goes here
		AND R5, R5, #0		;clear R6
NEXT_CHAR	GETC			;Read in a character
		OUT			;Print character out
		LD R1, INVERSE_EQUAL	;load in the negative hex value of the equal sign ascii
		ADD R1, R1, R0		;check to see if the entered character is an equal sign or not
		BRz CHECK_END		;the entered value is an equal sign --> equation has ended. Go to check validity of equation
		JSR EVALUATE		;go evaluate/update expression
		ADD R5, R5, #0		;set cc to R5
		BRp INVALID		;something invalid was detected in the evaulate subroutine --> print invalid
		BRnzp NEXT_CHAR		;get the next character in the equation

CHECK_END	JSR POP			;get result from the stack
		ADD R2, R0, #0		;copy result from R0 to R2
		ADD R5, R5, #0		;set cc to R5
		BRp INVALID		;if the stack is empty, print invalid string
		JSR POP			;pop again to check for underflow
		ADD R5, R5, #0		;set cc to R5
		BRnz INVALID		;there is underflow, meaning that we only have 1 item in stack
		ADD R5, R2, #0		;move result back into R5
		JSR PRINT_HEX		;print out the result in hexadecimal
		BRnzp STOP		;finish

INVALID		LEA R1, INVALID_STR	;put starting address of the string in R1
LOOP		LDR R0, R1, #0		;put ascii value at said address in R0
		BRz STOP		;once the ascii value loaded in is null, we can finish
		OUT                     ;Print out ascii character 
                ADD R1, R1, #1		;go to the address of the next character in the string
		BRnzp LOOP		;repeat process	

STOP		HALT


INVERSE_EQUAL	.FILL xFFC3
INVALID_STR	.STRINGZ "Invalid Expression"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRINT_HEX
;code from lab1
;OUTPUT --> R0 (four bit value of one ascii character)
;R1 = counter value (4) for looping one section of 4 in the bit pattern
;R2 = counter value (4) for looping through all the sections of 4 in the bit pattern
;R4 = changes value into correct ASCII character
;R5 = holds hexadecimal bit pattern (input)

		ST R1, PRINT_SAVE_R1    ;save value in R1
		ST R2, PRINT_SAVE_R2	;save value in R2
		ST R4, PRINT_SAVE_R4	;save value in R4
		ST R5, PRINT_SAVE_R5	;save value in R5
		ST R7, PRINT_SAVE_R7	;save value in R7

		LD R2, FOUR		;intialize R2 to 4
NEXT_HEX	LD R1, FOUR		;initialize R1 to 4
		AND R0, R0, #0		;initialize r0 to 0
	
ONE_HEX		ADD R0, R0, R0		;makes space for new bit value. This new bit
					;value will be the MSB of the bit pattern in R5
		ADD R5, R5, #0		;set cc value to R5's value
		BRzp SHIFT		;branches if the MSB of R5 is 0
		ADD R0, R0, #1		;if the MSB of R5 is 1, we add a 1 to update
					;the bit value in R0
SHIFT		ADD R5, R5, R5		;shift out the MSB of R5
		ADD R1, R1, #-1		;decrease counter value
		BRp ONE_HEX		;repeat until R0 has 1 hex value
	
		ADD R0, R0, #-9		;subtract 9 from R0 to see what range it 
					;falls into (numbers <=9  Letters >9)
		BRnz NUMBER		;branch because hex value would be a number
		LD R4, TO_LET		;get decimal value 64 so R0 can get to the correct
					;ASCII character (Letter)
		BRnzp PRINT		;get ready to print out ASCII character
NUMBER		LD R4, TO_NUM		;get decimal value 57 so R0 can get to the 
					;correct ASCII character (Number)
PRINT		ADD R0, R0, R4		;add appropriate value from R4 to R0
		OUT			;print out ASCII character
		ADD R2, R2, #-1		;decrement counter loop
		BRp NEXT_HEX		;if counter is not 0, continue to next 4 bit
					;section in bit pattern
	
		LD R1, PRINT_SAVE_R1	;get old value back from R1
		LD R2, PRINT_SAVE_R2	;get old value back from R2
		LD R4, PRINT_SAVE_R4	;get old value back from R4
		LD R5, PRINT_SAVE_R5	;get old value back from R5
		LD R7, PRINT_SAVE_R7	;get old value back form R7
	
		RET			;return from subroutine PRINT_HEX

FOUR		.FILL x0004
TO_NUM		.FILL x0039
TO_LET		.FILL x0040

PRINT_SAVE_R1	.BLKW #1
PRINT_SAVE_R2	.BLKW #1
PRINT_SAVE_R4	.BLKW #1
PRINT_SAVE_R5	.BLKW #1
PRINT_SAVE_R7	.BLKW #1

;R0 - character input from keyboard (INPUT)
;R1 - register used to load in ascii values that will check to see what character is being inputted in
;R2 - register used to help with computations
;R3 - value in the 'higher' stack location (most recent one)
;R4 - value in the 'lower' stack location
;R5 - Holds a positive number if there is an invalid character found (OUTPUT)
;R6 - holds a copy of the inputted character
EVALUATE

;your code goes here
		ST R1, EVAL_R1		;store value that was in R1	
		ST R2, EVAL_R2		;store value that was in R2
		ST R7, EVAL_R7		;store value that was in R5

		ADD R6, R0, #0		;put a copy of the inputted character in for later computations
		LD R1, PLUS_SIGN	;put the negative value of the plus sign ascii char in R1
		ADD R2, R0, R1		;check to see it the inputted character is a plus sign
		BRz OPERATOR		;plus sign detected

		LD R1, MINUS_SIGN	;put the negative value of the minus sign in R1
		ADD R2, R0, R1		;check to see if the inputted character is a minus sign
		BRz OPERATOR		;minus sign detected

		LD R1, MULT_SIGN	;load in the negative value of the asterick
		ADD R2, R0, R1		;check to see if the inputted character is an asterick
		BRz OPERATOR 		;asterick detected 

		LD R1, DIV_SIGN		;load in negative value of the division symbol
		ADD R2, R0, R1		;check to see if the inputted character is /
		BRz OPERATOR		;division sign detected

		LD R1, POW_SIGN		;load in the negative value of the power sign
		ADD R2, R0, R1		;check to see if the inputted character is a ^
		BRz OPERATOR		;^ detected

		LD R1, INVERSE_0	;put the negative value of 0 in R1
		ADD R2, R1, R0		;Check to see where our ascii character is in relation to the hex value of 0 (INPUT - '0')
		BRn CHECK_SPACE		;it is not any value over than '0'
		
		LD R1, NINE_ASCII	;Put hex value of 9 in R1
		ADD R2, R0, #0		;put value of input character in R2
		NOT R2, R2		;invert R2's value
		ADD R2, R2, #1		;get negative value of our input character 
		ADD R2, R2, R1		;check to see where our input character's hex value lies in relation to '9' ('9' - INPUT)
		BRn CHECK_SPACE		;Character has a higher hex value than '9' (is not in the range from 0-9)
		
		LD R1, INVERSE_0        ;put the negative version of '0' in R1
                ADD R0, R0, R1          ;change from the hex value of the number to its binary value
		JSR PUSH		;input character is an operand --> push to stack
		BRnzp LOAD		;go get old values back before returning from JSR EVALUATE

CHECK_SPACE	LD R1, INVERSE_SP	;get the negative value of the space ascii character
		ADD R2, R1, R0		;check to see if the input character is space
		BRz LOAD		;input character is a space character
		
THIS_INVALID	AND R5, R5, #0		;clear R5
		ADD R5, R5, #1		;invalid characters/expression detected --> cannot be used to perform a complete computation. Signal to print invalid expression 
		BRnzp LOAD		;get ready to return

OPERATOR	
		JSR POP                 ;pop first value

                ADD R5, R5, #0          ;set cc to R5
                BRp LOAD	        ;if R5 = 1 from pop --> underflow and cannot proceed
                ADD R3, R0, #0          ;put first popped value in R3

                JSR POP                 ;pop second value
                ADD R5, R5, #0          ;set cc to R5
                BRp LOAD	        ;if R5 = 1 from pop --> underflow
                ADD R4, R0, #0          ;put second popped value to R4 (in binary value)
                
		LD R1, PLUS_SIGN        ;put the negative value of the plus sign hex value in R1
                ADD R2, R6, R1          ;check to see it the inputted character is a plus sign
		BRnp SUBTRACT		;not addition, check subtraction

                JSR PLUS	        ;plus sign detected --> add values
		BRnzp PUSH_AFTER	;get ready to push value back
		
SUBTRACT        LD R1, MINUS_SIGN       ;put the negative value of the minus sign in R1
                ADD R2, R6, R1          ;check to see if the inputted character is a minus sign
		BRnp MULT		;not subtraction, check multiplication

                JSR MIN		        ;minus sign detected --> subtract values
		BRnzp PUSH_AFTER	;get ready to value back

MULT            LD R1, MULT_SIGN        ;load in the negative value of the asterick
                ADD R2, R6, R1          ;check to see if the inputted character is an asterick
		BRnp DIVISION		;not multiplication, check division

                JSR MUL		        ;asterick detected --> multiply values
		BRnzp PUSH_AFTER	;get ready to push value back

DIVISION        LD R1, DIV_SIGN         ;load in negative value of the division symbol
                ADD R2, R6, R1          ;check to see if the inputted character is /
		BRnp POWER		;not divison, go to power

                JSR DIV		        ;division sign detected --> divide values
		BRnzp PUSH_AFTER	;get ready to push value back

POWER	        JSR EXP		        ;^ detected

PUSH_AFTER	JSR PUSH		;push computed value back in stack

LOAD		LD R1, EVAL_R1		;get old value from R1
		LD R2, EVAL_R2		;get old value from R2
		LD R7, EVAL_R7          ;get old value from R7

		RET

INVERSE_SP	.FILL xFFE0
INVERSE_0	.FILL xFFD0
NINE_ASCII	.FILL x0039
	
PLUS_SIGN	.FILL xFFD5
MINUS_SIGN	.FILL xFFD3
MULT_SIGN	.FILL xFFD6
DIV_SIGN	.FILL xFFD1
POW_SIGN	.FILL xFFA2
	
EVAL_R7		.BLKW #1
EVAL_R1		.BLKW #1
EVAL_R2		.BLKW #1
EVAL_R5		.BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;output R0
PLUS	
;your code goes here
		ADD R0, R4, R3		;add two values in R3 and R4 and keep it in R0

		RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;output R0
MIN	
;your code goes here
		NOT R3, R3		;invert the bit values in R3
		ADD R3, R3, #1		;get negative value of what was in R3
		ADD R0, R4, R3		;Perform (R4 - R3) and put answer in R0

		RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;output R0
;R1 - Counts and determines how many negative numbers there are
MUL	
;your code goes here
		ST R1, MULT_R1		;save R1's old value
		AND R1, R1, #0		;clear R1
		ADD R1, R1, #-1		;set R1 to -1
		AND R0, R0, #0          ;clear R0

		ADD R3, R3, #0		;set cc to R3
		BRzp CHECK_R4		;if the value in R3 is not a negative number, go check R4
		ADD R1, R1, #1		;increment R1's value because R3 holds a negative number
CHECK_R4	ADD R4, R4, #0		;set cc to R4
		BRzp CHECK_SIGNS	;if the value in R4 is not a negative number, check total signs
		ADD R1, R1, #1		;increment R1's value (negative number in R4)

CHECK_SIGNS	ADD R1, R1, #0		;set cc to R1
		BRn MULT_LOOP		;There are two positive numbers (R1 = -1). No values need to be modified
	
		ADD R3, R3, #0		;set cc to R3
		BRzp R4_NEGATIVE	;if R3 is 0 or positive, check for the sign in R4
		NOT R3, R3		;invert R3
		ADD R3, R3, #1		;Add 1 to R3
	
		ADD R1, R1, #0		;check to see if there is only 1 negative number or two
		BRp R4_NEGATIVE		;if R1 = 1, both R3 and R4 should hold negative numbers and get a positive result
		BRnzp MULT_LOOP
R4_NEGATIVE	NOT R4, R4		;invert R4
		ADD R4, R4, #1		;Add 1 to R4
		
MULT_LOOP	ADD R0, R0, R4		;add value in R4 to R0
		ADD R3, R3, #-1		;use R3 as a counter and decrement it
		BRp MULT_LOOP		;counter has not reached 0 --> continue looping

		ADD R1, R1, #0		;check to see if the result would be positive or negative
		BRnp RETURN_MULT	;if the final result from the computation is positive, load back old values
		NOT R0, R0		;invert result
		ADD R0, R0, #1		;get negative version of result
		
RETURN_MULT	LD R1, MULT_R1		;get R1's old value back
		RET 

MULT_R1		.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;output R0
DIV	
;your code goes here
		NOT R3, R3		;invert value in R3
		ADD R3, R3, #1		;get negative value of R3
		AND R0, R0, #0		;clear R0
DIV_LOOP	ADD R4, R4, R3		;R4 - R3
		BRn OUT_LOOP		;if the value in R4 cannot be divided anymore, exit DIV
		ADD R0, R0, #1		;increment R0 --> How many times the number in R3 can go in the number in R4
		BRnzp DIV_LOOP		;repeat cycle

OUT_LOOP	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;output R0
;R1 - counts how many times we should multiply the base number by (number in the exponent)
;R2 - holds value in R4 (base number)
EXP
;your code goes here
		ST R1, SAVE_R1		;store old value of R1
		ST R2, SAVE_R2		;store old value of R2
		ST R7, SAVE_R7          ;save value of R7

		ADD R1, R3, #0		;copy value in R3 to R1
		ADD R2, R4, #0		;copy value in R4 to R2
		
		ADD R3, R4, #0		;replace value in R3 with R4
		ADD R1, R1, #-1		;decrement counter meant to count how many times we should multiply a number to itself
		
EXPONENT_LOOP	JSR MUL			;go multiply the base number with itself

		ADD R4, R0, #0		;move answer from R0 to R4
		ADD R3, R2, #0		;reset so we are multiplying by the base number
		ADD R1, R1, #-1		;decrement counter
		BRp EXPONENT_LOOP	;continue until exponent operation is complete

		LD R1, SAVE_R1		;get R1 value back
		LD R2, SAVE_R2		;get R2 value back
		LD R7, SAVE_R7          ;get R7 value back

		RET

SAVE_R1		.BLKW #1
SAVE_R2		.BLKW #1
SAVE_R7		.BLKW #1
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
