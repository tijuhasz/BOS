@SET KIND=Visual Studio 12 Win64
@SET OUTDIR=vs2013_x64

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -T "v120_xp" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win64-vs2012.cmake

pause
