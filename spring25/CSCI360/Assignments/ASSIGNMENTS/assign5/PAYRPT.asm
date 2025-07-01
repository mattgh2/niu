//KC03AEDA JOB ,'M. Warner',MSGCLASS=H
//*
//JSTEP01  EXEC PGM=ASSIST
//*
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//*
//SYSIN    DD *
***************************************************************** 
*                                                               * 
*  CSCI 360-1             ASSIGNMENT 5        SPRING 2025       * 
*                                                               * 
*    PROGRAMMER NAME: Matthew Warner                            * 
*           DATE DUE: March 6, 2025                             * 
*                                                               * 
*  MAIN PROGRAM NAME: PAYRPT                                    *
*                                                               *
*           FUNCTION: The function of this program is to        *
*                     calculate payroll for a business          *
*                                                               * 
*****************************************************************
* 
PAYRPT   CSECT
         USING PAYRPT,15      ESTABLISH ADDRESSABILITY ON REG 15
*                                  
         LA    10,16          GET FED WITHHOLDING PERCENT INTO R10
         LA    11,4           GET STATE WITHHOLDING PERCENT INTO R11
*
         XREAD RECORD,80      GET FIRST EMPLOYEE RECORD
*
LOOP     BC   B'0100',ENDLOOP BRANCH TO ENDLOOP1 IF END-OF-FILE (EOF)
*
*  HERE IS WHERE THE BODY OF YOUR LOOP WILL BE CODED
*
         MVC  OEMPNME(25),RECORD  GET EMPLOYEE NAME
         MVC  OEMPID(5),RECORD+30 GET EMPLOYEE ID
*
         XDECI 2,RECORD+36        GET PAY RATE
         XDECO 2,OPAYRATE         DISPLAY PAY RATE
         XDECI 3,0(,1)            GET HOURS
         XDECO 3,OHOURS           DISPLAY HOURS
*
         MR    2,2                PAY RATE * HOURS (PRODUCT IN R3)
*
         XDECI 2,0(,1)            GET DEDUCTIONS
         SR    3,2                SUBTRACT FROM PAY
         XDECI 2,0(,1)            GET BONUS
         AR    3,2                ADD TO PAY
         XDECO 3,OGROSS           DISPLAY GROSS PAY AMOUNT
*
         LR    7,3                LOAD GROSS PAY INTO R7
         LR    8,7                LOAD GROSS PAY INTO R8
         LA    4,100              LOAD 100 INTO R4 
*
         MR    2,10               GROSS PAY AMOUNT * FED WITHHOLDING %
         DR    2,4                DIVIDE (GROSS PAY * FED WH) BY 100
         XDECO 3,OFEDWH           DISPLAY FED WITHHOLDING AMT
         MR    6,11               MULTIPLY (GROSS PAY * STATE WH %)
         DR    6,4                DIVIDE (GROSS PAY * STATE WH %) / 100
         XDECO 7,OSTWH            DISPLAY STATE WITHHOLDING AMT
         SR    8,3                (GROSS PAY - FED WH)
         SR    8,7                (GROSS PAY - FED WH) - STATE WH
         XDECO 8,ONETPAY          DISPLAY NET PAY
*
         XPRNT DETAIL,133     PRINT THE EMPLOYEE DETAIL RECORD
*
         XREAD RECORD,80      READ NEXT EMPLOYEE RECORD
*
         BC    B'1111',LOOP   BRANCH TO TOP OF LOOP1 TO CHECK EOF
*
ENDLOOP  DS    0H    
*
         BCR   B'1111',14     UNCONDITIONAL RETURN TO CALLER
*
         LTORG                LITERAL ORGANIZATION
*
* THE FOLLOWING 16 LINES ARE THE DEFINITION FOR THE OUTPUT DETAIL
*   LINE FOR EACH EMPLOYEE FOR THE REPORT YOU ARE CREATING.  IT 
*   IS EXACTLY 133 BYTES LONG.  EACH OUTPUT FIELD IS SEPARATED 
*   BY 4 OR 5 BYTES OF EBCDIC SPACES, i.e., X'40'.
*
DETAIL   DC    C'0'   CARRIAGE CONTROL CHARACTER
OEMPID   DS    CL5    OUTPUT FIELD FOR EMPLOYEE ID
         DC    4C' '  SPACES
OEMPNME  DS    CL25   OUTPUT FIELD FOR EMPLOYEE NAME
         DC    4C' '  SPACES
OPAYRATE DS    CL12   OUTPUT FIELD FOR XDECO OF PAY RATE
         DC    4C' '  SPACES
OHOURS   DS    CL12   OUTPUT FIELD FOR XDECO OF HOURS WORKED
         DC    4C' '  SPACES
OGROSS   DS    CL12   OUTPUT FIELD FOR XDECO OF GROSS PAY AMT
         DC    4C' '  SPACES
OFEDWH   DS    CL12   OUTPUT FIELD FOR XDECO OF FEDERAL WH AMT
         DC    5C' '  SPACES
OSTWH    DS    CL12   OUTPUT FIELD FOR XDECO OF STATE WH AMT
         DC    5C' '  SPACES
ONETPAY  DS    CL12   OUTPUT FIELD FOR XDECO OF NET PAY AMT
*
*  THE FOLLOWING IS THE BUFFER FOR THE INPUT RECORD
*
RECORD   DS    CL80   BUFFER FOR EMPLOYEE RECORD READ FROM INPUT FILE
*
         END   PAYRPT
/*
//*
//* THE FOLLOWING IS THE INPUT DATA SET
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATAFA24(DATA5),DISP=SHR
//*
//* THE FOLLOWING IS THE OUTPUT DATA SET
//*
//FT06F001 DD SYSOUT=*
//*
//SYSPRINT DD SYSOUT=*
//*
//
