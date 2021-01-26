//---------------------------------------------------------------------------------------------
// ** Tooltip.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** INCLUDE FILES
//---------------------------------------------------------------------------------------------
#include "Tooltip.h"
#include <commctrl.h>


//---------------------------------------------------------------------------------------------
// ** Import library (Common Controls)
//---------------------------------------------------------------------------------------------
#pragma comment(lib, "comctl32.lib")


//---------------------------------------------------------------------------------------------
// ** Create a tooltip for a control
//---------------------------------------------------------------------------------------------
HWND CreateToolTip(HWND hParentWnd, /*int ctrlID,*/ HWND hWndCtrl, LPTSTR lpszText)
{
     // ** Initialize Common Controls
    INITCOMMONCONTROLSEX cc;
    cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    cc.dwICC = ICC_TAB_CLASSES | ICC_BAR_CLASSES;
    InitCommonControlsEx(&cc);

    // ** Max-width (pixels) before newline occurs
    int iMaxWidth = 300;

    // ** Delay time (seconds) before the tooltip disappears
    int iDelayTime = 2;
        
    // ** Get the control and set the tooltip
    HWND hWndTool = hWndCtrl;  
    /* HWND hWndTool = GetDlgItem(hParentWnd, ctrlID); */

    // ** Create tooltip
    HWND hWndTip = NULL;
    
    // ** Create control
    hWndTip = CreateWindowEx(
        WS_EX_TOPMOST, 
        TOOLTIPS_CLASS,
        NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, // | TTS_BALLOON,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        hParentWnd,
        NULL, 
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE), // Handle to the instance of the module
        NULL);

    if (!hWndTool || !hWndTip)
    {
        return (HWND)NULL;
    }                              

    // ** Associate the tooltip with control
    TOOLINFO toolInfo = { 0 };
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.hwnd = hParentWnd;
    toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    toolInfo.uId = (UINT_PTR)hWndTool;
    toolInfo.lpszText = lpszText;
    SendMessage(hWndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
    
    // ** Set the default max-width
    SendMessage(hWndTip, TTM_SETMAXTIPWIDTH, 0, iMaxWidth);

    // ** Set the default delay time
    SendMessage(hWndTip, TTM_SETDELAYTIME, TTDT_AUTOPOP, MAKELPARAM((iDelayTime * 1000), (0)));

    // ** Return
    return hWndTip;
};
//---------------------------------------------------------------------------------------------
// ** END: Create a tooltip for a control
//---------------------------------------------------------------------------------------------


/*
// EXAMPLE USAGE:

#include "Tooltip.h"

 // ... 

void OnCreate(HWND hWnd)
{
    // ** First create a control
    HWND myBtn = CreateWindow( ...blablabla );

    // ** Then create a tooltip and attach it to the control you just created
    HWND hTooltip = CreateToolTip(hWnd, myBtn, (LPTSTR)"This is a button");

    // Done!
};


*/
