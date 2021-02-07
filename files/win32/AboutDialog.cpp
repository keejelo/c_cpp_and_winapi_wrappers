//---------------------------------------------------------------------------------------------
// ** AboutDialog.cpp
//---------------------------------------------------------------------------------------------
// This is just the dialog procedure (dialog message handler).
// The actual dialog is created with the function "DlgBox" (CreateDialogBox.cpp)
// Can be invoked like this, which creates and opens the dialog:
// DlgBox(hWnd, L"About", 286, 120, AboutDlgProc, true); // <-- true = modal
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "AboutDialog.h"
#include "Controls.h"         // <--- create controls easier


//---------------------------------------------------------------------------------------------
// ** Dialog procedure (message handler)
//---------------------------------------------------------------------------------------------
INT_PTR CALLBACK AboutDlgProc(HWND hDlgWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:      // <-- This captures ENTER key, default dialog OK 
                    EndDialog(hDlgWnd, wParam);
                    return TRUE;

                case IDCANCEL:  // <-- This captures ESC key, default dialog CANCEL
                    EndDialog(hDlgWnd, wParam);
                    return TRUE;
            }
            return TRUE;

        case WM_CLOSE:
            EndDialog(hDlgWnd, wParam);
            return TRUE;

        case WM_INITDIALOG:
        {   
            // ** Create some controls
            HWND hText = CreateStaticTextCtrl(hDlgWnd, "This is the about dialog!", 20, 20);
            HWND hOkBtn = CreateButtonCtrl(hDlgWnd, IDOK, "OK", 212, 55, 30);

            // ** Set default gui font to controls
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            SendMessage(hText, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
            SendMessage(hOkBtn, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

            // ** Set focus to button
            SetFocus(hOkBtn);

            return TRUE;
        }
    }

    return FALSE; // Give control back to OS so it can process other messages
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog procedure (message handler)
//---------------------------------------------------------------------------------------------
