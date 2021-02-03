//---------------------------------------------------------------------------------------------
// ** SearchDialog.cpp
//---------------------------------------------------------------------------------------------
// Modeless dialog created for search, uses "DialogTemplate.rc" dialog skeleton.
// Controls and all other stuff is created with code.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SearchDialog.h"
#include "Resource.h"      // <---- contains ID's
#include "Controls.h"      // <---- create controls easier


//---------------------------------------------------------------------------------------------
// ** Dialog procedure (message handler)
//---------------------------------------------------------------------------------------------
BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hEdit = NULL;

    switch (msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:      // <-- This captures ENTER key, default dialog OK (also works in EditBox)
                    ValidateSearch(hWnd);
                    return 1;

                case IDCANCEL:  // <-- This captures ESC key, default dialog CANCEL
                    EndDialog(hWnd, 0);
                    return 1;

                case ID_SEARCH_BTN_OK:
                    ValidateSearch(hWnd);
                    return 1;

                case ID_SEARCH_BTN_CANCEL:
                    EndDialog(hWnd, 0);
                    return 1;
            }
            break;

        case WM_CLOSE:
            EndDialog(hWnd, 0);
            return 1;

        case WM_INITDIALOG:
        {
            // ** Create some controls
            hEdit = CreateEditCtrl(hWnd, ID_SEARCH_TXT, "", 10, 10, 100);
            CreateButtonCtrl(hWnd, ID_SEARCH_BTN_OK, "OK", 10, 50);
            CreateButtonCtrl(hWnd, ID_SEARCH_BTN_CANCEL, "Cancel", 130, 50);

            SetFocus(hEdit);  // Set focus to edit control when opening
            EnumChildWindows(hWnd, SetCtrlFont, 0);  // Set font to DEFAULT_GUI

            ShowWindow(hWnd, SW_SHOW);

            return 1;
        }
        default:
            return 0;  // Give control back to OS so it can process other messages
    }

    return 0;
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog procedure (message handler)
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

    HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(ID_DIALOG_TEMPLATE), hWndParent, DlgProc);

    if (hDlg == NULL)
    {
        MessageBox(NULL, "Dialog creation failed!", "Error", MB_ICONEXCLAMATION);
        return 0;
    }

    SetWindowText(hDlg, sTitle);
    SetWindowPos(hDlg, 0, xPos, yPos, iWidth, iHeight, 0);

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
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Set default gui font to all controls
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Validate search input
//---------------------------------------------------------------------------------------------
void ValidateSearch(HWND hWnd)
{
    char str[255] = { 0 };
    GetDlgItemText(hWnd, ID_SEARCH_TXT, str, sizeof(str));

    if (strlen(str) == 0)
    {
        MessageBox(hWnd, "Search string cannot be empty!", "Error", MB_ICONEXCLAMATION);
        SetFocus(GetDlgItem(hWnd, ID_SEARCH_TXT));
    }
    else
    {
        SendMessage(hWnd, WM_CLOSE, NULL, NULL);
        SearchList(str);  // <----- Extern function that searches for a string
    }
};
//---------------------------------------------------------------------------------------------
// ** END: Validate search input
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
        case WM_COMMAND:
        {
            // ** Parse menu selections
            switch (wParam)
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


// AND CHANGE YOUR MAIN MESSAGE LOOP LIKE BELOW:


while (GetMessage(&msg, NULL, 0, 0) > 0) 
{
    if (!g_hMyDlg || !IsDialogMessage(g_hMyDlg, &msg))   // <--- Enables dialog to catch tabstop and keypresses for controls !!!!!!!!!!
    {
        // accelerator etc and what not

        TranslateMessage(&msg);			 // Translate keyboard messages
        DispatchMessage(&msg);			 // Return control to Windows (OS)
    }
}

return (int)msg.wParam;


*/
