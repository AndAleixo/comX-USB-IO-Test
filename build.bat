@echo off
REM Build script for COMX51 IO Test
REM Usage: build.bat [x64|x86] [Debug|Release]

setlocal enabledelayedexpansion

echo ========================================
echo COMX51 IO Test - Build Script
echo ========================================

REM Check parameters
if "%1"=="" (
    echo Usage: build.bat [x64^|x86] [Debug^|Release]
    echo.
    echo Examples:
    echo   build.bat x64 Release
    echo   build.bat x86 Debug
    echo   build.bat x64
    echo   build.bat
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

REM Check that MSBuild is available
where msbuild >nul 2>&1
if errorlevel 1 (
    echo ERROR: MSBuild not found
    echo Make sure you have Visual Studio installed and run from Developer Command Prompt
    pause
    exit /b 1
)

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
