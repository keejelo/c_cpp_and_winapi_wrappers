//---------------------------------------------------------------------------------------------
// ** SearchDialog.cpp
//---------------------------------------------------------------------------------------------
// This is just the dialog procedure (dialog message handler).
// The actual dialog is created with the function "DlgBox" (CreateDialogBox.cpp)
// Can be invoked like this, which creates and opens the dialog:
// DlgBox(hWnd, L"Find", 238, 130, SearchDlgProc);
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "SearchDialog.h"
#include "Resource.h"      // <---- contains ID's
#include "Controls.h"      // <---- create controls easier


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
BOOL CALLBACK SetCtrlFont(HWND hWnd, LPARAM lParam);
void ValidateSearch(HWND hWnd);


//---------------------------------------------------------------------------------------------
// ** Dialog procedure (message handler)
//---------------------------------------------------------------------------------------------
INT_PTR CALLBACK SearchDlgProc(HWND hDlgWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:      // <-- IDOK captures ENTER key, default dialog OK (also works in EditBox)
                    ValidateSearch(hDlgWnd);
                    return TRUE;

                case IDCANCEL:  // <-- IDCANCEL captures ESC key, default dialog CANCEL
                    EndDialog(hDlgWnd, wParam);
                    DestroyWindow(hDlgWnd);
                    return TRUE;

                case ID_SEARCH_BTN_OK:
                    ValidateSearch(hDlgWnd);
                    return TRUE;

                case ID_SEARCH_BTN_CANCEL:
                    EndDialog(hDlgWnd, wParam);
                    DestroyWindow(hDlgWnd);
                    return TRUE;
            }
            return TRUE;

        case WM_CLOSE:
            EndDialog(hDlgWnd, wParam);
            DestroyWindow(hDlgWnd);
            return TRUE;

        case WM_INITDIALOG:
        {
            // ** Create some controls
            HWND hEdit = CreateEditCtrl(hDlgWnd, ID_SEARCH_TXT, "", 10, 10, 100);
            CreateButtonCtrl(hDlgWnd, ID_SEARCH_BTN_OK, "OK", 10, 50);
            CreateButtonCtrl(hDlgWnd, ID_SEARCH_BTN_CANCEL, "Cancel", 130, 50);

            SetFocus(hEdit);  // Set focus to edit control when opening
            EnumChildWindows(hDlgWnd, SetCtrlFont, 0);  // Set font to DEFAULT_GUI

            return TRUE;
        }
    }

    return FALSE; // Give control back to OS so it can process other messages
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog procedure (message handler)
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Set default gui font to all controls
//---------------------------------------------------------------------------------------------
// EnumChildWindows(hWnd, SetCtrlFont, 0);  // <--- Run this after creating controls
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
