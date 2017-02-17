	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0, =NUM1
	LDR R1, =NUM2
	LDR R0, [R0]
	LDR R1, [R1]
	LDR R2, =0X20000000
	MSR XPSR, R2
	MOV R2, #0
	SUBS R2, R0, R1
	LDR R3, =DIFF
	STR R2, [R3]
STOP B STOP

NUM1 dcd 0X87654321
NUM2 dcd 0X11111111
	AREA mydata, DATA, READWRITE
DIFF dcd 0
	END