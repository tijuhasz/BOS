@SET KIND=Visual Studio 14 Win64
@SET OUTDIR=vs2015_x64

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -T "v140_xp" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win64-vs2012.cmake -DMSVC2015=TRUE

pause
