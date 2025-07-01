//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H
//JSTEP01  EXEC PGM=ASSIST
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSIN    DD *
***************************************************************** 
*                                                               * 
*  CSCI 360-1             ASSIGNMENT 7        SPRING 2025       * 
*                                                               * 
*    PROGRAMMER NAME: Matthew Warner                            * 
*           DATE DUE: APRIL 1, 2025                             * 
*                                                               * 
*  MAIN PROGRAM NAME: PAYROLL                                   *
*                                                               *
*           FUNCTION: The function of this program is to        *
*                                                               * 
*                                                               * 
*****************************************************************
* 
PAYROLL  CSECT
*
*  STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)  SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15         COPY CSECT ADDR INTO R12
         USING PAYROLL,12    ESTABLISH R12 AS THE BASE REG
         LA    14,SAVEAREA   R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)     STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)     STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14         POINT R13 AT THIS CSECT'S SAVE AREA
*
*
         XREAD RECORD,80       PRIMARY READ INTO RECORD
*
LOOP     BC    B'0100',ENDLOOP EXEC LOOP IF SUCCESSFUL READ
*
         MVI   DETAIL+1,C' '   COPY WHITESPACE INTO 1ST BYTE OF PRINTLN
         MVC   DETAIL+2(131),DETAIL+1  COPY WHTESPCE TO REMAINING BYTES
*
         MVC   OEMPNME(25),IEMPNME    MOVE EMPLOYEE NAME INTO PRNT LINE
         MVC   OEMPID(6),IEMPID       MOVE EMPLOYEE ID INTO PRINT LINE
* 
         PACK  PHRPAY(3),IHRPAY(5)    GET PACKED DECMIAL FORM OF HR PAY
         LA    1,OHRPAY+3             ENSURE R1 HOLDS A BYTE FOR '$'
         MVC   OHRPAY(7),=X'402021204B2020' MOVE EDIT PATTERN TO OHRPAY
         EDMK  OHRPAY(7),PHRPAY    PUTS EBCDIC HRPAY INTO PRINT LINE
         BCTR  1,0    DECREMENT R1 BY 1
         MVI   0(1),C'$'   PLACE DOLLAR SIGN
*
         PACK  PHOUR(3),IHOURS(5)    GET PACKED DECIMAL FORM OF HOURS
         MVC   OHOURS(7),=X'402021204B2020' MOVE EDIT PATTERN TO PRNTLN
         ED    OHOURS(7),PHOUR    PUT EBCDIC HOURS INTO PRINT LINE
*
         ZAP   PGRPAY(6),PHRPAY(3)    PREPARES FOR MULTIPLICATION
         MP    PGRPAY(6),PHOUR(3) MULTIPLY PACKED HRPAY BY PACKED HOURS
         SRP   PGRPAY(6),64-2,5   SHIFT 2 TO THE RIGHT AND ROUND
         LA    1,OGRPAY+8         ENSURE R1 HOLDS SLOT FOR '$'
         MVC   OGRPAY(15),=X'402020202020206B2021204B2020' EDIT PATTERN
         EDMK  OGRPAY(15),PGRPAY    PUT PACKED GROSS PAY TO PRINT LINE
         BCTR  1,0     DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
         XPRNT DETAIL,133    PRINT DETAIL LINE FOR EMPLOYEE
         XREAD RECORD,80     SECONDARY READ INTO RECORD
         BC    B'1111',LOOP  BRANCH BACK TO THE TOP OF LOOP
*
ENDLOOP  DS    0H   
*  STANDARD EXIT LINKAGE WITH RC OF 0
*
         SR    15,15         R15 = RETURN CODE OF 0
         L     13,4(,13)     POINTS R13 TO CALLER'S SAVE AREA
         L     14,12(,13)    RESTORE REGISTER 14
         LM    0,12,20(13)   RESTORE R0 THRU R12
*
         BR    14            RETURN TO CALLER
*
         LTORG
*
         ORG   PAYROLL+((*-PAYROLL+31)/32)*32
         DC    C'* PROGRAM STORAGE FOR PAYROLL **'
*
SAVEAREA DS    18F    REGISTER SAVE AREA
*
DETAIL   DC    C'0'   CARRIAGE CONTROL CHARACTER
OEMPNME  DS    CL25
         DC    4C' '
OEMPID   DS    CL6
         DC    4C' '
OHRPAY   DS    CL7
         DC    4C' '
OHOURS   DS    CL5
         DC    4C' '
OGRPAY   DS    CL15
         DC    58C' '
*
RECORD   DS    0H     INPUT RECORD STORAGE
IEMPNME  DS    CL25
IEMPID   DS    CL6
IHRPAY   DS    ZL5
IHOURS   DS    ZL5
         DC    39C' '
* 
PHRPAY   DC    PL3'0'
PHOUR    DC    PL3'0'
PGRPAY   DC    PL6'0'
*
         END PAYROLL
/* 
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATASP25(DATA7),DISP=SHR
//*
//FT06F001 DD SYSOUT=*
//
