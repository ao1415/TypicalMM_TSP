@echo off

set TESTER=./../tester/tester.jar
set EXEC=./../x64/Release/TypicalMM_TSP.exe

cd ./image

set i=1
:loop
REM java -jar %TESTER% -exec %EXEC% -seed %i% -vis -save -num
java -jar %TESTER% -exec %EXEC% -seed %i% -save -num
set /a i+=1
if %i% leq 10 goto loop

pause
