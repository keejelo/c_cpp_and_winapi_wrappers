//---------------------------------------------------------------------------------------------
// ** AboutDialog.cpp
//---------------------------------------------------------------------------------------------
// This is just the dialog procedure (dialog message handler).
// The actual dialog is created with the function CreateDialogBox (CreateDialogBox.cpp)
// invoked from another place.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "AboutDialog.h"
#include "CreateDialogBox.h"  // <--- for using MODALINFO struct
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
                    EndDialog(hDlgWnd, 0);
                    DestroyWindow(hDlgWnd);
                    return 1;

                case IDCANCEL:  // <-- This captures ESC key, default dialog CANCEL
                    EndDialog(hDlgWnd, 0);
                    DestroyWindow(hDlgWnd);
                    return 1;
            }
            return 1;

        case WM_CLOSE:
            EndDialog(hDlgWnd, 0);
            DestroyWindow(hDlgWnd);
            return 1;

        case WM_INITDIALOG:
        {
            //---------------------------------------------------------------------------------------------
            // ** Since this is a modal dialog, we have to set size, pos, and title with MODALINFO
            //---------------------------------------------------------------------------------------------
            MODALINFO *mi = (MODALINFO*)lParam;
            SetWindowText(hDlgWnd, mi->title);
            SetWindowPos(hDlgWnd, 0, mi->x, mi->y, mi->w, mi->h, 0);
            //---------------------------------------------------------------------------------------------

            // ** Create some controls
            HWND hText = CreateStaticTextCtrl(hDlgWnd, "This is the about dialog!", 20, 20);
            HWND hOkBtn = CreateButtonCtrl(hDlgWnd, IDOK, "OK", mi->w - 87, mi->h - 75, 30);

            // ** Set default gui font to controls
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            SendMessage(hText, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
            SendMessage(hOkBtn, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

            // ** Set focus to button
            SetFocus(hOkBtn);

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
