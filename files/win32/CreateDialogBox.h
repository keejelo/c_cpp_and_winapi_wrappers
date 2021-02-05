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
struct MODALINFO { const char *s; int x; int y; int w; int h; };


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------

// ** CreateDialogBox | shorthand: DlgBox( ... ) 
HWND CreateDialogBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc,
                     bool bModal = false, int xPos = 0, int yPos = 0, bool bCenterWindow = true);

// ** DlgBox | shorthand for: CreateDialogBox ( ... )
HWND DlgBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, 
            bool bModal = false, int xPos = 0, int yPos = 0, bool bCenterWindow = true);

// ** SetModal | setting the size, position and title of a modal dialog, use it in: WM_INITDIALOG
void SetModal(HWND hDlgWnd, LPARAM lParam);

//---------------------------------------------------------------------------------------------
#endif // CREATE_DIALOG_BOX_H
//---------------------------------------------------------------------------------------------
