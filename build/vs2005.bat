SET KIND=Visual Studio 8 2005
SET OUTDIR=.\vs2005\

IF NOT EXIST "%OUTDIR%\nul" md %OUTDIR%
cd "%OUTDIR%"
cmake ../.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2005.cmake

pause
