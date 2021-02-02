//---------------------------------------------------------------------------------------------
// ** SearchDialog.cpp
//---------------------------------------------------------------------------------------------
// Modeless dialog created for search, based on "ModelessDialog.cpp", but more detailed and
// functional.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SearchDialog.h"
#include "Resource.h"      // <---- contains ID's
#include "Controls.h"      // <---- for creating controls
#include <vector>


//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------
WNDPROC g_DefEditProc;       // variable that holds the default message proc for child control
WNDPROC g_DefOkBtnProc;      // variable that holds the default message proc for child control
WNDPROC g_DefCancelBtnProc;  // variable that holds the default message proc for child control

size_t iTabFocusIndex = 0;          // index that holds the current control in focus
std::vector<HWND> vDialogControls;  // vector that holds all dialog controls


//---------------------------------------------------------------------------------------------
// ** Function that adds all controls to a vector for indexing
//---------------------------------------------------------------------------------------------
BOOL CALLBACK EnableTabKey(HWND hWnd, LPARAM lParam)
{
    vDialogControls.push_back(hWnd);
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Function that adds all controls to a vector for indexing
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Custom TAB key function to move focus between controls
//---------------------------------------------------------------------------------------------
void TabFocus(bool bUpDown)
{
    if (bUpDown)
    {
        if (iTabFocusIndex < (vDialogControls.size() - 1) )
        {
            SetFocus(vDialogControls[iTabFocusIndex + 1]);
            iTabFocusIndex++;
        }
        else
        {
            SetFocus(vDialogControls[0]);
            iTabFocusIndex = 0;
        }
    }
    else
    {
        if (iTabFocusIndex >= 1)
        {
            SetFocus(vDialogControls[iTabFocusIndex - 1]);
            iTabFocusIndex--;
        }
        else
        {
            SetFocus(vDialogControls[(vDialogControls.size() - 1)]);
            iTabFocusIndex = (vDialogControls.size() - 1);
        }
    }
};
//---------------------------------------------------------------------------------------------
// ** END: Custom TAB key function to move focus between controls
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Dialogbox window procedure (message handler for dialog window)
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hEdit = NULL;
    HWND hOkBtn = NULL;
    HWND hCancelBtn = NULL;

    switch (msg)
    {
        case WM_CREATE:
        {
            // ** Create some controls
            hEdit      = CreateEditCtrl(hWnd, ID_SEARCH_TXT, "", 10, 10, 100);
            hOkBtn     = CreateButtonCtrl(hWnd, ID_SEARCH_BTN_OK, "OK", 10, 50);
            hCancelBtn = CreateButtonCtrl(hWnd, ID_SEARCH_BTN_CANCEL, "Cancel", 130, 50);

            SetFocus(hEdit); // Set focus to edit control when opening
            iTabFocusIndex = 0; // Set focus index to ZERO
            vDialogControls.clear(); // Clear vector (in case it's not empty)
            
            EnumChildWindows(hWnd, EnableTabKey, 0); // Enable tabkey for controls
            EnumChildWindows(hWnd, SetCtrlFont, 0);	// Set font to DEFAULT_GUI

            g_DefEditProc      = (WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, (long)EditProc);
            g_DefOkBtnProc     = (WNDPROC)SetWindowLong(hOkBtn, GWL_WNDPROC, (long)OkBtnProc);
            g_DefCancelBtnProc = (WNDPROC)SetWindowLong(hCancelBtn, GWL_WNDPROC, (long)CancelBtnProc);
        }
        break;

        case WM_COMMAND: 
            
            switch (wParam)
            {
                case ID_SEARCH_BTN_OK:
                {
                    ValidateSearch(hWnd);
                    break;
                }

                case ID_SEARCH_BTN_CANCEL:
                    SendMessage(hWnd, WM_CLOSE, NULL, NULL);
                    break;
            }
            break;

        case WM_CLOSE:
            SetWindowLong(hEdit, GWL_WNDPROC, (long)g_DefEditProc);  // Reset the window proc to default (or else errors can occur)
            SetWindowLong(hOkBtn, GWL_WNDPROC, (long)g_DefOkBtnProc);  // Reset the window proc to default (or else errors can occur)
            SetWindowLong(hCancelBtn, GWL_WNDPROC, (long)g_DefCancelBtnProc);  // Reset the window proc to default (or else errors can occur)
            DestroyWindow(hWnd);
            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
};
//---------------------------------------------------------------------------------------------
// ** END: Dialogbox window procedure
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Edit control window procedure (message handler for this control)
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK EditProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_RETURN:
                    ValidateSearch(GetParent(hCtrlWnd));
                    break;

                case VK_ESCAPE:
                    SendMessage(GetParent(hCtrlWnd), WM_CLOSE, NULL, NULL);
                    break;
                
                case VK_TAB:
                    if (GetKeyState(VK_SHIFT) & 0x8000)  // Check if SHIFT key is pressed
                    {
                        TabFocus(0);
                    }
                    else
                    {
                        TabFocus(1);
                    }
                    break;
            }
        }
        break;
    }

    return CallWindowProc(g_DefEditProc, hCtrlWnd, msg, wParam, lParam);
};
//---------------------------------------------------------------------------------------------
// ** END: Edit control window procedure
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Ok Button control window procedure (message handler for this control)
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK OkBtnProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_RETURN:
                    ValidateSearch(GetParent(hCtrlWnd));
                    break;

                case VK_ESCAPE:
                    SendMessage(GetParent(hCtrlWnd), WM_CLOSE, NULL, NULL);
                    break;

                case VK_TAB:
                    if (GetKeyState(VK_SHIFT) & 0x8000)  // Check if SHIFT key is pressed
                    {
                        TabFocus(0);
                    }
                    else
                    {
                        TabFocus(1);
                    }
                    break;
            }
        }
        break;
    }

    return CallWindowProc(g_DefOkBtnProc, hCtrlWnd, msg, wParam, lParam);
};
//---------------------------------------------------------------------------------------------
// ** END: Ok Button control window procedure
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Cancel Button control window procedure (message handler for this control)
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK CancelBtnProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_RETURN:
                case VK_ESCAPE:
                    SendMessage(GetParent(hCtrlWnd), WM_CLOSE, NULL, NULL);
                    break;

                case VK_TAB:
                    if (GetKeyState(VK_SHIFT) & 0x8000)  // Check if SHIFT key is pressed
                    {
                        TabFocus(0);
                    }
                    else
                    {
                        TabFocus(1);
                    }
                    break;
            }
        }
        break;
    }

    return CallWindowProc(g_DefCancelBtnProc, hCtrlWnd, msg, wParam, lParam);
};
//---------------------------------------------------------------------------------------------
// ** END: Cancel Button control window procedure
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Register the dialog (window) 'class'
//---------------------------------------------------------------------------------------------
void RegisterDialogClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = (WNDPROC)DialogProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszClassName = "DialogClass";

    // ** Register the window class
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Dialog window registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
    }
};
//---------------------------------------------------------------------------------------------
// ** END: Register the dialog (window) 'class'
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create Dialogbox
//---------------------------------------------------------------------------------------------
HWND CreateDialogBox(HWND hWndParent, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight)
{
    // ** Get parent window dimensions, position dialog in parent center
    RECT rc = { 0 };
    GetWindowRect(hWndParent, &rc);
    int xPos = ((rc.left + rc.right) / 2) - (iWidth / 2);
    int yPos = ((rc.top + rc.bottom) / 2) - (iHeight / 2);

    // ** Create and show the dialog
    HWND hDlg = CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, "DialogClass", sTitle,
        WS_VISIBLE | WS_SYSMENU | WS_CAPTION,
        xPos, yPos, iWidth, iHeight,
        NULL, NULL, hInstance, NULL);

    return hDlg;
};
//---------------------------------------------------------------------------------------------
// ** END: Create Dialogbox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Set default gui font to all controls
//---------------------------------------------------------------------------------------------
// EnumChildWindows(hWnd, SetCtrlFont, 0);  // <--- Run this at the end of: WM_CREATE
//---------------------------------------------------------------------------------------------
BOOL CALLBACK SetCtrlFont(HWND hWnd, LPARAM lParam)
{
    HFONT hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(TRUE, 0));
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Set default gui font to all controls
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Search 
//---------------------------------------------------------------------------------------------
void ValidateSearch(HWND hWnd)
{
    char str[255] = { 0 };
    GetDlgItemText(hWnd, ID_SEARCH_TXT, str, sizeof(str));

    if (strlen(str) == 0)
    {
        MessageBox(hWnd, "Search string cannot be empty!","Error", MB_ICONEXCLAMATION);
        SetFocus(GetDlgItem(hWnd, ID_SEARCH_TXT));
    }
    else
    {
        SendMessage(hWnd, WM_CLOSE, NULL, NULL);
        SearchList(str);  // <----- Extern function that searches for a string
    }
};
//---------------------------------------------------------------------------------------------
// ** END: Search 
//---------------------------------------------------------------------------------------------





///////////////////////////////////////////////////////////////////////////////////////////////
// ** HOW TO IMPLEMENT
///////////////////////////////////////////////////////////////////////////////////////////////
/*

// ** Do this in your main window procedure

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            RegisterDialogClass(g_hInstance);  // <-------  add this, "g_hInstance" is GLOBAL handle to instance
            break;
        }

        case WM_COMMAND:
        {
            // ** Parse menu selections
            switch (LOWORD(wParam))
            {
                case ID_FIND: // some menu item with control id: ID_FIND
                    // ** Create and open dialog when menu item is clicked, g_hMyDlg is GLOBAL handle to dialog (HWND g_hMyDlg)
                    g_hMyDlg = CreateDialogBox(hWnd, g_hInstance, "My find dialog", 238, 130);  // <-------  add this, "g_hInstance" is GLOBAL handle to instance
                    break;
            }
            break;
        }
        break;

        case WM_SIZE:
        {
            switch (wParam)
            {
                case SIZE_MINIMIZED:
                    ShowWindow(g_hMyDlg, SW_HIDE);  // <-------  add this, "g_hMyDlg" is GLOBAL handle to dialog (HWND g_hMyDlg)
                    break;

                case SIZE_RESTORED:
                    ShowWindow(g_hMyDlg, SW_SHOW);  // <-------  add this, "g_hMyDlg" is GLOBAL handle to dialog (HWND g_hMyDlg)
                    break;
            }
            break;
        }
        break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
};
*/
