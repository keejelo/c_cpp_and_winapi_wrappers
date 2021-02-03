//---------------------------------------------------------------------------------------------
// ** Dialog.cpp
//---------------------------------------------------------------------------------------------
// Wrapper for CreateDialog, uses file "DialogTemplate.rc" for creating dialog skeleton.
// The dialog content are created in their own custom dialog procedure in "WM_INITDIALOG".
// Each dialog needs to have its own dialog procedure and handle all its action there.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "Dialog.h"


//---------------------------------------------------------------------------------------------
// ** Create Dialogbox
//---------------------------------------------------------------------------------------------
HWND CreateDialogBox(HWND hWndParent, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc)
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





/*
///////////////////////////////////////////////////////////////////////////////////////////////
// ** HOW TO USE AND IMPLEMENT:
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
// STEP 1: Create a dialog procedure, here you tell what the dialog is going to do.
//         This can be in its own file i.e. "MyDlg.cpp" and "MyDlg.h", if so you of course then
//         need to include it (#include "MyDlg.h") wherever you are going to use it.
///////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------
// ** Dialog procedure (message handler)
//---------------------------------------------------------------------------------------------
BOOL CALLBACK MyDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:      // <-- This captures ENTER key, default dialog OK (also works in EditBox)
                    // do something here
                    return 1;

                case IDCANCEL:  // <-- This captures ESC key, default dialog CANCEL
                    EndDialog(hWnd, 0);
                    return 1;

                case ID_BUTTON1:
                    // do something here
                    return 1;

                case ID_BUTTON2:
                    // do something here
                    return 1;
            }
            return 1;

        case WM_CLOSE:
            EndDialog(hWnd, 0);
            return 1;

        case WM_INITDIALOG:
        {
            // ** Create some controls when dialog starts
            HWND hEdit = CreateEditCtrl(hWnd, ID_EDITBOX, "", 10, 10, 100);
            CreateButtonCtrl(hWnd, ID_BUTTON1, "OK", 10, 50);
            CreateButtonCtrl(hWnd, ID_BUTTON2, "Cancel", 130, 50);

            SetFocus(hEdit);  // Set focus to edit control when opening
            ShowWindow(hWnd, SW_SHOW);  // Show dialog
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


///////////////////////////////////////////////////////////////////////////////////////////////
// STEP 2: DO THIS IN YOUR MAIN WINDOW PROCEDURE (usually in "WinMain.cpp" or "main.cpp")
///////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------
// ** Main window procedure (message handler)
//---------------------------------------------------------------------------------------------
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

                    g_hMyDlg = CreateDialogBox(hWnd, g_hInstance, "My find dialog", 238, 130, MyDlgProc);  // <-------  add this, "g_hInstance" is GLOBAL handle to instance

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
//---------------------------------------------------------------------------------------------
// ** END: Main window procedure (message handler)
//---------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////////
//  STEP 3: CHANGE/ADD TO YOUR WINMAIN FUNCTION (MESSAGE LOOP) LIKE BELOW:
//          (usually at the bottom in "WinMain.cpp" or "main.cpp")
///////////////////////////////////////////////////////////////////////////////////////////////
    
    // above here (WinMain function) is window created etc.

    // ** The message loop

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

};

//---------------------------------------------------------------------------------------------
// ** END: WinMain function
//---------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////////
// DONE! Good luck!
///////////////////////////////////////////////////////////////////////////////////////////////
*/
