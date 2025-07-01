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
         USING PAYRPT,15     
*
         LA    10,16              
         LA    11,4               
         XREAD RECORD,80        
LOOP     BC   B'0100',ENDLOOP 
*
         MVC  OEMPNME(25),RECORD  
         MVC  OEMPID(5),RECORD+30
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
         LR    7,3
         LR    8,7
         MR    2,10               GROSS PAY AMOUNT * FED WITHHOLDING %
         LA    4,100
         DR    2,4
         XDECO 3,OFEDWH
         MR    6,11
         DR    6,4
         XDECO 7,OSTWH
         SR    8,3
         SR    8,7
         XDECO 8,ONETPAY
*
         XPRNT DETAIL,133         PRINT THE EMPLOYEE DETAIL RECORD
         XREAD RECORD,80          READ NEXT EMPLOYEE RECORD
         BC    B'1111',LOOP       BRANCH TO TOP OF LOOP1 TO CHECK EOF
*
ENDLOOP  DS    0H    
         BCR   B'1111',14     UNCONDITIONAL RETURN TO CALLER
*
*
         LTORG                
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
