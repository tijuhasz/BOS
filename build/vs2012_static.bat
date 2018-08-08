@SET KIND=Visual Studio 11
@SET OUTDIR=vs2012_static

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -T "v110_xp" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2012.cmake -DBUILD_SHARED=FALSE


