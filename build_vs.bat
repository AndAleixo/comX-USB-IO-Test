@echo off
REM Build script for COMX51 IO Test with automatic VS configuration
REM Usage: build_vs.bat [x64|x86] [Debug|Release]

setlocal enabledelayedexpansion

echo ========================================
echo COMX51 IO Test - Build Script
echo ========================================

REM Check parameters
if "%1"=="" (
    echo Usage: build_vs.bat [x64^|x86] [Debug^|Release]
    echo.
    echo Examples:
    echo   build_vs.bat x64 Release
    echo   build_vs.bat x86 Debug
    echo   build_vs.bat x64
    echo   build_vs.bat
    echo.
    echo If no parameters are specified, x64 Release will be compiled
    echo.
    pause
    exit /b 1
)

REM Configure platform
set PLATFORM=%1
if "%PLATFORM%"=="x64" (
    echo Platform: x64
) else if "%PLATFORM%"=="x86" (
    echo Platform: x86
) else (
    echo ERROR: Invalid platform. Use x64 or x86
    exit /b 1
)

REM Configure configuration
set CONFIG=%2
if "%CONFIG%"=="" (
    set CONFIG=Release
    echo Configuration not specified, using Release
) else if "%CONFIG%"=="Debug" (
    echo Configuration: Debug
) else if "%CONFIG%"=="Release" (
    echo Configuration: Release
) else (
    echo ERROR: Invalid configuration. Use Debug or Release
    exit /b 1
)

echo ========================================
echo Compiling: %PLATFORM% %CONFIG%
echo ========================================

REM Find Visual Studio and configure environment
echo Configuring Visual Studio environment...

REM Find Visual Studio 2022
set VS_PATH=
for /f "tokens=*" %%i in ('dir "C:\Program Files\Microsoft Visual Studio\2022" /b 2^>nul') do (
    if exist "C:\Program Files\Microsoft Visual Studio\2022\%%i\Common7\Tools\VsDevCmd.bat" (
        set VS_PATH=C:\Program Files\Microsoft Visual Studio\2022\%%i
        goto :found_vs
    )
)

REM Find Visual Studio 2019
for /f "tokens=*" %%i in ('dir "C:\Program Files (x86)\Microsoft Visual Studio\2019" /b 2^>nul') do (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\%%i\Common7\Tools\VsDevCmd.bat" (
        set VS_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\%%i
        goto :found_vs
    )
)

echo ERROR: Visual Studio not found
echo Make sure you have Visual Studio 2019 or 2022 installed
pause
exit /b 1

:found_vs
echo Visual Studio found at: %VS_PATH%

REM Configure Visual Studio environment
echo Configuring environment...
call "%VS_PATH%\Common7\Tools\VsDevCmd.bat" -arch=%PLATFORM%

if errorlevel 1 (
    echo ERROR: Could not configure Visual Studio environment
    pause
    exit /b 1
)

REM Check that MSBuild is available
where msbuild >nul 2>&1
if errorlevel 1 (
    echo ERROR: MSBuild not found after configuring environment
    pause
    exit /b 1
)

echo ✓ Visual Studio environment configured correctly

REM Check that solution file exists
if not exist "COMX51_IO_Test.sln" (
    echo ERROR: Solution file not found
    echo Make sure to run this script from the project directory
    pause
    exit /b 1
)

REM Clean previous build
echo Cleaning previous build...
msbuild COMX51_IO_Test.sln /t:Clean /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /verbosity:minimal

if errorlevel 1 (
    echo ERROR: Error cleaning
    pause
    exit /b 1
)

REM Compile
echo Compiling project...
msbuild COMX51_IO_Test.sln /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /verbosity:normal

if errorlevel 1 (
    echo ========================================
    echo ERROR: Build failed
    echo ========================================
    pause
    exit /b 1
)

echo ========================================
echo ✓ Build successful
echo ========================================
echo.
echo Generated files in: build\%PLATFORM%\%CONFIG%\
echo.
echo To run:
echo   build\%PLATFORM%\%CONFIG%\COMX51_IO_Test.exe
echo.

REM Show generated files
if exist "build\%PLATFORM%\%CONFIG%\COMX51_IO_Test.exe" (
    echo Generated files:
    dir "build\%PLATFORM%\%CONFIG%\"
) else (
    echo WARNING: Generated executable not found
)

pause
