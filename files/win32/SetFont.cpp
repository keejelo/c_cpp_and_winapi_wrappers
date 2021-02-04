//---------------------------------------------------------------------------------------------
// ** SetFont.cpp
//---------------------------------------------------------------------------------------------

/*
USAGE: use below code in any function to change font

    EnumChildWindows(ctrl, (WNDENUMPROC)SetFont, (LPARAM)GetStockObject(ANSI_FIXED_FONT));
*/


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SetFont.h"

//---------------------------------------------------------------------------------------------
//** Set ctrl font
//---------------------------------------------------------------------------------------------
bool CALLBACK SetFont(HWND ctrl, LPARAM font)
{
    // Sets only font to first item (i.e. header of listctrl)
    SendMessage(ctrl, WM_SETFONT, font, true); 

    // Sets font to first item (i.e. header of listctrl) and all other childctrls of parent ctrl
    //SendMessage(ctrl, WM_SETFONT, (WPARAM)GetStockObject(ANSI_FIXED_FONT), MAKELPARAM(TRUE, 0));

    return true;
};
//---------------------------------------------------------------------------------------------
