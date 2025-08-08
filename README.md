# COMX51 USB I/O Test - PROFINET Communication Project

## 📋 Description

Project for I/O communication with COMX51 device via USB using Hilscher's netXSPMUSB API. Allows testing communication between a PLC via PROFINET and the COMX51 device.

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
- **COMX51**: PROFINET I/O Device (slave) with appropriate firmware, inside COMXEB
- **PC**: Running this code, connected to COMXEB via USB
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
├── cifX32DLL.dll      
├── cifX32DLL64.dll    
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
- COMX51 device connected via USB
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