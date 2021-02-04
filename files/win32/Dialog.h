#pragma once
//---------------------------------------------------------------------------------------------
// ** Dialog.h
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Defines
//---------------------------------------------------------------------------------------------
#ifndef DIALOG_H
#define DIALOG_H
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
HWND CreateDialogBox(HWND hParentWnd, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, int xPos = 0, int yPos = 0, bool bCenterWindow = true);
HWND DlgBox(HWND hParentWnd, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, int xPos = 0, int yPos = 0, bool bCenterWindow = true);


//---------------------------------------------------------------------------------------------
#endif // DIALOG_H
//---------------------------------------------------------------------------------------------
