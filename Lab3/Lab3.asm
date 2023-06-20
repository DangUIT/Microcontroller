ORG 0000H
LJMP MAIN
//////Ngat ngoai 0///////
ORG 0003H
LJMP PAUSE
/////Ngat ngoai 1////////
ORG 0013H
LJMP RESET
////Chuong trinh chinh///
ORG 0030H
MAIN:
SETB P3.0
MOV R1,#0; GIAY
MOV R2,#0; %GIAY
MOV IE,#85H
CLR IT0
CALL CLOCK
JMP MAIN
/////Ham thoi gian dong ho////////
CLOCK:	/////Ham tang 1
JB P0.0,DEC_1
JNB P0.0,$
INC R1
CJNE R1,#100,DEC_1
MOV R1,#0
///////Ham giam 1
DEC_1:
JB P0.1,CLOCK_1
JNB P0.1,$
DEC R1
CJNE R1,#-1,CLOCK_1
MOV R1,#99
////////Ham xu li thoi gian dong ho//////
CLOCK_1:
CALL HIENTHI
JNB P3.0,CLOCK
INC R2
CJNE R2,#100,CLOCK
INC R1
MOV R2,#0
CJNE R1,#100,CLOCK
MOV R1,#0
JMP CLOCK
/////Ham hien thi thoi gian/////////
HIENTHI:
MOV A,R1
MOV B,#10
DIV AB
MOV P1,#01H
MOV P2,A
CALL DELAY
MOV P1,#02H
MOV P2,B
CALL DELAY
MOV A,R2
MOV B,#10
DIV AB
MOV P1,#04H
MOV P2,A
CALL DELAY
MOV P1,#08H
MOV P2,B
CALL DELAY
RET
////Ham pause,resume/////////
PAUSE:
JNB P3.2,$ 
CPL P3.0
RETI
/////////Ham reset///////////
RESET:
MOV R1,#0; GIAY
MOV R2,#0; %GIAY
RETI
////////Delay bang vong lap////////
;DELAY:
;MOV R6,#245
;MOV R7,#5
;LOOP1: DJNZ R6,$
;LOOP2: DJNZ R7,LOOP1
;RET
////////////Delay bang timer/////////
DELAY:
MOV TMOD,#01H
MOV TH0,#HIGH(-2500)
MOV TL0,#LOW(-2500)
SETB TR0
JNB TF0,$
CLR TF0
CLR TR0
RET
/////Ket thuc chuong trinh//////////////
END

