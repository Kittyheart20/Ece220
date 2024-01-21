;R0 = what will be put out to the monitor
;R1 = counter value (4) for looping one section of 4 in the bit pattern
;R2 = counter value (4) for looping through all the sections of 4 in the bit pattern
;R3 = holds hexadecimal bit pattern
;R4 = changes value into correct ASCII character


		.ORIG x3000		;write your code here
	
		LD R2, FOUR		;initialize R2 to 4
NEXT_HEX	LD R1, FOUR		;initialize R1 to 4
		AND R0, R0, #0		;initialize r0 to 0
	
ONE_HEX		ADD R0, R0, R0		;makes space for new bit value. This new bit
					;value will be the MSB of the bit pattern in R3
		ADD R3, R3, #0		;set cc value to R3's value
		BRzp SHIFT		;branches if the MSB of R3 is 0
		ADD R0, R0, #1		;if the MSB of R3 is 1, we add a 1 to update
					;the bit value in R0
SHIFT		ADD R3, R3, R3		;shift out the MSB of R3
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

		HALT
	
FOUR		.FILL x0004
TO_NUM		.FILL x0039
TO_LET		.FILL x0040

		

		.END
