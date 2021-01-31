//---------------------------------------------------------------------------------------------
// ** SetFont.h
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SetFont.h"


//---------------------------------------------------------------------------------------------
/*
// https://stackoverflow.com/a/17075471

// Usage: 
// Inside a separate file or just in the main.cpp just run the below whenever you want,
// for example in the WM_CREATE message, after you've created all your child windows and controls.

// ** Set default GUI font (usually Tahoma)
EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));

*/
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
// ** Set font to window/control
//---------------------------------------------------------------------------------------------
bool CALLBACK SetFont(HWND hCtrl, LPARAM font)
{
    SendMessage(hCtrl, WM_SETFONT, font, true);
    return true;
};
//---------------------------------------------------------------------------------------------
// END: Set font to window/control
//---------------------------------------------------------------------------------------------
    
    
    
//---------------------------------------------------------------------------------------------
// ** Set default gui font to all controls
//---------------------------------------------------------------------------------------------
// EnumChildWindows(hWnd, EnumChildProc, 0);  // <--- Run this at the end of: WM_CREATE
//---------------------------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Set default gui font to all controls
//---------------------------------------------------------------------------------------------

