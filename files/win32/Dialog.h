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
// ** CreateDialogBox | shorthand: DlgBox( ... ) 
HWND CreateDialogBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, int xPos = 0, int yPos = 0, bool bCenterWindow = true);

// ** CreateDialogBoxModal | shorthand: DlgBoxModal( ... )
int  CreateDialogBoxModal(HWND hWndParent, DLGPROC DlgProc);

// ** DlgBox (shorthand for CreateDialogBox)
HWND DlgBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, int xPos = 0, int yPos = 0, bool bCenterWindow = true);

// ** DlgBoxModal (shorthand for CreateDialogBoxModal)
int  DlgBoxModal(HWND hWndParent, DLGPROC DlgProc);



//---------------------------------------------------------------------------------------------
#endif // DIALOG_H
//---------------------------------------------------------------------------------------------
