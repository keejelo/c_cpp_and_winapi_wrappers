#pragma once
//---------------------------------------------------------------------------------------------
// ** Tooltip.h
//---------------------------------------------------------------------------------------------
#ifndef TOOLTIP_H
#define TOOLTIP_H
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
HWND CreateToolTip(HWND hParentWnd, /*int toolID,*/ HWND hWndCtrl = NULL, PTSTR pszText = NULL);



//---------------------------------------------------------------------------------------------
#endif // TOOLTIP_H
//---------------------------------------------------------------------------------------------
