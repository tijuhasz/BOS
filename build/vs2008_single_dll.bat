SET KIND=Visual Studio 9 2008
SET OUTDIR=.\vs2008\

IF NOT EXIST "%OUTDIR%\nul" md %OUTDIR%
cd "%OUTDIR%"
cmake ../.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2008.cmake  -DVCF_SINGLE_DLL=TRUE

pause
