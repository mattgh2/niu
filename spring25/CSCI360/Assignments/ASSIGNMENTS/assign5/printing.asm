//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H
//JSTEP01  EXEC PGM=ASSIST
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSIN    DD *
MAIN     CSECT
         USING MAIN,15      ESTABLISHING ADDRESSABILITY ON REG 15
         LA    2,12        LOAD NUM1 INTO R2
         LA    3,10        LOAD NUM2 INTO R3
         AR    2,3           ADD CONTENTS OF REG 3 TO 2
         XDECO 2,ONUM1
         XPRNT PRNTLINE,133
         BCR   B'1111',14    RETURN TO CALLER
         LTORG
PRNTLINE DC    C' '
         DC    CL17'NUM1 IS EQUAL TO '
ONUM1    DS    CL12
         DC    103C' '
/* 
//

