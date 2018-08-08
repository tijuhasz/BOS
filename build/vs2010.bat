@SET KIND=Visual Studio 10
@SET OUTDIR=vs2010

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2010.cmake

pause