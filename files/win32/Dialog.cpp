//---------------------------------------------------------------------------------------------
// ** Dialog.cpp
//---------------------------------------------------------------------------------------------
// This creates a dialog template to be used as an empty skeleton dialog.
// The dialog content are created in their own custom dialog procedure in "WM_INITDIALOG".
// Each dialog needs to have its own dialog procedure and handle all its action there.
// See bottom of this file on how to implement and use.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "Dialog.h"
#include <CommCtrl.h>

//---------------------------------------------------------------------------------------------
// ** Dialog template
//---------------------------------------------------------------------------------------------
#define DLGTITLE    "DIALOG TEMPLATE"
#define DLGFONT     "MS Shell Dlg"
#define NUMCHARS(a) (sizeof(a)/sizeof((a)[0]))

#pragma pack(push, 4)
struct DialogTemplate
{
    DWORD style;
    DWORD dwExtendedStyle;
    WORD  ccontrols;
    short x;
    short y;
    short cx;
    short cy;
    WORD  menu;                         // menu resource name
    WORD  windowClass;                  // window 'class' name
    CHAR  szTitle[NUMCHARS(DLGTITLE)];  // window title of dialog
    short pointsize;                    // only if DS_SETFONT flag is set
    CHAR  szFont[NUMCHARS(DLGFONT)];    // typeface name, if DS_SETFONT is set
} dlgTpl =
{
    WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
    | DS_MODALFRAME | DS_SHELLFONT | DS_SETFONT | DS_SETFOREGROUND /*| DS_CENTER*/,
    0x0,                     // exStyle
    0,                       // number of ccontrols in dialog
    0, 0, 0, 0,              // x, y, w, h (pos and size of dialog)
    0,                       // no menu
    0,                       // no window class
    DLGTITLE,                // caption (we override this later)
    8,                       // font size (have no effect on future created controls)
    DLGFONT                  // font name (have no effect on future created controls)
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog template
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create Dialogbox - this creates a dialogbox from the template
//---------------------------------------------------------------------------------------------
// This is the function you use to create your dialogs. 
// "DlgBox" is an optional shorthand for "CreateDialogBox"
//---------------------------------------------------------------------------------------------
HWND CreateDialogBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, int xPos, int yPos, bool bCenterWindow)
{
    // ** Create a dialog with the template above
    HWND hDlg = CreateDialogIndirectParam((HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE), (LPCDLGTEMPLATE)&dlgTpl, hWndParent, DlgProc, 0);

    if (hDlg == NULL)
    {
        MessageBox(NULL, "Dialog creation failed!\n\nError: NULL", "Error", MB_ICONEXCLAMATION);
        return 0;
    }

    // ** Get parent window dimensions, position dialog in parent center
    if (bCenterWindow)
    {
        RECT rc = { 0 };
        GetWindowRect(hWndParent, &rc);
        xPos = ((rc.left + rc.right) / 2) - (iWidth / 2);
        yPos = ((rc.top + rc.bottom) / 2) - (iHeight / 2);
    }

    SetWindowPos(hDlg, 0, xPos, yPos, iWidth, iHeight, 0);
    SetWindowText(hDlg, sTitle);

    return hDlg;
};
//---------------------------------------------------------------------------------------------
// ** END: Create Dialogbox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create Modal Dialogbox - this creates a dialogbox from the template
//---------------------------------------------------------------------------------------------
// This is the function you use to create your dialogs. 
// "DlgBoxModal" is an optional shorthand for "CreateDialogBoxModal"
//---------------------------------------------------------------------------------------------
INT_PTR CreateDialogBoxModal(HWND hWndParent, DLGPROC DlgProc)
{
    // ** Create a dialog with the template above
    INT_PTR nDlg = DialogBoxIndirectParam((HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE), (LPCDLGTEMPLATE)&dlgTpl, hWndParent, DlgProc, 0);
    
    if (nDlg == -1)
    {
        MessageBox(NULL, "Dialog creation failed!\n\nError: -1", "Error", MB_ICONEXCLAMATION);
        return 0;
    }
    return nDlg;


    /*//-------------------------------------------------------------------
    // IMPORTANT NOTICE ABOUT MODAL DIALOG CREATION:
    //---------------------------------------------------------------------
    // Since modal dialogs do not return a window handle, the dialogs size,
    // position, title caption etc. must be handled in its own dialog proc. 
    // "WM_INITDIALOG" like below:
    //-------------------------------------------------------------------

        case WM_INITDIALOG:
        {
            // ** Dialogs title
            SetWindowText(hDlgWnd, "My dialog");

            // ** Dialog size
            int w = 238;
            int h = 130;

            // ** Position dialog in center of parent window
            RECT rc = { 0 };
            GetWindowRect(GetParent(hDlgWnd), &rc);
            int x = ((rc.left + rc.right) / 2) - (w / 2);
            int y = ((rc.top + rc.bottom) / 2) - (h / 2);

            // ** Set dialog position and size
            SetWindowPos(hDlgWnd, 0, x, y, w, h, 0);

            // ..other code if any

            return 1;
        }

    *///--------------------------------------------------------------------

};
//---------------------------------------------------------------------------------------------
// ** END: Create Modal Dialogbox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** DlgBox (shorthand for CreateDialogBox)
//---------------------------------------------------------------------------------------------
HWND DlgBox(HWND hWndParent, const char *sTitle, int iWidth, int iHeight, DLGPROC DlgProc, int xPos, int yPos, bool bCenterWindow)
{
    return CreateDialogBox(hWndParent, sTitle, iWidth, iHeight, DlgProc, xPos, yPos, bCenterWindow);
};
//---------------------------------------------------------------------------------------------
// ** END: DlgBox (shorthand for CreateDialogBox)
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** DlgBoxModal (shorthand for CreateDialogBoxModal)
//---------------------------------------------------------------------------------------------
INT_PTR DlgBoxModal(HWND hWndParent, DLGPROC DlgProc)
{
    return CreateDialogBoxModal(hWndParent, DlgProc);
};
//---------------------------------------------------------------------------------------------
// ** END: DlgBoxMod (shorthand for CreateDialogBoxModal)
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
// ** Dialog procedure (modeless, non modal)
//---------------------------------------------------------------------------------------------
BOOL CALLBACK MyDlgProc(HWND hDlgWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
                    EndDialog(hDlgWnd, 1);
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
            EndDialog(hDlgWnd, 1);
            DestroyWindow(hDlgWnd);
            return 1;

        case WM_INITDIALOG:
        {
            // ** Create some controls when dialog starts
            HWND hEdit = CreateEditCtrl(hDlgWnd, ID_EDITBOX, "", 10, 10, 100);
            CreateButtonCtrl(hDlgWnd, ID_BUTTON1, "Hello", 10, 50);
            CreateButtonCtrl(hDlgWnd, ID_BUTTON2, "world", 130, 50);

            SetFocus(hEdit);            // Set focus to edit control when opening

            return 1;
        }

        default:
            return 0;  // Give control back to OS so it can process other messages
    }

    return 0;
};
//---------------------------------------------------------------------------------------------
// ** END: Dialog procedure (modeless, non modal)
//---------------------------------------------------------------------------------------------



///////////////////////////////////////////////////////////////////////////////////////////////
// STEP 2: DO THIS IN YOUR MAIN WINDOW PROCEDURE (usually in "WinMain.cpp" or "main.cpp")
///////////////////////////////////////////////////////////////////////////////////////////////


HWND g_hMyDlg;      // <--- Global handle to your dialog window, somewhere in a global place


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
                    ShowWindow(g_hMyDlg, SW_SHOW);  // <-------  add this, if you want the dialog to follow parent when window is restored
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