@SET KIND=Visual Studio 14
@SET OUTDIR=vs2015

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2012.cmake -DMSVC2015=TRUE

pause