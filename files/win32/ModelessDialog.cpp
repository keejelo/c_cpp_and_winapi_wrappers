//---------------------------------------------------------------------------------------------
// ** ModelessDialog.cpp
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "ModelessDialog.h"
//#include "Controls.h"  // <---- This makes creating controls easier



//---------------------------------------------------------------------------------------------
// ** Dialogbox window procedure
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            /*
            CreateEditCtrl(hWnd, "", 10, 10, IDC_EDIT1);
            CreateButtonCtrl(hWnd, "OK", 10, 50, IDC_BUTTON1);
            CreateButtonCtrl(hWnd, "Cancel", 150, 50, IDC_BUTTON2);
            */
            EnumChildWindows(hWnd, EnumDialogChildProc, 0);	// Set control visuals
            break;

        case WM_COMMAND:

            break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
    }

    return (DefWindowProc(hWnd, msg, wParam, lParam));
};
//---------------------------------------------------------------------------------------------
// ** END: Dialogbox window procedure
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
    // ** Get parents dimensions, position dialog in parent center
    RECT rc = { 0 };
    GetWindowRect(hWndParent, &rc);
    int xPos = ((rc.left + rc.right) / 2) - (iWidth / 2);
    int yPos = ((rc.top + rc.bottom) / 2) - (iHeight / 2);

    // ** Create and show the dialog
    HWND hDlg = CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, "DialogClass", sTitle,
                    WS_VISIBLE | WS_SYSMENU | WS_CAPTION,
                    xPos, yPos, iWidth, iHeight, 
                    NULL, NULL, hInstance,  NULL);
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



///////////////////////////////////////////////////////////////////////////////////////////////
// ** HOW TO IMPLEMENT
///////////////////////////////////////////////////////////////////////////////////////////////
/*
// ** Do this in your main window procedure 

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            RegisterDialogClass(g_hInstance);  // <-------  add this, "g_hInstance" is GLOBAL handle to instance
            break;
        }
        
        case WM_COMMAND:
        {
            // ** Parse menu selections
            switch(LOWORD(wParam))
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
                    ShowWindow(hMyDlg, SW_HIDE);  // <-------  add this, "hMyDlg" is GLOBAL handle to dialog
                    break;
                
                case SIZE_RESTORED:
                    ShowWindow(hMyDlg, SW_SHOW);  // <-------  add this, "hMyDlg" is GLOBAL handle to dialog
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


