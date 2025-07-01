//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H
//JSTEP01  EXEC PGM=ASSIST
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSIN    DD *
*
*****************************************************************
*                                                               *
*  CSCI 360-1             ASSIGNMENT 6               SPRING 2025*
*                                                               *
*  PROGRAMMER NAME: Matt Warner                                 *
*        DUE DATE: March 22, 2025                               *
*                                                               *
*  NO FURTHER DOCUMENTATION IS NECESSARY                        *
*                                                               *
***************************************************************** 
* 
DISASM   CSECT 
         USING DISASM,15   ESTABLISH ADDRESSABILITY ON REG 15 
* 
         LA    4,23        LOAD VALUE 17 INTO R4.
         L     5,60(,15)   LOAD VALUE AT ADDRESS 0x00003C INTO R5.
         LR    2,4         LOAD R4 INTO R2.
         AR    2,5         ADD R5 TO R2.
         ST    2,64(,15)   STORE CONTENTS OF R2 INTO ADDRESS 0x000040.
         LR    7,5         LOAD R5 INTO R7.
         LR    6,4         LOAD R4 INTO R6
         MR    6,6         MULTIPLY R6 BY R7, PROD STORED IN R7.
         ST    7,68(,15)   STORE R7 IN ADDRESS 0x000044.
         LR    9,4         LOAD R4 INTO R9.
         M     4,80(,15)   MULTIPLY R5 BY VALUE AT ADDRESS 0x000050.
         DR    4,9         DIVIDE R5 BY R9.
         ST    4,72(,15)   STORE R4 IN ADDRESS 0x000048.
         ST    5,76(,15)   STORE R5 IN ADDRESS 0x00004C.
         XDUMP DISASM,84   MEMORY DUMP.
         BCR   B'1111',14  UNCONDITION RETURN TO CALLER.
* 
         LTORG             LITERAL ORGANIZATION 
         DS    CL4
         DC    F'101'
         DS    F
         DS    F
         DS    F
         DS    F
         DC    F'1'
* 
         END   DISASM 
/* 
//
