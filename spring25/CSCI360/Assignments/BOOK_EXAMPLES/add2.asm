//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H
//JSTEP01  EXEC PGM=ASSIST
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSIN    DD *
*
ADD2     CSECT
         USING ADD2,15
         L     1,16(,15)          LOAD THE FIRST NUMBER INTO R1
         L     2,20(,15)          LOAD THE FIRST NUMBER INTO R1
         AR    1,2          LOAD THE SECOND NUMBER INTO R2
         ST    1,24(,15)          
*
*
         LTORG
         DC    F'4'
         DC    F'6'
         DS    F
         END ADD2
/* 
//
