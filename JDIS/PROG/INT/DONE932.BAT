:DONE932.BAT -- CONVERSION of 93-1 Data Files to Multi-User 93-2 Format
:14 JUL 93 - JJS
:                                                                            
:START
echo off
cls
echo                  JDIS Conversion 93-1 to 93-2 Data Files
echo            .
echo            .
echo            .
echo            ****************************************************
echo            *                                                  *
echo            *     This will complete Data Files Conversion     *
echo            *                                                  *
echo            ****************************************************
echo            .
echo            .
:CKTRANS
cd \prog\cmn
if not exist aspenprc.dlr goto CONT1
:CONT
echo            .
echo            .
echo            **********************************************
echo            *      The next step will remove files       *
echo            *      that are no longer needed.  Ignore    *
echo            *      any 'File Not Found' message.         *
echo            **********************************************
echo            .
del \prog\cmn\aspenprc.sys
rename aspenprc.dlr aspenprc.sys
cd \
del start932.bat
cd \prog\cmn
if not exist aspenprc.sys goto ERROR
echo            .
echo            .
:pause
:CONT1
cls
echo                JDIS Conversion 93-1 to 93-2 Data Files
echo            .
echo            .
echo            .
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *            S U C C E S S F U L !            *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *                                             *
echo            *            Conversion Completed             *
echo            *                                             *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            .
echo            .
pause
jdis
goto end
:ERROR
cls
echo               JDIS Conversion 93-1 to 93-2 Data Files
echo            .
echo            .
echo            .
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *                E R R O R                    *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            *                                             *
echo            *     Your ASPENPRC.SYS file has not been     *
echo            *     reset.  Contact JDIS before you         *
echo            *     continue.                               *
echo            *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
echo            .
echo            .
pause
jdis
goto end
:END
