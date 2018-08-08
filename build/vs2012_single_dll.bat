@SET KIND=Visual Studio 11
@SET OUTDIR=vs2012_single_dll

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -T "v110_xp" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2012.cmake -DVCF_SINGLE_DLL=TRUE

pause
