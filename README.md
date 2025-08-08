# COMX51 USB I/O Test - PROFINET Communication Project

## 📋 Description

Project for I/O communication with COMX51 device via USB using Hilscher's netXSPMUSB API. Allows testing communication between a PLC via PROFINET and the COMX51 device. The COMX51 module is built around the Hilscher netX51 industrial communication SoC.

## 🔄 Test Architecture

```
┌─────────────────┐
│                 │
│   PLC (PROFINET │
│   Controller)   │
│                 │
└─────────────────┘
         │
         │ PROFINET
         ▼
┌─────────────────┐
│  ┌─────────────┐│
│  │  COMX51     ││
│  │ (PROFINET   ││
│  │  I/O Device)││
│  └─────────────┘│
│                 │
│                 │
│  COMXEB (USB)   │
└─────────────────┘
         │
         │ USB
         ▼
┌─────────────────┐
│                 │
│  PC (This Code) │
│                 │
└─────────────────┘
```

**Test Setup:**
- **PLC**: PROFINET Controller (master) - connected directly to COMX51
- **COMXEB**: USB interface module containing COMX51
- **COMX51**: PROFINET I/O Device (slave) with appropriate firmware, inside COMXEB (netX51-based)
- **PC**: Running this code, connected to COMXEB via USB
- **Register Editor**: Ensure that in you register editor route "computer\HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\CIFxDrv" 
                       your start driver is set to automatic (2, NOT 3), and your imagePath is correct "\SystemRoot\System32\drivers\BthHfAud.sys"
- **Communication**: Real-time I/O data exchange between PLC and COMX51, accessed through COMXEB

## 🎯 Why This Project?

This project was created to address a common problem faced by developers working with **Hilscher COMX boards**:

### The Problem
- Hilscher provides the DLLs but the documentation is **disorganized and confusing**
- There's **limited clear information** about how to get started with I/O data communication
- The official "Getting Started" guides are scattered and lack practical examples for sending/receiving I/O data
- Developers often struggle to find working examples that demonstrate the complete workflow
- Documentation is fragmented across multiple sources making it difficult to follow

### The Solution
This project provides:
- ✅ **Complete working example** of I/O communication with COMX51
- ✅ **Clear code structure** showing how to initialize, configure, and use the cifX API
- ✅ **Real-time I/O data exchange** between PLC and COMX51 device
- ✅ **Error handling** and debugging information
- ✅ **Ready-to-use code** that can be adapted for other COMX boards

### Who Can Benefit
- **Developers** working with Hilscher COMX boards (COMX51, COMX50, etc.)
- **System integrators** who need to implement PROFINET communication
- **Students** learning industrial communication protocols
- **Anyone** who needs a practical example of cifX API usage

## ✅ Project Status

**PROJECT FULLY FUNCTIONAL!**

- ✅ x64 compilation working
- ✅ x86 compilation working  
- ✅ DLLs copied automatically
- ✅ Automation scripts created
- ✅ Program running correctly

## 🧰 Setup

1. Install Visual Studio 2022 (Desktop development with C++).
2. Install one of the Hilscher USB drivers listed below in Requirements.
3. Ensure the libraries are present in `lib/`:
   - `lib/x64/Release/netXSPMUSB.{dll,lib}`
   - `lib/x64/Debug/netXSPMUSB.{dll,lib}`
   - `lib/x86/Release/netXSPMUSB.{dll,lib}` (optional, for Win32 build)
   - `lib/x86/Debug/netXSPMUSB.{dll,lib}` (optional, for Win32 build)
4. Build with the script or from the IDE (post-build copies `netXSPMUSB.dll` automatically).

## 🚀 Quick Compilation

### Automatic Script (Recommended)
```batch
# x64 Release (recommended)
build_vs.bat x64 Release

# x86 Release
build_vs.bat x86 Release

# x64 Debug
build_vs.bat x64 Debug

# x86 Debug
build_vs.bat x86 Debug
```

### From Visual Studio IDE
1. Open `COMX51_IO_Test.sln`
2. Select configuration (x64/Win32, Debug/Release)
3. Build → Build Solution (Ctrl+Shift+B)

## 📁 Project Structure

```
cifx-usb-io-test/
├── src/
│   └── COMX51_IO_Test.cpp          # Main source code
├── includes/
│   ├── cifXAPI/                     # cifX API headers
│   └── HilscherDefinitions/         # Hilscher definition headers
├── lib/                             # Libraries organized by architecture
│   ├── x64/
│   │   ├── Debug/                   # x64 Debug DLLs
│   │   └── Release/                 # x64 Release DLLs
│   └── x86/
│       ├── Debug/                   # x86 Debug DLLs
│       └── Release/                 # x86 Release DLLs
├── build/                           # Compiled files (auto-generated)
│   ├── x64/
│   │   ├── Debug/
│   │   └── Release/
│   └── Win32/
│       ├── Debug/
│       └── Release/
├── build_vs.bat                     # Automatic compilation script
├── post_build.bat                   # Post-build script to copy DLLs
├── COMX51_IO_Test.sln               # Visual Studio solution
├── COMX51_IO_Test.vcxproj           # C++ project
└── README.md                        # This file
```

## 🔧 Available Configurations

| Architecture | Configuration | Output Directory | Status |
|--------------|---------------|------------------|--------|
| **x64** | **Release** | `build\x64\Release\` | ✅ **WORKING** |
| **x64** | **Debug** | `build\x64\Debug\` | ✅ **READY** |
| **Win32 (x86)** | **Release** | `build\Win32\Release\` | ✅ **WORKING** |
| **Win32 (x86)** | **Debug** | `build\Win32\Debug\` | ✅ **READY** |

## 📦 Generated Files

### x64 Release (Recommended)
```
build\x64\Release\
├── COMX51_IO_Test.exe
├── COMX51_IO_Test.pdb
├── netXSPMUSB.dll
└── vc143.pdb
```

### Win32 Release
```
build\Win32\Release\
├── COMX51_IO_Test.exe 
├── COMX51_IO_Test.pdb 
├── netXSPMUSB.dll     
└── vc143.pdb          
```

## 🎯 How to Use

### 1. Compile
```batch
# Compile x64 Release (recommended)
build_vs.bat x64 Release
```

### 2. Execute
```batch
# Run the program
build\x64\Release\COMX51_IO_Test.exe
```

Notes:
- Run from a terminal with access to the output folder, or double-click the EXE in Explorer.
- Stop the I/O loop by pressing the key `Q` in the console.
- For Win32 (x86), build `Win32 Release` and run from `build\Win32\Release\`.

### 3. Connect Hardware
- Connect COMX51 device via USB
- Program will automatically detect the device
- Will show driver and board information
- Will start I/O communication test

## 🔍 Program Features

### Main Functions
- ✅ **Automatic DLL loading** according to architecture (x64/x86)
- ✅ **Device detection** COMX51
- ✅ **Driver information** cifX
- ✅ **Board and channel information**
- ✅ **Real-time I/O communication test**
- ✅ **Detailed error handling**

## 🛠️ Requirements

### Software
- Visual Studio 2022 with C++ Desktop Development (tested with C++17)
- Windows 10/11
- **Hilscher USB drivers** - Install one of the following:
  - `netX USB FTDI driver installation`
  - `netX51_52_4000_4100_Dummy`
  - `netX50_51_52_100_4x00`
- **No additional cifX drivers required** - netXSPMUSB.dll is self-contained

### Hardware
- COMX51 device (netX51-based) connected via USB
- USB type A to micro-B cable

## 🔧 Troubleshooting

### Error: "MSBuild not found"
- Run from "Developer Command Prompt for VS 2022"
- Or use the `build_vs.bat` script that automatically configures the environment
- **Note**: Tested with Visual Studio 2022 and C++17

### Error: "DLL not found"
- Check that DLLs are in `lib\{arch}\{config}\`
- Post-build script automatically copies DLLs

### Error: "cifX driver not available"
- Check that netXSPMUSB.dll is in the correct directory
- Run as administrator
- Check that COMX51 is connected via USB

### Error: "Device not found" or "USB device not recognized"
- Install Hilscher USB drivers (one of the following):
  - `netX USB FTDI driver installation`
  - `netX51_52_4000_4100_Dummy`
  - `netX50_51_52_100_4x00`
- Check Device Manager to ensure COMX51 is properly recognized
- Try different USB cable or port
- Restart computer and reconnect device

### Common pitfalls
- Architecture mismatch (x64 app with x86 DLL or vice-versa). Build and DLL must match.
- Board name mismatch. Code expects board alias `cifX0` by default (see Configurable parameters).
- Device not enumerating as USB (driver not installed or cable/port issue).
- Permissions. If access is denied, try running the console as Administrator.

### Configurable parameters (source code)
Edit these constants if needed:

```c
// src/COMX51_IO_Test.cpp
#define IO_BUFFER_SIZE 1024
#define TIMEOUT_MS 1000
#define BOARD_NAME "cifX0"
```

## 🖨️ Expected Console Output (Example)

Note: The exact values depend on your COMX configuration (number/size of I/O areas, firmware, etc.). This is an example of a correct run after the board is configured and connected.

```
========================================
  COMX51 I/O Test - PROFINET
========================================

Starting program...
Checking available DLLs...

Testing loading of netXSPMUSB.dll...
SUCCESS: netXSPMUSB.dll loaded correctly!
Main functions found!

Checking if cifX driver is available...
Opening cifX driver...
cifX driver opened successfully!

=== Driver Information ===
Driver Version: netXSPMUSB DLL V1.10.0.0

=== Board Information ===
Board 0:
  Name: cifX0
  Alias:
  Device Number: 1571100
  Serial Number: 43394

  Channel 0:
    Channel Error: 0x00000000
    Board Name: cifX0
    Firmware: PROFINET IO Device
    FW Version: 4.9.4 Build 0
    Mailbox Size: 1596
    I/O Input Areas: 2
    I/O Output Areas: 2
    netX Flags: 0x000000F1
    Host Flags: 0x000000F0

  Channel 1:
    Channel Error: 0x00000000
    Board Name: cifX0
    Firmware: Network Services
    FW Version: 1.0.0 Build 0
    Mailbox Size: 1596
    I/O Input Areas: 2
    I/O Output Areas: 2
    netX Flags: 0x00000038
    Host Flags: 0x00000038

=== I/O Communication Test ===
Channel opened successfully!
Host configured as READY
Bus configured as ON

Starting I/O cycle...
Press 'Q' to stop

Cycle 1 - Input: 0x3A 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
Cycle 1 - Output: 0x01 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
---
Cycle 2 - Input: 0x73 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
Cycle 2 - Output: 0x02 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
---
Cycle 3 - Input: 0x74 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
Cycle 3 - Output: 0x03 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
---
Cycle 4 - Input: 0x75 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
Cycle 4 - Output: 0x04 0x00 0x00 0x00 0x00 0x00 0x00 0x00 ...
---
```