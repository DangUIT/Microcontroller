.MODEL SMALL
.STACK 100H
.DATA
STR1 DB "A=   $"
STR2 DB 10,13, "B=   $"
STR3 DB 10,13, "A-B= $"  
STR4 DB "Overflow $"
.CODE  
MAIN:           
    MOV AX, @DATA
    MOV DS, AX      
    MOV DX, OFFSET STR1 
    MOV AH, 9
    INT 21H 
    CALL INPUT 
    PUSH BX
    CALL INPUT
    PUSH BX 
    MOV DX, OFFSET STR2
    MOV AH, 9
    INT 21H 
    CALL INPUT 
    PUSH BX
    CALL INPUT
    PUSH BX      
    MOV DX, OFFSET STR3
    MOV AH, 9
    INT 21H  
    POP DX
    POP CX
    POP BX
    POP AX
    SUB BX,DX
    PUSH BX   
    JC CARRY 
    JMP NOT_CARRY  
CARRY:
    ADD CX,1
    JC CARRY2
    JMP NOT_CARRY 
NOT_CARRY:    
    SUB AX,CX
    JC CARRY2  
    PUSH AX
    POP BX
    CALL PRINT
    POP BX
    CALL PRINT
    JMP EXIT
CARRY2:
    MOV AX, @DATA
    MOV DS, AX      
    MOV DX, OFFSET STR4 
    MOV AH, 9
    INT 21H
    JMP EXIT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
INPUT PROC 
    MOV CX, 16
    MOV BX, 0
INPUT1:
    MOV AH, 1
    INT 21H
    SUB AL, 30H
    MOV AH, 0
    PUSH AX
    MOV AX, 2
    MUL BX
    MOV BX, AX
    POP AX
    ADD BX, AX
    LOOP INPUT1     
    RET
INPUT ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRINT PROC  
    MOV CX,16
PRINT1: 
    MOV AH, 2
    MOV DL, '0'
    TEST BX,8000H
    JZ ZERO
    MOV DL, '1'
ZERO:  
    INT 21H
    SHL BX, 1
LOOP PRINT1
RET
PRINT ENDP   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;      
EXIT:
END