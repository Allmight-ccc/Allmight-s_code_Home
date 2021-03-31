DATA SEGMENT
    DATA1 DB 32h, 29h, 30, 35h, 34h
    DATA2 DB 34h

    MES1 DB '*','$'
    MES2 DB '=','$'

    RESULT DB 6 DUP (00h)
DATA ENDS

STACK SEGMENT
    STA DB 20 DUP (?)
    TOP EQU LENGTH STA
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK, ES:DATA
    START:  MOV AX, DATA
            MOV DS, AX
            MOV AX, STACK
            MOV SS, AX
            MOV SP, TOP
            ; MOV SP, 250H
            LEA SI, DATA1
            MOV BX, 05H
        L1: MOV AH, 02H
            MOV DL, [SI+BX-1]
            INT 21H
            DEC BX
            JNZ L1
            MOV AH, 09H
            LEA DX, MES1
            INT 21H
            LEA SI, DATA2
            MOV AH, 02H
            MOV DL, [SI]
            INT 21H
            MOV AH, 09H
            LEA DX, MES2
            INT 21H
            MOV SI, OFFSET DATA2
            MOV BL, [SI]
            AND BL, 00001111B
            MOV SI, OFFSET DATA1
            MOV DI, OFFSET RESULT
            MOV CX, 05
    LOOP1:  MOV AL, [SI]
            AND AL, 00001111B
            INC SI
            MUL BL
            AAM
            ADD AL, [DI]
            AAA
            MOV [DI], AL
            INC DI
            MOV [DI], AH
            LOOP LOOP1
            MOV CX, 06
            MOV SI, DI
    DISPL:  MOV AH, 02
            MOV DL, [SI]
            ADD DL, 30H
            INT 21H
            DEC SI
            LOOP DISPL
            MOV AX, 4C00H
            INT 21H
CODE ENDS
     END START