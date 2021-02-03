#pragma once
//---------------------------------------------------------------------------------------------
// ** Dialog.h
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Defines
//---------------------------------------------------------------------------------------------
#define ID_DIALOG_TEMPLATE    10001
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
HWND CreateDialogBox(HWND hWnd, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc);


//---------------------------------------------------------------------------------------------
#endif // DIALOG_H
//---------------------------------------------------------------------------------------------
