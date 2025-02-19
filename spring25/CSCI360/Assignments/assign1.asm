//KC03AEDA JOB ,'M. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
*
PROGRAM1 CSECT
         USING PROGRAM1,15
         XDUMP ,
         BCR   B'1111',14
         END   PROGRAM1
