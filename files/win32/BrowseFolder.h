#pragma once
//---------------------------------------------------------------------------------------------
// ** BrowseFolder.h
//---------------------------------------------------------------------------------------------
#ifndef BROWSEFOLDER_H
#define BROWSEFOLDER_H
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** INCLUDE FILES
//---------------------------------------------------------------------------------------------
#include <windows.h>
#include <string>


//---------------------------------------------------------------------------------------------
// ** FUNCTION PROTOTYPES
//---------------------------------------------------------------------------------------------
std::string BrowseFolder(HWND hWnd, std::string strInitialDir = "");
static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
static BOOL CALLBACK EnumCallback(HWND hWndChild, LPARAM lParam);


//---------------------------------------------------------------------------------------------
#endif // BROWSEFOLDER_H
//---------------------------------------------------------------------------------------------
