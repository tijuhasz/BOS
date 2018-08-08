@SET KIND=Visual Studio 14
@SET OUTDIR=vs2015_static

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2012.cmake -DBUILD_SHARED=FALSE -DMSVC2015=TRUE

pause
