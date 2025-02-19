//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H 
//JSTEP01  EXEC PGM=ASSIST 
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR 
//SYSPRINT DD SYSOUT=* 
//SYSIN    DD * 
***************************************************************** 
*                                                               * 
*  CSCI 360-1             ASSIGNMENT 1        SPRING 2025       * 
*                                                               * 
*    PROGRAMMER NAME: Matthew Warner                            * 
*           DATE DUE: January 24, 2025                          * 
*                                                               * 
*  MAIN PROGRAM NAME: PROGRAM1                                  *
*                                                               *
*           FUNCTION: The function of this program is to        * 
*                     provide an example of a simple ASSIST     * 
*                     Assembler program and documentation.      * 
*                                                               * 
*****************************************************************
*
PROGRAM1 CSECT
         USING PROGRAM1,15 ESTABLISH ADDRESSABILITY ON REG 15 
         LA    4,13        LOAD 13 INTO REG 4 
         LA    8,6         LOAD 6 INTO REG 8 
         AR    4,8         ADD REG 8'S CONTENTS TO REG 4'S 
         XDUMP ,           DUMP CONTENTS OF ALL 16 REGS 
         BCR   B'1111',14  UNCONDITIONAL RETURN TO CALLER (OS) 
* 
         LTORG             LITERAL ORGANIZATION 
* 
         END   PROGRAM1 
/* 
//
