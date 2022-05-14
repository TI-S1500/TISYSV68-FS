:START932.BAT -- CONVERSION of Rel 93-1 to Rel 93-2 Multi-user format
:14 JUL 93 - JJS
:                                                                    
:START
echo off
cls
echo                   JDIS Conversion 93-1 to 93-2 Data Files
echo            .
echo            .
echo            .
echo            ****************************************************
echo            *  NOTE:  Once you start this process, you will    *
echo            *         need to COMPLETE all of the instructions * 
echo            *         to convert your Data Files before you    *
echo            *         can run any other JDIS programs.         *
echo            *                                                  *
echo            ****************************************************
echo            .
echo            .
question  DO YOU WISH TO CONTINUE (Y,N): @YN
if errorlevel 2 goto STOP
if errorlevel 1 goto CONT    
:CONT
cd \prog\cmn
if exist aspenprc.dlr goto CONT1
rename aspenprc.sys aspenprc.dlr
rename aspenprc.932 aspenprc.sys
cd \
echo            .
echo            .
pause
:CONT1
cls
echo                 JDIS Conversion 93-1 to 93-2 Data Files
echo            .
echo            .
echo            .
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *            S U C C E S S F U L !            *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *                                             *
echo            *  Press ENTER/RETURN and the JDIS Main       *
echo            *  Menu will display.                         *
echo            *                                             *
echo            *  At the "Make Your Selection:" prompt,      *
echo            *  type CONV932 and press ENTER/RETURN.       *
echo            *                                             *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            .
echo            .
pause
jdis
goto end
:STOP
cls
echo                 JDIS Conversion 93-1 to 93-2 Data Files
echo            .
echo            .
echo            .
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *           INSTALLATION TERMINATED           *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            .
echo            .
pause
jdis
goto end
:END
