//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H
//JSTEP01  EXEC PGM=ASSIST
//STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSIN    DD *
***************************************************************** 
*                                                               * 
*  CSCI 360-1             ASSIGNMENT 10        SPRING 2025      * 
*                                                               * 
*    PROGRAMMER NAME: Matthew Warner                            * 
*           DATE DUE: May 2, 2025                               *
*                                                               * 
*    *  MAIN PROGRAM NAME: PAYROLL                              *
*                                                               *
*           FUNCTION: The function of this program is to        *
*                      product a payroll report for a company   *
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
         LA    11,4095(,12)  POINT R11 4095 BYTES BEYOND R12
         LA    11,1(,11)        POINT R11 4096 BYTES BEYOND R12
         USING PAYROLL+4096,11 ESTABLISH R11 AS SECOND BASE REG
* 
*** CALL TO BUILDTBL TO BUILD TABLE ***
*
         LA    1,BTPARMS   POINT R1 TO THE PARM LIST FOR BUILDTBL
         L     15,=V(BUILDTBL)  PUT THE ADDRESS OF BUILDTBL INTO R15
*
         BALR  14,15  STORE THE ADDRESS OF THE NEXT INSTRUCTION
*                      IN R14 AND BRANCH TO BUILDTBL
*
*** CALL TO PROCTBL TO PROCESS EMPLOYEE DATA IN TABLE ***
*
         LA    1,PTPARMS   POINT R1 TO THE PARM LIST FOR PROCTBL
         L     15,=V(PROCTBL)  PUT THE ADDRESS OF PROCTBL INTO R15
*
         BALR  14,15  STORE THE ADDRESS OF THE NEXT INSTRUCTION
*                      IN R14 AND BRANCH TO PROCTBL
*
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
EMPTBL   DS    120CL42  EMPLOYEE TABLE
*
PFWHPCT  DC    PL4'0' PACKED FEDERAL WITHHOLDING PERCENTAGE
PSWHPCT  DC    PL4'0' PACKED STATE WITHHOLDING PERCENTAGE
PEMPCTR  DC    PL3'0' PACKED EMPLOYEE COUNTER (MAX 999)
*
BTPARMS  DC    A(EMPTBL)
         DC    A(PEMPCTR)
         DC    A(PFWHPCT)
         DC    A(PSWHPCT)
*
PTPARMS  DC    A(EMPTBL)
         DC    A(PEMPCTR)
         DC    A(PFWHPCT)
         DC    A(PSWHPCT)
*
*
*        END   PAYROLL 
*
*****************************************************************
*                                                               *
*   SUBPROGRAM NAME: BUILDTBL                                   *
*                                                               *
*          FUNCTION: Reads input from a file containing         *
*                     employee information and stores the       *
*                     information in a table                    *
*                                                               *
*         PARAMETERS:  EMPTBL                                   *
*                      PEMPCTR                                  *
*                      PFWHPCT                                  *
*                      PSWHPCT                                  *
*                                                               *
*                                                               *
*****************************************************************
*
$TEMPENT DSECT
$TEMPID  DS    PL5
$TEMPNME DS    CL25
$THRPAY  DS    PL3
$THOURS  DS    PL3
$TDEDUCT DS    PL3
$TBONUS  DS    PL3
*
BUILDTBL CSECT
*
*  STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)  SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15         COPY CSECT ADDR INTO R12
         USING BUILDTBL,12    ESTABLISH R12 AS THE BASE REG
         LA    14,TBLSAVE   R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)     STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)     STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14         POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,5,0(1)    R2 -> EMPTBL -- 120x42
*                          R3 -> PEMPCTR -- L3
*                          R4 -> PFWHPCT -- L4
*                          R5 -> PSWHPCT -- L4
*
         LA    6,0(,2)      LOAD ADDR OF EMPTBLE INTO R6
         USING $TEMPENT,6  EST ADDRESSABLITY ON R6
*
         XREAD IWTHPCT,80   READ FED AND STATE PERCENTAGES
         BC    B'0100',ENDBUILD BRANCh TO END IF EMPTY FILE
*
         PACK  0(4,4),IFPCT(6) PACK ZONED FED PERCENTAGE
         PACK  0(4,5),ISPCT(6) PACK ZONED STATE PERCENTAGE
*
         XREAD RECORD,80    READ RECORD INTO BUFFER
TBLLOOP  BC    B'0100',ENDBUILD  BRANCH TO END IF EMPTY FILE
*
         PACK  $TEMPID(5),IEMPID(8)   PACK ZONED EMPID
         PACK  $THRPAY(3),IHRPAY(5) PACK HRPAY
         PACK  $THOURS(3),IHOURS(5)  PACK HOURS
         PACK  $TBONUS(3),IBONUS(5)   PACK BONUS AMOUNT
         PACK  $TDEDUCT(3),IDEDUCT(5) PACK DEDUCTION AMOUNT
         MVC   $TEMPNME(25),IEMPNME  MOVE EMPLOYEE NAME TO TABLE ENTRY
*
         AP    0(3,3),=PL1'1'   ADD ONE TO EMP COUNTER
         LA    6,42(,6)         MOVE TO NEXT ENTRY IN TABLE
*
         XREAD RECORD,80        READ FROM RECORD
         BC    B'1111',TBLLOOP  BRANCH BACK TO TOP OF LOOP
*
ENDBUILD DS    0H
         DROP  6
*
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
         ORG   BUILDTBL+((*-BUILDTBL+31)/32)*32
         DC    C'* PROGRAM STORAGE FOR BUILDTBL **'
*
TBLSAVE DS     18F    REGISTER SAVE AREA
*
* INPUT RECORD VARIABLES
*
RECORD   DS    0H 
IEMPID   DS    ZL8
IHRPAY   DS    ZL5
IHOURS   DS    ZL5
IDEDUCT  DS    ZL5
IBONUS   DS    ZL5
IEMPNME  DS    CL25
         DS    CL27
*
IWTHPCT  DS    0H
IFPCT    DS    ZL6
ISPCT    DS    ZL6
         DC    68C' '
*
*****************************************************************
*                                                               *
*   SUBPROGRAM NAME: PROCTBL                                    *
*                                                               *
*          FUNCTION: Processes the employee data stored in the  *
*                     table that is constructed with the        *
*                    BUILDTBL subprogram                        *
*                                                               *
*         PARAMETERS:   EMPTBL                                  *
*                        PEMPCTR                                *
*                        PFWHPCT                                *
*                        PSWHPCT                                *
*                                                               *
*                                                               *
*****************************************************************
$EMPENT DSECT
$EMPID  DS    PL5
$EMPNME DS    CL25
$HRPAY  DS    PL3
$HOURS  DS    PL3
$DEDUCT DS    PL3
$BONUS  DS    PL3
PROCTBL CSECT
*
*  STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)  SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15         COPY CSECT ADDR INTO R12
         USING PROCTBL,12    ESTABLISH R12 AS THE BASE REG
         LA    14,PROCSAVE   R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)     STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)     STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14         POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,5,0(1)   R2 -> EMPTBL
*                         R3 -> PEMPCTR(3)
*                         R4 -> PFWHPCT(4)
*                         R5 -> PSWHPCT(4)
*
         LA    6,0(,2)     LOAD ADDR OF TABLE IN R6
         USING $EMPENT,6  EST ADDRESSABLITY ON R6
*
         ST    4,CNPPARMS+4  PUT ADDR OF PFWHPCT IN NET PAY PARM LIST
         ST    5,CNPPARMS+12 PUT ADDR OF PSWHPCT IN NET PAY PARM LIST
         ST    3,CAPARMS+4   PUT ADDR OF EMPCOUNT IN AVG PARM LIST
*
         ZAP   PECOUNT(3),0(3,3)   STORE A COPY OF PEMPCTR IN STORAGE
*                                   FOR NON ZERO COUNT LOOP CONDITION
*
         LA    8,99   INITIALIZE R5 TO 99 FOR PAGINATION
*
*
         CP    PECOUNT(3),=PL1'0'     CHECK IF EMPCOUNT IS NON ZERO
PROCREC  BC    B'1000',ENDPROC   BRANCH PAST IF EMP COUNTER IS ZERO
*
         MVI   EMPDTL+1,C' '      CLEAR 1ST BYTE OF PRINT LINE
         MVC   EMPDTL+2(131),EMPDTL+1  CLEAR OUT REMANING BYTES
*
         MVC   IDPTRN(10),=X'21202060202020202020' CREATE EDIT PATTERN
         ED    IDPTRN(10),$EMPID    PUT PACKED EMP ID INTO OUTPUT
         MVC   OEMPID(9),IDPTRN+1   GETS RID OF THE LEADING ZERO
* 
         MVC   OEMPNME(25),$EMPNME  MOVE EMPLOYEE NAME TO DETAIL LINE
*
         LA    1,OHRPAY+3          ENSURES PLACEMENT OF DOLLAR SIGN
         MVC   OHRPAY(8),=X'402021204B2020' ADD EDIT PATTERN
         EDMK  OHRPAY(8),$HRPAY  MOVE PACKED FIED INTO PRINTLINE
         BCTR  1,0        DECREMENT R1 BY 1
         MVI   0(1),C'$'  PLACE DOLLAR SIGN
*
         MVC   OHOURS(7),=X'402021204B2020' CREATE EDIT PATTERN
         ED    OHOURS(7),$HOURS  MOVE INTO DETAIL LINE
*
         ZAP   PGRPAY(6),$HOURS(3)   PLACE PHOURS IN PGRPAY
         MP    PGRPAY(6),$HRPAY(3)   MP GROSS PAY BY HOURLY PAY
         SRP   PGRPAY(6),64-2,5      SHIFT 2 TO THE RIGHT & ROUND
         SP    PGRPAY(6),$DEDUCT(3)  SUBTRACT DEDUCTION FROM GROSS PAY
         AP    PGRPAY(6),$BONUS(3)   ADD BONUS AMOUNT TO GROSS PAY
*
         LA    1,OGRPAY+10           ENSURE PLACEMENT OF '$'
         MVC   OGRPAY(15),=X'402020202020206B2021204B2020'
         EDMK  OGRPAY(15),PGRPAY  MOVE PACKED GROSS PAY TO DETAIL LINE
         BCTR  1,0     DECREMENT R1 BY 1
         MVI   0(1),C'$'  PLACE DOLLAR SIGN
         AP    PTGRPAY(7),PGRPAY(6)  ADD GROSS PAY TO TOTAL
*
         LA    1,CNPPARMS    POINT R1 TO NET PAY PARMS LIST
         L     15,=V(CALCNPAY)  STORE LOCATION OF CALCNPAY IN R15
*
         BALR  14,15    GET THE RETURN ADDR FROM PSW 
*                       AND BRANCH TO CALCNPAY TO GET NET PAY
*                       AND BOTH WITHHOLDINGS
*
         LA    1,OFWTH+10   ENSURE PLACEMENT OF DOLLAR SIGN
         MVC   OFWTH(15),=X'402020202020206B2021204B2020'
         EDMK  OFWTH(15),PFEDWITH    MOVE PACKED FED WTHHOLDING TO DTL
         BCTR  1,0    DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
         AP    PTFWITH(7),PFEDWITH(6)  ADD FED WITHHOLDING TO TOTAL
*
         LA    1,OSWTH+10           ENSURE PLACEMENT OF DOLLAR SIGN
         MVC   OSWTH(15),=X'402020202020206B2021204B2020'
         EDMK  OSWTH(15),PSTWITH   MOVE PACKED STATE WTHHOLDING TO DTL
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
         AP    PTSWITH(7),PSTWITH(6)  ADD STATE WITHHOLDING TO TOTAL
* 
         LA    1,ONETPAY+10   ENSURE DOLLAR SIGN PLACEMENT
         MVC   ONETPAY(15),=X'402020202020206B2021204B2020'
         EDMK  ONETPAY(15),PNETPAY  MOVE NET PAY INTO DETAIL
         BCTR  1,0  DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
         AP    PTNETPAY(7),PNETPAY(6)  ADD NET PAY TO TOTAL
*
         C     8,MAXLINES    CHECK IF WE HAVE REACHED 19 LINES
         BC    B'0100',NOHDR BRANCH PAST HEADERS IF LESS THAN 19
*
         AP    PPAGECTR(2),=PL1'1'     ADD ONE TO PAGE COUNTER
         MVC   OPAGECTR(4),=X'40202120' CREATE EDIT PATTERN
         ED    OPAGECTR(4),PPAGECTR    PUT PPAGECTR IN OUTPUT FIELD
         SR    8,8                     ZERO OUT LINE COUNTER
*
         XPRNT COMPNAME,133    PRINT COMPANY NAME
         XPRNT SUBHDR,133      PRINT SUBHEADER
         XPRNT COLHDR1,133     PRINT COLHEADER 1
         XPRNT COLHDR2,133     PRINT COLHEADER 2
         XPRNT COLHDR3,133     PRINT COLHEADER 3
*
*
NOHDR    DS    0H
         XPRNT EMPDTL,133   PRINT EMPLOYEE DETAIL LINE
*
         LA    8,1(,8)  ADD ONE TO LINE COUNTER
*
         LA    6,42(,6)  MOVE TO NEXT ELEMENT IN TABLE
         SP    PECOUNT(3),=PL1'1'  DECREMENT EMPLOYEE COUNT BY 1
*
         CP    PECOUNT(3),=PL1'0'     CHECK IF EMPCOUNT IS NON ZERO
         BC    B'1111',PROCREC     BRANCH BACK TO TOP OF LOOP
*
ENDPROC  DS    0H
*
TOTALS   CP    0(3,3),=PL1'0'    CHECK IF EMPLOYEE COUNTER IS ZERO
         BC    B'1000',ENDTOTAL   BRANCH OVER TOTALS IF ZERO
*
         AP    PPAGECTR(2),=PL1'1'     ADD ONE TO PAGE COUNTER
         MVC   OPAGECTR(4),=X'40202120' CREATE EDIT PATTERN
         ED    OPAGECTR(4),PPAGECTR    PUT PPAGECTR IN OUTPUT FIELD
*
         MVC   OEMPCTR(6),=X'402020202120' EMP COUNTER EDIT PATTERN
         ED    OEMPCTR(6),0(3)   MOVE EMP COUNTER INTO PRINT LINE
*
         SRP   0(3,3),2,0  GIVE PEMPCTR 2 IMPLICIT DECMIAL PLACES
*
* PUT TOTAL GROSS PAY INTO PRINT LINE
*
         LA    1,OTGRPAY+11  ENSURE TOTAL GRPAY HAS DOLLAR SIGN IF 0
         MVC   OTGRPAY(19),=X'4020206B2020206B2020206B2021204B2020' 
         EDMK  OTGRPAY(19),PTGRPAY   MOVE PACKED TOTAL GRPAY INTO PL
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* CALCULATE AVERAGE GROSS PAY AMOUNT
*
         ZAP   PTOTAL(7),PTGRPAY(7)  USE PTGRPAY AS PARAM TO CALCAVG
         LA    1,CAPARMS             POINT R1 TO PARAMETERS
         L     15,=V(CALCAVG)        LOAD LOCATION OF CALCAVG INTO R15
         BALR  14,15                 BRANCH TO CALCAVG
         ZAP   PAVGROSS(7),PAVG(7)   MOVE AVERAGE TO AVERAGE GROSS
*
* MOVE AVERAGE GROSS PAY INTO PRINT LINE
*
         LA    1,OAVGROSS+11  ENSURE R1 HOLDS SLOT OF '$' IF ZERO
         MVC   OAVGROSS(16),=X'402020206B2020206B2021204B2020' 
         EDMK  OAVGROSS(16),PAVGROSS+1  MOVE AVG GROSS INTO PRINT LN
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* MOVE TOTAL FED WITHHOLDING INTO PRINT LINE
*
         LA    1,OTFWITH+11 ENSURE TOTAL FED WITH HAS DOLLAR SIGN IF 0
         MVC   OTFWITH(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTFWITH(19),PTFWITH   MOVE PACKED TOTAL GRPAY INTO PL
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* CALCULATE AVERAGE FED WITHHOLDING
*
         ZAP   PTOTAL(7),PTFWITH(7)  USE PTFWITH AS PARAM TO CALCAVG
         LA    1,CAPARMS             POINT R1 TO PARAMETERS
         L     15,=V(CALCAVG)        LOAD LOCATION OF CALCAVG INTO R15
         BALR  14,15                 BRANCH TO CALCAVG
         ZAP   PAVGFWTH(7),PAVG(7)   MOVE AVERAGE TO AVERAGE FED
*
* MOVE AVERAGE FED WITHHOLDING AMOUNT INTO PRINT LINE
*
         LA    1,OAVGFWTH+11  ENSURE R1 HOLDS SLOT OF '$' IF ZERO
         MVC   OAVGFWTH(16),=X'402020206B2020206B2021204B2020' 
         EDMK  OAVGFWTH(16),PAVGFWTH+1  MOVE AVG FED INTO PRINT LN
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* MOVE TOTAL STATE WITHHOLDING AMOUNT TO PRINT LINE
*
         LA    1,OTSWITH+11 ENSURE R1 HOLDS SLOT OF '$' IF 0
         MVC   OTSWITH(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTSWITH(19),PTSWITH  MOVE PTSWITH INTO PRINT LINE
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* CALCULATE AVERAGE STATE WITHHOLDING AMOUNT
*
         ZAP   PTOTAL(7),PTSWITH(7)  USE PTSWITH AS PARAM TO CALCAVG
         LA    1,CAPARMS             POINT R1 TO PARAMETERS
         L     15,=V(CALCAVG)        LOAD LOCATION OF CALCAVG INTO R15
         BALR  14,15                 BRANCH TO CALCAVG
         ZAP   PAVGSWTH(7),PAVG(7)   MOVE AVERAGE TO AVERAGE STATE
*
* MOVE AVERAGE STATE WITH INTO PRINT LINE
*
         LA    1,OAVGSWTH+11  ENSURE R1 HOLDS SLOT OF '$' IF ZERO
         MVC   OAVGSWTH(16),=X'402020206B2020206B2021204B2020' 
         EDMK  OAVGSWTH(16),PAVGSWTH+1  MOVE AVG STATE INTO PRINT LN
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* MOVE TOTAL NET PAY AMOUNT TO PRINT LINE
*
         LA    1,OTNETPAY+11 ENSURE R1 HOLDS SLOT OF '$' IF 0
         MVC   OTNETPAY(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTNETPAY(19),PTNETPAY  MOVE PTNETPAY INTO PL
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* CALCULATE AVERAGE NET PAY AMOUNT
*
         ZAP   PTOTAL(7),PTNETPAY(7)  USE PTSWITH AS PARAM TO CALCAVG
         LA    1,CAPARMS             POINT R1 TO PARAMETERS
         L     15,=V(CALCAVG)        LOAD LOCATION OF CALCAVG INTO R15
         BALR  14,15                 BRANCH TO CALCAVG
         ZAP   PAVGNET(7),PAVG(7)   MOVE AVERAGE TO AVERAGE STATE
*
* MOVE AVERAGE NET PAY INTO PRINT LINE
*
         LA    1,OAVGNET+11  ENSURE R1 HOLDS SLOT OF '$' IF ZERO
         MVC   OAVGNET(16),=X'402020206B2020206B2021204B2020' 
         EDMK  OAVGNET(16),PAVGNET+1  MOVE AVG NET INTO PRINT LN
         BCTR  1,0   DECREMENT R1 BY 1
         MVI   0(1),C'$' PLACE DOLLAR SIGN
*
* PRINT TOTALS SECTION
*
         XPRNT COMPNAME,133  PRINT COMPANY NAME HEADER
         XPRNT SUBHDR,133    PRINT SUBHEADER
         XPRNT HTOTALS,133   PRINT SUBHEADER
*
         XPRNT EMPCOUNT,133  PRINT EMPLOYEE COUNT
         XPRNT TGRPAY,133    PRINT TOTAL GROSS PAY
         XPRNT TFEDDTL,133   PRINT TOTAL FEDERAL WITHHOLDING
         XPRNT TSTDTL,133    PRINT TOTAL FEDERAL WITHHOLDING 
         XPRNT TNETDTL,133   PRINT TOTAL NET PAY
*
ENDTOTAL DS    0H
         DROP  6
*
* STANDARD EXIT LINKAGE WITH RC OF 0
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
         ORG   PROCTBL+((*-PROCTBL+31)/32)*32
         DC    C'* PROGRAM STORAGE FOR PROCTBL **'
*
PROCSAVE DS    18F    REGISTER SAVE AREA
*
CNPPARMS DC    A(PGRPAY)
         DC    A(0)
         DC    A(PFEDWITH)
         DC    A(0)
         DC    A(PSTWITH)
         DC    A(PNETPAY)
*
CAPARMS  DC    A(PTOTAL)
         DC    A(0)
         DC    A(PAVG)
*
PTOTAL   DC    PL7'0'
PAVG     DC    PL7'0'
*
PPAGECTR DC PL2'0' PACKED PAGE COUNTER (MAX 999)
PECOUNT  DC PL3'0' PACKED EMPLOYEE COUNTER
*
PEMPID   DC    PL5'0' PACKED EMPLOYEE ID
PHRPAY   DC    PL3'0' PACKED EMPLOYEE HOURLY PAY RATE
PHOURS   DC    PL3'0' PACKED EMPLOYEE HOURS WORKED
PDEDUCT  DC    PL3'0' PACKED EMPLOYEE DEDUCTION
PBONUS   DC    PL3'0' PACKED EMPLOYEE BONUS
PGRPAY   DC    PL6'0' PACKED CALCULATED EMPLOYEE GROSS PAY
PFEDWITH DC    PL6'0' PACKED CALCULATED FEDERAL WITHHOLDING
PSTWITH  DC    PL6'0' PACKED CALCULATED STATE WITHHOLDING
PNETPAY  DC    PL6'0' PACKED CALCULATED EMPLOYEE NET PAY
*
*
PTGRPAY  DC    PL7'0' PACKED TOTAL GROSS EMPLOYEE PAY
PTFWITH  DC    PL7'0' PACKED TOTAL FEDERAL WITHHOLDING
PTSWITH  DC    PL7'0' PACKED TOTAL STATE WITHHOLDING
PTNETPAY DC    PL7'0' PACKED TOTAL NET EMPLOYEE PAY
*
PAVGROSS DC    PL7'0' PACKED AVERAGE GROSS PAY
PAVGFWTH DC    PL7'0' PACKED AVERAGE FEDERAL WITHHOLDING
PAVGSWTH DC    PL7'0' PACKED AVERAGE STATE WITHHOLDING
PAVGNET  DC    PL7'0' PACKED AVERAGE NETP PAY
*
*
* PAGE HEADER LINE ONE (Company Name)
*
COMPNAME DC    C'1'
         DC    51C' '
         DC    CL30'CHICAGO SOFTWARE COMPANY, INC.'
         DC    41C' '
         DC    CL5'PAGE:'
         DC    1C' '
OPAGECTR DS    CL4
*
* PAGE HEADER LINE TWO (Subheader)
*
SUBHDR   DC    C' '
         DC    54C' '
         DC    CL23'EMPLOYEE PAYROLL REPORT'
         DC    55C' '
*
* COLUMN HEADERS
*
*
COLHDR1  DC    C'0'
         DC    CL8'EMPLOYEE'
         DC    3C' '
         DC    CL8'EMPLOYEE'
         DC    21C' '
         DC    CL6'HOURLY'
         DC    5C' '
         DC    CL5'HOURS'
         DC    12C' '
         DC    CL8'EMPLOYEE'
         DC    4C' '
         DC    CL16'EMPLOYEE FEDERAL'
         DC    4C' '
         DC    CL14'EMPLOYEE STATE'
         DC    10C' '
         DC    CL8'EMPLOYEE'
COLHDR2  DC    C' '
         DC    CL2'ID'
         DC    9C' '
         DC    CL4'NAME'
         DC    28C' '
         DC    CL3'PAY'
         DC    4C' '
         DC    CL6'WORKED'
         DC    11C' '
         DC    CL9'GROSS PAY'
         DC    9C' '
         DC    CL11'WITHHOLDING'
         DC    7C' '
         DC    CL11'WITHHOLDING'
         DC    11C' '
         DC    CL7'NET PAY'
COLHDR3  DC    C' '
         DC    9C'-'
         DC    2C' '
         DC    25C'-'
         DC    3C' '
         DC    7C'-'
         DC    3C' '
         DC    7C'-'
         DC    5C' '
         DC    15C'-'
         DC    4C' '
         DC    16C'-'
         DC    4C' '
         DC    14C'-'
         DC    3C' '
         DC    15C'-'
HTOTALS  DC    C' '
         DC    62C' '
         DC    CL7'TOTALS '
         DC    64C' ' 
*
* EMPLOYEE DETAIL LINE
* 
EMPDTL   DC    C'0'
OEMPID   DS    CL9
         DC    2C' '
OEMPNME  DS    CL25
         DC    3C' '
OHRPAY   DS    CL8
         DC    2C' '
OHOURS   DS    CL7
         DC    6C' '
OGRPAY   DS    CL15
         DC    5C' '
OFWTH    DS    CL15
         DC    2C' '
OSWTH    DS    CL15
         DC    4C' '
ONETPAY  DS    CL15
*
*
* TOTALS PRINT LINES
*
*
* -- EMPLOYEE COUNT PRINT LINE -- 
EMPCOUNT DC    C'0'  
         DC    6C' '
         DC    CL20'NUMBER OF EMPLOYEES: '
         DC    10C' '
OEMPCTR  DS    CL6
         DC    90C' '
* -- TOTAL & AVERAGE GROSS PAY PRINT LINE --
TGRPAY   DC   C'0'
         DC   10C' '
         DC   CL16'TOTAL GROSS PAY:'
         DC   1C' '
OTGRPAY  DS   CL19
         DC   19C' '
         DC   CL18'AVERAGE GROSS PAY:'
         DC   C' '
OAVGROSS DS   CL16
         DC   32C' '
* -- TOTAL & AVERAGE FEDERAL WITHHOLDING PRINT LINE -- 
TFEDDTL  DC   C'0'
         DC   CL26'TOTAL FEDERAL WITHHOLDING:'
         DC   1C' '
OTFWITH  DC   CL19' '
         DC   10C' '
         DC   CL28'AVERAGE FEDERAL WITHHOLDING:'
OAVGFWTH DC   CL16' '
         DC   32C' '
* -- TOTAL & AVERAGE STATE WITHHOLDING PRINT LINE -- 
TSTDTL   DC   C'0'
         DC   2C' '
         DC   CL24'TOTAL STATE WITHHOLDING:'
         DC   1C' '
OTSWITH  DC   CL19' '
         DC   12C' '
         DC   CL26'AVERAGE STATE WITHHOLDING:'
OAVGSWTH DC   CL16' '
         DC   32C' '
* -- TOTAL & AVERAGE NET PAY PRINT LINE --
TNETDTL  DC   C'0'
         DC   12C' '
         DC   CL14'TOTAL NET PAY:'
         DC   1C' '
OTNETPAY DS   CL19
         DC   22C' '
         DC   CL16'AVERAGE NET PAY:'
OAVGNET  DC   CL16' '
         DC   32C' '
*
MAXLINES DC    F'19'
IDPTRN   DS    CL10
*
*
*****************************************************************
*                                                               *
*   SUBPROGRAM NAME: CALCNPAY                                   *
*                                                               *
*          FUNCTION: Calculates the employee's two              *
*                     withholding amounts and the               *
*                     employee's net pay amount                 *
*                                                               *
*         PARAMETERS: PEMPGPAY                                  *
*                      PFWHPCT                                  *
*                     PFEDWITH                                  *
*                      PSWHPCT                                  *
*                      PSTWITH                                  *
*                      PEMPNPAY                                 *
*                                                               *
*                                                               *
*****************************************************************
CALCNPAY CSECT
*
*  STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)  SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15         COPY CSECT ADDR INTO R12
         USING CALCNPAY,12    ESTABLISH R12 AS THE BASE REG
         LA    14,NETSAVE   R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)     STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)     STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14         POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,7,0(1)   R2 -> PGRPAY(6)
*                         R3 -> PFWHPCT(4)
*                         R4 -> PFEDWITH(6)
*                         R5 -> PSWHPCT(4)
*                         R6 -> PSTWITH(6)
*                         R7 -> PNETPAY(6)
*
         ZAP   PCALC(10),0(6,2)   PUT GROSS PAY INTO LARGER FIELD
         MP    PCALC(10),0(4,3)  MULTIPLY GROSS PAY BY FED WTH
         SRP   PCALC(10),64-5,5      SHIFT RIGHT FOR 2 DECIMAL PLACES
         ZAP   0(6,4),PCALC(10) MOVE PCALC INTO PFEDWITH FIELD
*      
         ZAP   PCALC(10),0(6,2)  MOVE PGRPAY INTO LARGER FIELD
         MP    PCALC(10),0(4,5) MULTIPLY GROSS PAY BY STATE WTH
         SRP   PCALC(10),64-5,5     SHIFT RIGHT FOR 2 DECIMAL PLACES
         ZAP   0(6,6),PCALC(10) MOVE PCALC INTO PSTWITH FIELD
*
         ZAP   0(6,7),0(6,2)  INITIALIZE NET PAY AS GROSS PAY
         SP    0(6,7),0(6,4) SUBTRACT FED WTH FROM NET PAY
         SP    0(6,7),0(6,6)  SUBTRACT STATE WTH FROM NET PAY
*
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
         ORG   CALCNPAY+((*-CALCNPAY+31)/32)*32
         DC    C'* PROGRAM STORAGE FOR CALCNPAY **'
*
NETSAVE  DS    18F    REGISTER SAVE AREA
*
PCALC    DC    PL10'0'
*
*
*****************************************************************
*                                                               *
*   SUBPROGRAM NAME: CALCAVG                                    *
*                                                               *
*          FUNCTION: Calculates a single average for an         *
*                     employee                                  *
*                                                               *
*         PARAMETERS: PTOTAL                                    *
*                     PEMPCTR                                   *
*                     PAVG                                      *
*                                                               *
*                                                               *
*****************************************************************
CALCAVG CSECT
*
*  STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13)  SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15         COPY CSECT ADDR INTO R12
         USING CALCAVG,12    ESTABLISH R12 AS THE BASE REG
         LA    14,AVGSAVE    R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13)     STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14)     STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14         POINT R13 AT THIS CSECT'S SAVE AREA
*
         LM    2,4,0(1)    R2 -> PTOTAL(7)
*                          R3 -> PEMPCTR(3)
*                          R4 -> PAVG(7)
*
         ZAP   PTMP(10),0(7,2) MOVE TOTAL INTO LARGER FIELD
         SRP   PTMP(10),3,0   ADD THREE FAKE DECIMAL PLACES
         DP    PTMP(10),0(3,3) DIVIDE TOTAL GROSS BY EMP COUNT
         SRP   PTMP(7),64-1,5     ROUND TO TWO DECIMAL PLACES
         ZAP   0(7,4),PTMP(7) MOVE CALCULATED AVG INTO ITS FIELD
*
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
         ORG   CALCAVG+((*-CALCAVG+31)/32)*32
         DC    C'* PROGRAM STORAGE FOR CALCAVG **'
*
AVGSAVE  DS    18F    REGISTER SAVE AREA
*
PTMP     DC    PL10'0'
         END   PAYROLL
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATASP25(DATA10),DISP=SHR
//*
//FT06F001 DD SYSOUT=*
//
