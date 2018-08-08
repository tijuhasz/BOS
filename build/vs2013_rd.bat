@SET KIND=Visual Studio 12
@SET OUTDIR=vs2013
@SET DIR=%CD%

@R:
@CD \
@IF NOT EXIST ".\%OUTDIR%\nul" md %OUTDIR%
@cd ".\%OUTDIR%\"
cmake %DIR%/.. -G "%KIND%" -DCMAKE_TOOLCHAIN_FILE=%DIR%/../cmake/win32-vs2012.cmake

pause
