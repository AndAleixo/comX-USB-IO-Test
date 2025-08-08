/**************************************************************************************
  COMX51 I/O Test Program
  Tests I/O communication between PLC via PROFINET and COMX51
  
  Based on examples from cifX Toolkit CD
**************************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

// Include cifX libraries
#include "cifXUser.h"
#include "cifXErrors.h"

// Global configurations
#define IO_BUFFER_SIZE 1024
#define TIMEOUT_MS 1000
#define BOARD_NAME "cifX0"

// I/O buffers
unsigned char g_abInputBuffer[IO_BUFFER_SIZE] = {0};
unsigned char g_abOutputBuffer[IO_BUFFER_SIZE] = {0};

/*****************************************************************************/
/*! Shows cifX driver error
*   \param  lError      cifX Error number                                    */
/*****************************************************************************/
void ShowError(int32_t lError)
{
  if(lError != CIFX_NO_ERROR)
  {
    char szError[1024] = {0};
    xDriverGetErrorDescription(lError, szError, sizeof(szError));
    printf("Error: 0x%08X - %s\n", lError, szError);
  }
}

/*****************************************************************************/
/*! Tests DLL loading
*   \param  szDllName   DLL name to test                                      */
/*****************************************************************************/
bool TestDllLoad(const char* szDllName)
{
  printf("Testing loading of %s...\n", szDllName);
  
  HMODULE hDll = LoadLibraryA(szDllName);
  if(hDll == NULL)
  {
    DWORD dwError = GetLastError();
    printf("ERROR: Could not load %s\n", szDllName);
    printf("Error code: %lu\n", dwError);
    
    // Show error description
    char szError[256] = {0};
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  szError, sizeof(szError), NULL);
    printf("Description: %s\n", szError);
    return false;
  }
  else
  {
    printf("SUCCESS: %s loaded correctly!\n", szDllName);
    
    // Check if main functions are available
    FARPROC pfnDriverOpen = GetProcAddress(hDll, "xDriverOpen");
    FARPROC pfnDriverClose = GetProcAddress(hDll, "xDriverClose");
    
    if(pfnDriverOpen && pfnDriverClose)
    {
      printf("Main functions found!\n");
    }
    else
    {
      printf("WARNING: Some main functions not found\n");
    }
    
    FreeLibrary(hDll);
    return true;
  }
}

/*****************************************************************************/
/*! Shows driver information
*   \param  hDriver    Driver handle                                          */
/*****************************************************************************/
void ShowDriverInfo(CIFXHANDLE hDriver)
{
  DRIVER_INFORMATION tDriverInfo = {{0}};
  
  printf("=== Driver Information ===\n");
  
  int32_t lRet = xDriverGetInformation(hDriver, sizeof(tDriverInfo), &tDriverInfo);
  if(lRet == CIFX_NO_ERROR)
  {
    printf("Driver Version: %s\n", tDriverInfo.abDriverVersion);
  }
  else
  {
    ShowError(lRet);
  }
  printf("\n");
}

/*****************************************************************************/
/*! Shows board information
*   \param  hDriver    Driver handle                                          */
/*****************************************************************************/
void ShowBoardInfo(CIFXHANDLE hDriver)
{
  printf("=== Board Information ===\n");
  
  unsigned long ulBoardIdx = 0;
  int32_t lBoardRet = CIFX_NO_ERROR;
  
  while(lBoardRet == CIFX_NO_ERROR)
  {
    BOARD_INFORMATION tBoardInfo = {0};
    lBoardRet = xDriverEnumBoards(hDriver, ulBoardIdx, sizeof(tBoardInfo), &tBoardInfo);
    
    if(lBoardRet == CIFX_NO_ERROR)
    {
      printf("Board %lu:\n", ulBoardIdx);
      printf("  Name: %s\n", tBoardInfo.abBoardName);
      printf("  Alias: %s\n", tBoardInfo.abBoardAlias);
      printf("  Device Number: %lu\n", tBoardInfo.tSystemInfo.ulDeviceNumber);
      printf("  Serial Number: %lu\n", tBoardInfo.tSystemInfo.ulSerialNumber);
      printf("\n");
      
      // Show channel information
      unsigned long ulChannelIdx = 0;
      int32_t lChannelRet = CIFX_NO_ERROR;
      
      while(lChannelRet == CIFX_NO_ERROR)
      {
        CHANNEL_INFORMATION tChannelInfo = {{0}};
        lChannelRet = xDriverEnumChannels(hDriver, ulBoardIdx, ulChannelIdx, sizeof(tChannelInfo), &tChannelInfo);
        
        if(lChannelRet == CIFX_NO_ERROR)
        {
          printf("  Channel %lu:\n", ulChannelIdx);
          printf("    Channel Error: 0x%08X\n", tChannelInfo.ulChannelError);
          printf("    Board Name: %s\n", tChannelInfo.abBoardName);
          printf("    Firmware: %s\n", tChannelInfo.abFWName);
          printf("    FW Version: %d.%d.%d Build %d\n", 
                 tChannelInfo.usFWMajor, tChannelInfo.usFWMinor,
                 tChannelInfo.usFWRevision, tChannelInfo.usFWBuild);
          printf("    Mailbox Size: %lu\n", tChannelInfo.ulMailboxSize);
          printf("    I/O Input Areas: %lu\n", tChannelInfo.ulIOInAreaCnt);
          printf("    I/O Output Areas: %lu\n", tChannelInfo.ulIOOutAreaCnt);
          printf("    netX Flags: 0x%08X\n", tChannelInfo.ulNetxFlags);
          printf("    Host Flags: 0x%08X\n", tChannelInfo.ulHostFlags);
          printf("\n");
        }
        ++ulChannelIdx;
      }
    }
    ++ulBoardIdx;
  }
}

/*****************************************************************************/
/*! Tests I/O communication with COMX51
*   \param  hDriver    Driver handle                                          */
/*****************************************************************************/
void TestIOCommunication(CIFXHANDLE hDriver)
{
  printf("=== I/O Communication Test ===\n");
  
  CIFXHANDLE hChannel = NULL;
  char boardName[] = BOARD_NAME;
  int32_t lRet = xChannelOpen(hDriver, boardName, 0, &hChannel);
  
  if(lRet != CIFX_NO_ERROR)
  {
    printf("Error opening channel!\n");
    ShowError(lRet);
    return;
  }
  
  printf("Channel opened successfully!\n");
  
  // Configure host state
  uint32_t ulState = 0;
  lRet = xChannelHostState(hChannel, CIFX_HOST_STATE_READY, &ulState, TIMEOUT_MS);
  if(lRet != CIFX_NO_ERROR)
  {
    printf("Error configuring host state!\n");
    ShowError(lRet);
  }
  else
  {
    printf("Host configured as READY\n");
  }
  
  // Configure bus state
  lRet = xChannelBusState(hChannel, CIFX_BUS_STATE_ON, &ulState, TIMEOUT_MS);
  if(lRet != CIFX_NO_ERROR)
  {
    printf("Error configuring bus state!\n");
    ShowError(lRet);
  }
  else
  {
    printf("Bus configured as ON\n");
  }
  
  printf("\nStarting I/O cycle...\n");
  printf("Press 'Q' to stop\n\n");
  
  int cycle = 0;
  while(!_kbhit() || _getch() != 'q')
  {
    cycle++;
    
    // Read input data (from PLC to COMX51)
    lRet = xChannelIORead(hChannel, 0, 0, sizeof(g_abInputBuffer), g_abInputBuffer, TIMEOUT_MS);
    if(lRet != CIFX_NO_ERROR)
    {
      printf("Error reading input data: 0x%08X\n", lRet);
      ShowError(lRet);
    }
    else
    {
      printf("Cycle %d - Input: ", cycle);
      for(int i = 0; i < 8; i++) // Show first 8 bytes
      {
        printf("0x%02X ", g_abInputBuffer[i]);
      }
      printf("...\n");
    }
    
    // Prepare output data (from COMX51 to PLC)
    // Simulate output data by incrementing
    g_abOutputBuffer[0] = cycle & 0xFF;
    g_abOutputBuffer[1] = (cycle >> 8) & 0xFF;
    
    // Write output data
    lRet = xChannelIOWrite(hChannel, 0, 0, sizeof(g_abOutputBuffer), g_abOutputBuffer, TIMEOUT_MS);
    if(lRet != CIFX_NO_ERROR)
    {
      printf("Error writing output data: 0x%08X\n", lRet);
      ShowError(lRet);
    }
    else
    {
      printf("Cycle %d - Output: ", cycle);
      for(int i = 0; i < 8; i++) // Show first 8 bytes
      {
        printf("0x%02X ", g_abOutputBuffer[i]);
      }
      printf("...\n");
    }
    
    printf("---\n");
    
    // Wait a bit
    Sleep(1000);
  }
  
  // Clear state
  lRet = xChannelHostState(hChannel, CIFX_HOST_STATE_NOT_READY, &ulState, TIMEOUT_MS);
  if(lRet != CIFX_NO_ERROR)
  {
    printf("Error clearing host state!\n");
    ShowError(lRet);
  }
  
  xChannelClose(hChannel);
  printf("I/O test finished!\n\n");
}

/*****************************************************************************/
/*! Main function
*   \return 0                                                                */
/*****************************************************************************/
int main()
{
  CIFXHANDLE hDriver = NULL;
  
  printf("========================================\n");
  printf("  COMX51 I/O Test - PROFINET\n");
  printf("========================================\n\n");
  
  printf("Starting program...\n");
  printf("Checking available DLLs...\n\n");
  
  // Test netXSPMUSB DLL directly
  bool bDllOk = TestDllLoad("netXSPMUSB.dll");
  printf("\n");
  
  if(!bDllOk )
  {
    printf("ERROR: No DLL was loaded correctly!\n");
    printf("Check if DLLs are in the current directory.\n");
    printf("Press any key to exit...\n");
    (void)_getch();
    return -1;
  }
  
  printf("Checking if cifX driver is available...\n");
  
  // Open driver
  printf("Opening cifX driver...\n");
  int32_t lRet = xDriverOpen(&hDriver);
  if(lRet != CIFX_NO_ERROR)
  {
    printf("ERROR: Failed to open cifX driver!\n");
    printf("Error code: 0x%08X\n", lRet);
    ShowError(lRet);
    printf("\nPossible solutions:\n");
    printf("1. Check if cifX driver is installed\n");
    printf("2. Run as administrator\n");
    printf("3. Check if COMX51 is connected\n");
    printf("\nPress any key to exit...\n");
    (void)_getch();
    return -1;
  }
  
  printf("cifX driver opened successfully!\n\n");
  
  // Show driver information
  ShowDriverInfo(hDriver);
  
  // Show board information
  ShowBoardInfo(hDriver);
  
  // Test I/O communication
  TestIOCommunication(hDriver);
  
  // Close driver
  xDriverClose(hDriver);
  
  printf("Program finished!\n");
  printf("Press any key to exit...\n");
  (void)_getch();
  
  return 0;
} 