//---------------------------------------------------------------------------------------------
// ** SearchDialog.cpp
//---------------------------------------------------------------------------------------------
// Modeless dialog created for search, based on "ModelessDialog.cpp", but more detailed.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SearchDialog.h"
#include "Resource.h"      // <---- contains ID's
#include "Controls.h"      // <---- for creating controls


//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------
WNDPROC g_DefEditProc;  // Variable that holds the default message proc for Editbox


//---------------------------------------------------------------------------------------------
// ** Dialogbox window procedure (message handler for dialog window)
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hEdit = NULL;

    switch (msg)
    {
        case WM_CREATE:
        {
            hEdit = CreateEditCtrl(hWnd, ID_SEARCH_TXT, "", 10, 10);
            CreateButtonCtrl(hWnd, ID_SEARCH_BTN_OK, "OK", 10, 50);
            CreateButtonCtrl(hWnd, ID_SEARCH_BTN_CANCEL, "Cancel", 150, 50);
            
            EnumChildWindows(hWnd, EnumDialogChildProc, 0);	// Set control font to DEFAULT_GUI
            
            SetFocus(hEdit); // Set focus to edit control when opening
            
            g_DefEditProc = (WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, (long)EditProc);
        }
        break;

        case WM_COMMAND:
            switch (wParam)
            {
                case ID_SEARCH_BTN_OK:
                    Search(hWnd);
                    break;

                case ID_SEARCH_BTN_CANCEL:
                    SendMessage(hWnd, WM_CLOSE, NULL, NULL);
                    break;
            }
            break;

        case WM_CLOSE:
            SetWindowLong(hEdit, GWL_WNDPROC, (long)g_DefEditProc);  // Reset the window proc to default (or else errors can occur)
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
LRESULT CALLBACK EditProc(HWND hEditWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_KEYDOWN:
        {
            switch ((char)wParam)
            {
                case VK_RETURN:
                    Search(GetParent(hEditWnd));
                    break;
                case VK_ESCAPE:
                    SendMessage(GetParent(hEditWnd), WM_CLOSE, NULL, NULL);
                    break;
            }
        }
        break;
    }

    return CallWindowProc(g_DefEditProc, hEditWnd, msg, wParam, lParam);
};
//---------------------------------------------------------------------------------------------
// ** END: Edit control window procedure
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
// ** Enumerate over all controls and set correct font
//---------------------------------------------------------------------------------------------
BOOL CALLBACK EnumDialogChildProc(HWND hWnd, LPARAM lParam)
{
    HFONT hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(TRUE, 0));
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Enumerate over all controls and set font
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Search 
//---------------------------------------------------------------------------------------------
void Search(HWND hWnd)
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
        SearchList(str);  // <----- EXTERN function that searches for a string
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
                    // ** Create and open dialog when menu item is clicked, hMyDlg is GLOBAL handle to dialog (HWND hMyDlg)
                    hMyDlg = CreateDialogBox(hWnd, g_hInstance, "My find dialog", 300, 200);  // <-------  add this, "g_hInstance" is GLOBAL handle to instance
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
                    ShowWindow(hMyDlg, SW_HIDE);  // <-------  add this, "hMyDlg" is GLOBAL handle to dialog (HWND hMyDlg)
                    break;

                case SIZE_RESTORED:
                    ShowWindow(hMyDlg, SW_SHOW);  // <-------  add this, "hMyDlg" is GLOBAL handle to dialog (HWND hMyDlg)
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
