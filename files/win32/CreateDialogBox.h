#pragma once
//---------------------------------------------------------------------------------------------
// ** CreateDialogBox.h
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Defines
//---------------------------------------------------------------------------------------------
#ifndef CREATE_DIALOG_BOX_H
#define CREATE_DIALOG_BOX_H
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>

//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------

// ** Struct that holds modal dialog information (title, position and size)
struct MODALINFO { LPCWSTR s; int x; int y; int w; int h; };


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------

// ** CreateDialogBox | shorthand: DlgBox( ... ) 
HWND CreateDialogBox(HWND hWndParent, LPCWSTR sTitle, int iWidth, int iHeight, DLGPROC DlgProc, bool bModal = false, bool bCenterWindow = true, int xPos = 0, int yPos = 0);

// ** DlgBox | shorthand for: CreateDialogBox ( ... )
HWND DlgBox(HWND hWndParent, LPCWSTR sTitle, int iWidth, int iHeight, DLGPROC DlgProc, bool bModal = false, bool bCenterWindow = true, int xPos = 0, int yPos = 0);

// ** SetModal | Alternative method to set size, position and title to a modal dialog, use it in your dialog proc.: WM_INITDIALOG
void SetModal(HWND hDlgWnd, LPARAM lParam);


//---------------------------------------------------------------------------------------------
#endif // CREATE_DIALOG_BOX_H
//---------------------------------------------------------------------------------------------
