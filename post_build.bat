@echo off
REM Post-build script to copy DLLs according to configuration
REM Parameters: %1 = TargetDir, %2 = ConfigurationName, %3 = PlatformName

echo ========================================
echo Post-Build Script - COMX51 IO Test
echo ========================================
echo TargetDir: %1
echo Configuration: %2
echo Platform: %3
echo ========================================

REM Check parameters
if "%1"=="" (
    echo ERROR: TargetDir not specified
    exit /b 1
)

if "%2"=="" (
    echo ERROR: ConfigurationName not specified
    exit /b 1
)

if "%3"=="" (
    echo ERROR: PlatformName not specified
    exit /b 1
)

REM Determine library directory according to platform and configuration
REM Remove quotes from parameters if they have them
set PLATFORM=%3
set PLATFORM=%PLATFORM:"=%
set CONFIG=%2
set CONFIG=%CONFIG:"=%

if "%PLATFORM%"=="Win32" (
    set LIB_DIR=%~dp0lib\x86\%CONFIG%
) else (
    set LIB_DIR=%~dp0lib\%PLATFORM%\%CONFIG%
)

echo Copying DLLs from: %LIB_DIR%

REM Check if directory exists
if not exist "%LIB_DIR%" (
    echo ERROR: Library directory not found: %LIB_DIR%
    echo Available directories:
    dir /b "%~dp0lib\%3\"
    exit /b 1
)

REM Copy netXSPMUSB.dll (once)
echo Copying netXSPMUSB.dll...
if exist "%LIB_DIR%\netXSPMUSB.dll" (
    copy /Y "%LIB_DIR%\netXSPMUSB.dll" "%1" >nul
    if errorlevel 1 (
        echo ERROR: Could not copy netXSPMUSB.dll
        exit /b 1
    ) else (
        echo ✓ netXSPMUSB.dll copied successfully
    )
) else (
    echo WARNING: netXSPMUSB.dll not found in %LIB_DIR%
)

echo ========================================
echo Post-build completed successfully
echo ========================================
