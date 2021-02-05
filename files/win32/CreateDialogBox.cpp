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
// See bottom of this file on how to implement and use.
//---------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "CreateDialogBox.h"


//---------------------------------------------------------------------------------------------
// ** Dialog template
//---------------------------------------------------------------------------------------------
#define DLGTITLE    L"EMPTY_DIALOG_TEMPLATE"
#define NUMCHARS(a) (sizeof(a)/sizeof((a)[0]))

struct DialogTemplate
{
    DWORD style;
    DWORD dwExtendedStyle;
    WORD  cDlgItems;
    short x;
    short y;
    short w;
    short h;
    WORD  menu;                         
    WORD  windowClass;
    WCHAR wszTitle[NUMCHARS(DLGTITLE)];
} dt =
{
    WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
    | DS_MODALFRAME | DS_SETFOREGROUND,
    0x0,         // exStyle
    0,           // number of controls in dialog
    0, 0, 0, 0,  // x, y, w, h (pos and size of dialog)
    0,           // no menu
    0,           // no window class (0 = dialog)
    DLGTITLE     // dialog window title (default)
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog template
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
// ** Create Dialogbox - this creates a dialogbox from the template | shorthand: DlgBox( ... ) 
//---------------------------------------------------------------------------------------------
// This is the function you use to create your dialogs.
//---------------------------------------------------------------------------------------------
HWND CreateDialogBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, bool bModal, int xPos, int yPos, bool bCenterWindow)
{
    HWND hDlg = NULL;

    // ** Get parent window dimensions, position dialog in parent center
    if (bCenterWindow)
    {
        RECT rc = { 0 };
        GetWindowRect(hWndParent, &rc);
        xPos = ((rc.left + rc.right) / 2) - (iWidth / 2);
        yPos = ((rc.top + rc.bottom) / 2) - (iHeight / 2);
    }

    // ** Modal ?
    if (bModal)
    {
        // ** Since this is a modal we have to pass this struct along with the LPARAM below ( (LPARAM)&modalinfo) )
        MODALINFO modalinfo{sTitle, xPos, yPos, iWidth, iHeight};

        // ** Create a modal dialog with the template above (read below about modal dialog creation)
        INT_PTR nDlg = DialogBoxIndirectParam((HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE), (LPCDLGTEMPLATE)&dt, hWndParent, DlgProc, (LPARAM)&modalinfo);

        if (nDlg == -1)
        {
            MessageBox(NULL, "Modal Dialog creation failed!\n\nReturn value: -1", "Error", MB_ICONEXCLAMATION);
        }
        return 0; // we have to return zero because outside return type is HWND and we come from INT_PTR and we cannot use that, so we just use zero.
    }
    else
    {
        // ** Create a dialog with the template above
        hDlg = CreateDialogIndirect((HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE), (LPCDLGTEMPLATE)&dt, hWndParent, DlgProc);
    }

    if (hDlg == NULL)
    {
        MessageBox(NULL, "Dialog creation failed!\n\nReturn value: NULL", "Error", MB_ICONEXCLAMATION);
        return 0;
    }

    // ** If dialog is not modal, then we can set title, pos and size here
    SetWindowPos(hDlg, 0, xPos, yPos, iWidth, iHeight, 0);
    SetWindowText(hDlg, sTitle);

    // ** Return window handle
    return hDlg;


    /*//-------------------------------------------------------------------
    // IMPORTANT NOTICE ABOUT MODAL DIALOG CREATION
    //---------------------------------------------------------------------
    // Since modal dialogs do not return a window handle: we have to set
    // the dialogs size, position and title in the dialogs own procedure, 
    // "WM_INITDIALOG" like below with MODALINFO, just copy/paste it and
    // you'll be fine, just check that you use the correct window name
    // handle, if "hDlgWnd" is not your dialog window name HWND handle.
    // Also be sure to #include "CreatDialogBox.h" to be able to use it.
    //-------------------------------------------------------------------
        case WM_INITDIALOG:
        {
            MODALINFO *mi = (MODALINFO*)lParam; SetWindowText(hDlgWnd, mi->title);
            SetWindowPos(hDlgWnd, 0, mi->x, mi->y, mi->w, mi->h, 0);


            // ..your other code to create controls and other stuff etc.

            return 1;
        }
    *///--------------------------------------------------------------------
};
//---------------------------------------------------------------------------------------------
// ** END: Create Dialogbox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** DlgBox | shorthand for: CreateDialogBox( ... )
//---------------------------------------------------------------------------------------------
HWND DlgBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, bool bModal, int xPos, int yPos, bool bCenterWindow)
{
    return CreateDialogBox(hWndParent, sTitle, iWidth, iHeight, DlgProc, bModal, xPos, yPos, bCenterWindow);
};
//---------------------------------------------------------------------------------------------
// ** END: DlgBox (shorthand for CreateDialogBox)
//---------------------------------------------------------------------------------------------




/*
///////////////////////////////////////////////////////////////////////////////////////////////
// ** HOW TO USE AND IMPLEMENT:
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
// STEP 1: Create a dialog procedure, here you tell what the dialog is going to do.
//         This can be in its own file i.e. "MyDlg.cpp" and "MyDlg.h", if so, you
//         need to include it (#include "MyDlg.h") wherever you are going to use it.
///////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------------
// ** Dialog procedure (non modal example)(modal is exactly the same but more code in "WM_INITDIALOG")
//---------------------------------------------------------------------------------------------
INT_PTR CALLBACK MyDlgProc(HWND hDlgWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case IDOK:      // <-- This captures ENTER key, default dialog "OK" (also works in EditBox) "submit form"
                    // do something here
                    return 1;

                case IDCANCEL:  // <-- This captures ESC key, default dialog CANCEL
                    EndDialog(hDlgWnd, 0);
                    DestroyWindow(hDlgWnd);
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
            EndDialog(hDlgWnd, 0);
            DestroyWindow(hDlgWnd);
            return 1;

        case WM_INITDIALOG:
        {
            // (If this was a modal dialog we'd have to use MODALINFO struct here also, see above notice!)

            // ** Create some controls when dialog starts
            HWND hEdit = CreateEditCtrl(hDlgWnd, ID_EDITBOX, "", 10, 10, 100);
            CreateButtonCtrl(hDlgWnd, ID_BUTTON1, "Hello", 10, 50);
            CreateButtonCtrl(hDlgWnd, ID_BUTTON2, "world", 130, 50);

            SetFocus(hEdit);   // Set focus to edit control when opening

            return 1;
        }

        default:
            return 0;  // Give control back to OS so it can process other messages
    }

    return 0;
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
            // ** Parse menu selections
            switch (wParam)
            {
                case ID_FIND: // some menu item with control id: ID_FIND

                    // ** Create and open dialog when menu item is clicked

                    g_hMyDlg = DlgBox(hWnd, "My find dialog", 238, 130, MyDlgProc);  // <-------  add this to create and open your dialog

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
                    ShowWindow(g_hMyDlg, SW_HIDE);  // <-------  add this, if you want the dialog to follow parent when window is minimized
                    break;

                case SIZE_RESTORED:
                    ShowWindow(g_hMyDlg, SW_SHOW);  // <-------  add this, if you want the dialog to follow parent when window is restored.
                    break;                                       //  Be sure to close the dialog with "DestroyWindow()" in addition to "EndDialog()"
            }                                                    //  or else the dialog can popup again on "SIZE_RESTORED" even if you closed it.
            break;                                               //  Since the dialog window remains in memory if only using "EndDialog()".
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
//          (usually at the bottom in "WinMain.cpp" or "main.cpp")
///////////////////////////////////////////////////////////////////////////////////////////////
    
    // ...above this is the window creation code etc. as usual. (WinMain function)

    // ** The message loop  (WinMain function)

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
// DONE!
///////////////////////////////////////////////////////////////////////////////////////////////
*/
