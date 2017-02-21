@SET KIND=Visual Studio 11
@SET OUTDIR=vs2012

REM delete build directory before starting to build
@IF EXIST ".\%OUTDIR%" RD /S /Q ".\%OUTDIR%"
@md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -T "v110_xp" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2012.cmake

@cd ..

pause