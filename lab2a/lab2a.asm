.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.

;R0 = input characters
;R1 = stack top address
;R2 = stack start address
;R5 = output (1 if it is balanced and -1 if it is not)
;R6 = register meant for computations 



		AND R5, R5, #0		;initialize R5 to 0
REPEAT		ADD R5, R5, #0		;set cc to R5
		BRn STOP		;if R5 = -1 from push/pop subroutines (overflow/underflow), then stop
		IN			;get the next input character

		LD R6, CHAR_RETURN	;load in return char
		NOT R6, R6
		ADD R6, R6, #1		;get additive inverse
		ADD R6, R6, R0		;check to see if inputted character is a new line character

		BRz CHECK_BALANCE	;return character detected. Check to see if there is an even amount of closed and open parentheses
		JSR IS_BALANCED		;if return character is not there, go push/pop the character
		BRnzp REPEAT		;get the next inputted character

CHECK_BALANCE	LD R1, STACK_TOP	;get address of where are top stack is at
		LD R2, STACK_START	;get address of where the stack starts at
		
		NOT R1, R1		
		ADD R1, R1, #1		;get additive inverse of the top address
		AND R5, R5, #0		;clear R5

		ADD R1, R1, R2		;check to see if the start address is the same as the top address
		BRz EVEN		;start address = top address
		ADD R5, R5, #-1		;Start address does not equal top address --> unbalanced
		BRnzp DONE
EVEN		ADD R5, R5, #1		;start address does equal top address --> balanced

STOP		HALT
 
SPACE	        .FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
INVERSE_NL	.FILL xFFF6

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.
;R1 (only for subroutine) = work register meant for computations

IS_BALANCED
		ST R7, SAVE_R7		;save address for JSR	
		ST R1, Save_R1		;save value in R1 before using the register
		AND R1, R1, #0		;clear R1 to 0

		LD R1, NEG_OPEN		;put the negative value of ( in the register
		ADD R1, R1, R0		;check if the inputted chracter is (
		BRz IS_OPEN		;inputted character is (

		LD R1, NEG_CLOSE	;put the negative value of ) in the register
		ADD R1, R1, R0		;check to see if inputted character is )
		BRz IS_CLOSE		;inputted character is )	
		
		BRnzp RETURN		;go get stored values back

IS_OPEN		JSR PUSH		;go push ( to stack
		BRnzp RETURN		;go get stored values back

IS_CLOSE	JSR POP			;pop the stack because of )
		ADD R5, R5, #0		;set cc to R5
		BRz RETURN		;R5 = 0 from the pop routine --> no underflow
		LD R5, NEGATIVE_ONE	;R5 = 1 from pop routine --> overflow. Therefore set R5 = -1 to show it is unbalanced

		BRnzp RETURN		;go back and retrieve old data
RETURN          LD R7, SAVE_R7          ;retrieve stored data from R7
                LD R1, SAVE_R1          ;retrieve stored data from R7

                RET
	

NEGATIVE_ONE	 .FILL xFFFF
NEG_OPEN	 .FILL xFFD8
NEG_CLOSE 	 .FILL xFFD7
SAVE_R7		 .BLKW #1
SAVE_R1		 .BLKW #1
SAVE_R5		 .BLKW #1
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
        AND R5, R5, #0          ;initialize R5 to 0
        LD R3, STACK_END        ;gets the address of the last slot in stack
        LD R4, STACk_TOP        ;gets the address of the current slot labelled "TOP"
        ADD R3, R3, #-1         ;move address up one slot in stack (address for out of stack bounds)
        NOT R3, R3              ;
        ADD R3, R3, #1          ;get the additive inverse of the incremented slot address
        ADD R3, R3, R4          ;add additive inverse to the current stack address position
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;update our output to 1, indicating that there is an overflow
DONE_PUSH
        LD R3, PUSH_SaveR3      ;load in the value previously saved in R3 back into this register
        LD R4, PUSH_SaveR4      ;load in the value previously saved in R4 back into this register
        RET


PUSH_SaveR3     .BLKW #1        ;reserve a space to store the number in R3
PUSH_SaveR4     .BLKW #1        ;Reserve a space to store 

;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;load in the address of the start of the stack
        LD R4, STACK_TOP        ;load in the address of where we are currently at for the top of the stack
        NOT R3, R3              ;
        ADD R3, R3, #1          ;get the additive inverse of the start address of the stack
        ADD R3, R3, R4          ;top - start of stack
        BRz UNDERFLOW           ;if the top of the stack is at the start already, then popping again will go into underflow
        ADD R4, R4, #1          ;If the top of the stack is not at the start, move the pointer for the top slot in the stack down
        LDR R0, R4, #0          ;Put the data located at that stack location and put it in R0
        ST R4, STACK_TOP        ;Store the new value of where the the top of the stack is
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;R5 = 1 if there is an underflow
DONE_POP
        LD R3, POP_SaveR3       ;get the value back of what was originally in R3
        LD R4, POP_SaveR4       ;get the value of what was originally in R4 back
        RET


POP_SaveR3      .BLKW #1        ;make memory location to save value in R3 before pop/push
POP_SaveR4      .BLKW #1        ;make memory location to save value in R4 before push/pop
STACK_END       .FILL x3FF0     ;address of where the end of the stack is at
STACK_START     .FILL x4000     ;address of where the start of the stack is at

STACK_TOP       .FILL x4000     ;where the top of the stack was originally when it started

.END

