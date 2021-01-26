//---------------------------------------------------------------------------------------------
// ** Status.cpp
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "Status.h"
#include <commctrl.h>


//---------------------------------------------------------------------------------------------
// ** Include libraries
//---------------------------------------------------------------------------------------------
#pragma comment(lib, "comctl32.lib")


//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------
const int NUMPARTS = 3; // <---- this is how many parts (sections) you want in the statusbar
int g_iParts[NUMPARTS]; // <---- an array that holds the total number of parts


//---------------------------------------------------------------------------------------------
// ** Create statusbar
//---------------------------------------------------------------------------------------------
HWND CreateStatusBar(HWND hWnd, int ctrlID)
{
    INITCOMMONCONTROLSEX cc;
    cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    cc.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&cc);

    RECT rc = { 0 };
    GetClientRect(hWnd, &rc);

    for (int i = 1; i <= NUMPARTS; i++)
    {
        g_iParts[i - 1] = rc.right / NUMPARTS * i;
    }
        
    HWND hStatusWnd = CreateWindowEx(
        NULL, 
        STATUSCLASSNAME, 
        "", // default text
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 
        0, 0, 0, 0,
        hWnd,
        (HMENU)ctrlID,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);
    
    SendMessage(hStatusWnd, SB_SETPARTS, (WPARAM)NUMPARTS, (LPARAM)g_iParts);

    return hStatusWnd;
};
//---------------------------------------------------------------------------------------------
// ** END: Create statusbar
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Set statusbar text
//---------------------------------------------------------------------------------------------
void SetStatusBarText(HWND hStatusBarWnd, int iPart, const char *szText)
{
    SendMessage(hStatusBarWnd, SB_SETTEXT, (WPARAM)iPart, (LPARAM)szText);
};
//---------------------------------------------------------------------------------------------
// ** END: Set statusbar text
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Resize statusbar
//---------------------------------------------------------------------------------------------
void ResizeStatusBar(HWND hWnd, HWND hStatusWnd, WPARAM wParam, LPARAM lParam)
{
    SendMessage(hStatusWnd, WM_SIZE, wParam, lParam);

    RECT rc = { 0 };
    GetClientRect(hWnd, &rc);

    for (int i = 1; i <= NUMPARTS; i++)
    {
        g_iParts[i - 1] = rc.right / NUMPARTS * i;
    }

    SendMessage(hStatusWnd, SB_SETPARTS, (WPARAM)NUMPARTS, (LPARAM)g_iParts);
};
//---------------------------------------------------------------------------------------------
// ** END: Resize statusbar
//---------------------------------------------------------------------------------------------




///////////////////////////////////////////////////////////////////////////////////////////////
// ** HOW TO IMPLEMENT
///////////////////////////////////////////////////////////////////////////////////////////////
/*

// ** Do this in your main window procedure

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            // ** Add statusbar
            hStatusBar = CreateStatusBar(hWnd, ID_STATUS);  // <------ add this, hStatusBar is GLOBAL handler to statusbar (HWND hStatusBar)
        }
        break;

        case WM_SIZE:
        {
            ResizeStatusBar(hWnd, hStatusBar, wParam, lParam);   // <------ add this, resizes the statusbar and parts when window is resized
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
};
*/
