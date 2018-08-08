@SET KIND=Visual Studio 12
@SET OUTDIR=vs2013_single_dll

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -T "v120_xp" -DCMAKE_TOOLCHAIN_FILE=../../cmake/win32-vs2012.cmake -DVCF_SINGLE_DLL=TRUE

pause
