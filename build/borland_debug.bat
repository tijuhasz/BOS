@SET KIND=Borland Makefiles
@SET OUTDIR=borland

@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake ../.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=../../cmake/borland.cmake -DCMAKE_BUILD_TYPE=Debug
