//---------------------------------------------------------------------------------------------
// ** CreateDialogBox.cpp
//---------------------------------------------------------------------------------------------
// Author: keejelo
// Github: https://github.com/keejelo/c_cpp_and_winapi_wrappers/tree/master/files/win32
//---------------------------------------------------------------------------------------------
// This creates a dialog template which is used as an empty skeleton dialog (without content).
// The dialog content must be created, dynamically with code, within its own Dialog Procedure
// in its "WM_INITDIALOG". Each dialog needs to have its own Dialog Procedure and handle all 
// its action there, as you normally do.
//
// The thought behind this is to have a common template for smaller dialogs and then create
// all the dialog controls by code. Of course it can be used for larger dialogs too, with lots
// of controls etc., if you enjoy coding then you can do it!  :)
// If so, you can use "Controls.cpp" to create controls quick and easy!
//
// NOTE: See bottom of this file on how to implement and use.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "CreateDialogBox.h"

#include <stdio.h>


//---------------------------------------------------------------------------------------------
// ** Dialog template
//---------------------------------------------------------------------------------------------
#define DLGFONT      L"MS Shell Dlg"
#define NUMCHARS(aa) (sizeof(aa)/sizeof((aa)[0]))

struct DialogTemplate
{
    DWORD style = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_MODALFRAME | DS_SETFOREGROUND | DS_SETFONT;
    DWORD dwExtendedStyle = 0;
    WORD  cDlgItems = 0;
    short x, y, w, h = 0;
    WORD  menu = 0;
    WORD  windowClass = 0;
    WCHAR wszTitle[255] = { 0 };
    short pointsize = 8;   
    WCHAR wszFont[NUMCHARS(DLGFONT)];
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog template
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create Dialogbox | this creates a dialogbox from the template | shorthand: DlgBox( ... )
//---------------------------------------------------------------------------------------------
HWND CreateDialogBox(HWND hWndParent, LPCWSTR sTitle, int iWidth, int iHeight, DLGPROC DlgProc, bool bModal, bool bCenterWindow, int xPos, int yPos)
{
    HWND hDlg = NULL;
    DialogTemplate dt; 
    
    // ** Calculate center dialog
    if (bCenterWindow)
    {
        // ** Get parent window dimensions, and set x and y
        RECT rc = { 0 };
        GetWindowRect(hWndParent, &rc);
        xPos = ((rc.left + rc.right) / 2) - (iWidth / 2);
        yPos = ((rc.top + rc.bottom) / 2) - (iHeight / 2);
    }

    // ** Modal ?
    if (bModal)
    {
        int bufSize = 256;
        dt.wszTitle[bufSize] = { 0 };

        // ** Set title
        for (int i = 0; i < bufSize; i++)
        {
            dt.wszTitle[i] = sTitle[i];

            if (sTitle[i] == '\0')
            {
                break;
            }
        }

        // ** Center dialog ? (modal way; this centers the dialog in screen center, not parent window center)
        if (bCenterWindow)
        {
            dt.style |= DS_CENTER;
        }
        else
        {
            dt.x = xPos;
            dt.y = yPos;
        }

        // ** Convert pixels into DLU (dialog units), seems to work ok on different resolutions and systems. It's the best I've got for now for setting width and height,
        //    Alternatively we can use "SetModal" in dialog proc. WM_INITDIALOG to set this info in an alternative way, but then: #include "CreatDialog.h" in your dialog file.
        LONG units = GetDialogBaseUnits();
        dt.w = MulDiv(LOWORD(units), iWidth, 16);
        dt.h = MulDiv(HIWORD(units), iHeight, 42);

        // ** Since this is a modal we pass a struct along with the "LPARAM" in below code ( ... (LPARAM)&modalinfo); )
        MODALINFO modalinfo{ sTitle, xPos, yPos, iWidth, iHeight }; // so we can use "SetModal" in dialog proc. WM_INITDIALOG to set this info that way if we want (optional)

        // ** Create a modal dialog with the template above
        INT_PTR nDlg = DialogBoxIndirectParam((HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE), (LPCDLGTEMPLATE)&dt, hWndParent, DlgProc, (LPARAM)&modalinfo);

        if (nDlg == -1)
        {
            MessageBox(NULL, "Modal Dialog creation failed!\n\nReturn value: -1", "Error", MB_ICONEXCLAMATION);
        }

        return (HWND)nDlg; // we try casting the returned INT_PTR to HWND, so we can return it to the outside, if we need it.
    }
    else
    {
        // ** Create a modeless dialog with the template above
        hDlg = CreateDialogIndirect((HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE), (LPCDLGTEMPLATE)&dt, hWndParent, DlgProc);

        if (hDlg != NULL)
        {
            // ** Since this is not modal and we have a window handle, we can set title, position and size here, much easier.
            SetWindowTextW(hDlg, sTitle);
            SetWindowPos(hDlg, 0, xPos, yPos, iWidth, iHeight, 0);
        }
        else
        {
            MessageBox(NULL, "Dialog creation failed!\n\nReturn value: NULL", "Error", MB_ICONEXCLAMATION);
            return 0;
        }
    }

    // ** Return handle
    return hDlg;
};
//---------------------------------------------------------------------------------------------
// ** END: Create Dialogbox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** DlgBox | shorthand for: CreateDialogBox( ... )
//---------------------------------------------------------------------------------------------
HWND DlgBox(HWND hWndParent, LPCWSTR sTitle, int iWidth, int iHeight, DLGPROC DlgProc, bool bModal, bool bCenterWindow, int xPos, int yPos)
{
    return CreateDialogBox(hWndParent, sTitle, iWidth, iHeight, DlgProc, bModal, bCenterWindow, xPos, yPos);
};
//---------------------------------------------------------------------------------------------
// ** END: DlgBox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** SetModal
//---------------------------------------------------------------------------------------------
// Alternative method to set size, position and title to a modal dialog, use it in: WM_INITDIALOG
// If centering, it sets the dialog center to parent window and not desktop like the default method does.
void SetModal(HWND hDlgWnd, LPARAM lParam)
{
    MODALINFO *mi = (MODALINFO*)lParam;
    SetWindowTextW(hDlgWnd, mi->s);
    SetWindowPos(hDlgWnd, 0, mi->x, mi->y, mi->w, mi->h, 0);
};
//---------------------------------------------------------------------------------------------
// ** END: SetModal
//---------------------------------------------------------------------------------------------


/*
///////////////////////////////////////////////////////////////////////////////////////////////
// ** HOW TO USE AND IMPLEMENT:
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
// STEP 1: 
///////////////////////////////////////////////////////////////////////////////////////////////
// Create a dialog procedure, this can be in its own file i.e. "MyDlg.cpp" and "MyDlg.h", 
// if so, then you need to include it (#include "MyDlg.h") wherever you are going to use it,
// as you normally do with header files.
///////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------
// ** Dialog procedure (modeless)
//---------------------------------------------------------------------------------------------
INT_PTR CALLBACK MyDlgProc(HWND hDlgWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:      // <-- IDOK captures ENTER key, default dialog "OK" (also works in EditBox) "submit".
                    // do something here
                    return TRUE;

                case IDCANCEL:  // <-- IDCANCEL captures ESC key, default dialog CANCEL
                    DestroyWindow(hDlgWnd);
                    return TRUE;

                case ID_BUTTON1:
                    // do something here
                    return TRUE;

                case ID_BUTTON2:
                    // do something here
                    return TRUE;
            }
            return TRUE;

        case WM_CLOSE:
            DestroyWindow(hDlgWnd);
            return TRUE;

        case WM_INITDIALOG:
        {
            // ** Create some controls when dialog starts
            HWND hEdit = CreateEditCtrl(hDlgWnd, ID_EDITBOX, "", 10, 10, 100);
            CreateButtonCtrl(hDlgWnd, ID_BUTTON1, "Hello", 10, 50);
            CreateButtonCtrl(hDlgWnd, ID_BUTTON2, "world", 130, 50);

            SetFocus(hEdit);   // Set focus to edit control when opening

            return TRUE;
        }
    }

    return FALSE; // Give control back to OS so it can process other messages
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog procedure
//---------------------------------------------------------------------------------------------



///////////////////////////////////////////////////////////////////////////////////////////////
// STEP 2: DO THIS IN YOUR MAIN WINDOW PROCEDURE (usually in "WinMain.cpp" or "main.cpp")
///////////////////////////////////////////////////////////////////////////////////////////////


HWND g_hMyDlg;      // <--- Global handle to your dialog window, somewhere in a global place


//---------------------------------------------------------------------------------------------
// ** Main window procedure (WinMain message handler)
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
        {
            switch (wParam)
            {
                case ID_OPEN_DIALOG:  // some menu item with control id: ID_OPEN_DIALOG

                    // ** Create and open modeless dialog
                    g_hMyDlg = DlgBox(hWnd, "My find dialog", 238, 130, MyDlgProc);  // <-------  modeless (default), returns a window handle HWND

                    // ** Create and open modal dialog
                    // DlgBox(hWnd, "My find dialog", 238, 130, MyDlgProc, true);    // <-------  true = modal (returns HWND that you can cast into an integer if you need it)

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
                    ShowWindow(g_hMyDlg, SW_HIDE);  // <-------  add this, if you want the dialog to follow parent window when minimized
                    break;

                case SIZE_RESTORED:
                    ShowWindow(g_hMyDlg, SW_SHOW);  // <-------  add this, if you want the dialog to follow parent window when restored.
                    break                                        // Be sure to close modeless dialogs with "DestroyWindow", or else it
            }                                                    // can popup again on "SIZE_RESTORED" (if you closed it with just "EndDialog")
            break;                                               // "DestroyWindow" also cleans up after us so we don't leak memory.
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
// ** END: Main window procedure (WinMain message handler)
//---------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////////
//  STEP 3: CHANGE/ADD TO YOUR WINMAIN FUNCTION (MESSAGE LOOP) LIKE BELOW:
//          (usually located at the bottom in "WinMain")
///////////////////////////////////////////////////////////////////////////////////////////////
    

    // ** The message loop  (WinMain function)

    while (GetMessage(&msg, NULL, 0, 0) > 0) 
    {
        if (!g_hMyDlg || !IsDialogMessage(g_hMyDlg, &msg))   // <--- Enables dialog to catch tabstop and keypresses for controls !!!
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
// DONE!
///////////////////////////////////////////////////////////////////////////////////////////////
*/

