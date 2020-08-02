//---------------------------------------------------------------------------------------------
// ** Controls.cpp
//---------------------------------------------------------------------------------------------

// TODO: Add more controls, the goal is to have a simple wrapper for each standard control for
//       easy creation at runtime.

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "Controls.h"


//---------------------------------------------------------------------------------------------
// ** Create static text control
//---------------------------------------------------------------------------------------------
HWND CreateStaticTextCtrl(HWND hParentWnd, const char szText[], int x, int y, int w, int h, DWORD dwStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_CHILD | WS_VISIBLE;

    return CreateWindowEx(
        NULL,           // Extended window style
        "static",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        NULL,           // Handle to a menu
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static text control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create static line horizontal
//---------------------------------------------------------------------------------------------
HWND CreateStaticLineHoriz(HWND hParentWnd, const char szText[], int x, int y, int w, int h, DWORD dwStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ;

    return CreateWindowEx(
        NULL,           // Extended window style
        "static",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        NULL,           // Handle to a menu
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static line horizontal
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create static line vertical
//---------------------------------------------------------------------------------------------
HWND CreateStaticLineVert(HWND hWndParent, const char szText[], int x, int y, int h, int w, DWORD dwStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_CHILD | WS_VISIBLE | SS_ETCHEDVERT;

    return CreateWindowEx(
        NULL,           // Extended window style
        "static",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hWndParent,     // Handle to parent window
        NULL,           // Handle to a menu
        (HINSTANCE)GetWindowLongPtr(hWndParent, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static line vertical
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create pushbutton control
//---------------------------------------------------------------------------------------------
HWND CreateButtonCtrl(HWND hParentWnd, const char szText[], int x, int y, int w, int h, DWORD dwStyle, void *fnCallback)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;

    HWND hWndBtnCtrl = CreateWindowEx(
        NULL,           // Extended window style
        "button",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        NULL,           // Handle to a menu
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer

    // ** ? TODO: push button object into vector array so its ID and callback function is saved for use in "OnButtonClick"  ?

    // ** Add an icon to the button (optional)
    //HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // IDI_APPLICATION used as example (default application icon)
    //SendMessage(hWndBtnCtrl, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);
    
    return hWndBtnCtrl;
};
//---------------------------------------------------------------------------------------------
// ** END: Create pushbutton control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create edit control
//---------------------------------------------------------------------------------------------
HWND CreateEditCtrl(HWND hParentWnd, const char szText[], int x, int y, int w, int h, DWORD dwStyle, int iMaxLength)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 10);

    // ** Add styles
    DWORD dwExStyle = WS_EX_CLIENTEDGE;
    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD;

    HWND hWndEditCtrl = CreateWindowEx(
        dwExStyle,      // Extended window style, this makes border native 3D or if manifested then OS colors and response
        "edit",         // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        NULL,           // Handle to a menu
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer

    // ** Set max limit if specified
    if (iMaxLength != NULL)
    {
        SendMessage(hWndEditCtrl, EM_SETLIMITTEXT, iMaxLength, NULL);
    }

    return hWndEditCtrl;
};
//---------------------------------------------------------------------------------------------
// ** END: Create edit control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create combobox dropdown control
//---------------------------------------------------------------------------------------------
HWND CreateComboBoxDropDownCtrl(HWND hParnetWnd, const char szText[], int x, int y, int w, int h)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);  // 50
    h = MulDiv(HIWORD(units), h, 10); // 12

    // ** Add styles
    DWORD dwExStyle = NULL;
    DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBS_DROPDOWN;    

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "combobox",     // Predefined class in "windows.h"
        szText,         // Text to display in editbox, can be blank ""
        dwStyle,        // Styles
        x,              // X position 
        y,              // Y position 
        w,              // Width
        h,              // Height
        hParnetWnd,     // Parent window
        NULL,           // No menu
        (HINSTANCE)GetWindowLongPtr(hParnetWnd, GWLP_HINSTANCE),
        NULL);          // Pointer not needed
};
//---------------------------------------------------------------------------------------------
// ** END: Create combobox control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create combobox simple control
//---------------------------------------------------------------------------------------------
HWND CreateComboBoxSimpleCtrl(HWND hParnetWnd, const char szText[], int x, int y, int w, int h)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);  // 50
    h = MulDiv(HIWORD(units), h, 10); // 12

    // ** Add styles
    DWORD dwExStyle = NULL;
    DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBS_SIMPLE;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "combobox",     // Predefined class in "windows.h"
        szText,         // Caption, can be blank ""
        dwStyle,        // Styles
        x,              // X position 
        y,              // Y position 
        w,              // Width
        h,              // Height
        hParnetWnd,     // Parent window
        NULL,           // No menu
        (HINSTANCE)GetWindowLongPtr(hParnetWnd, GWLP_HINSTANCE),
        NULL);          // Pointer not needed
};
//---------------------------------------------------------------------------------------------
// ** END: Create combobox simple control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create combobox dropdownlist control
//---------------------------------------------------------------------------------------------
HWND CreateDropDownListCtrl(HWND hParnetWnd, const char szText[], int x, int y, int w, int h)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);   // 50
    h = MulDiv(HIWORD(units), h, 10);  // 12

    // ** Add styles
    DWORD dwExStyle = NULL;
    DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "combobox",     // Predefined class in "windows.h"
        szText,         // Text to display in editbox, can be blank ""
        dwStyle,        // Styles
        x,              // X position 
        y,              // Y position 
        w,              // Width
        h,              // Height
        hParnetWnd,     // Parent window
        NULL,           // No menu
        (HINSTANCE)GetWindowLongPtr(hParnetWnd, GWLP_HINSTANCE),
        NULL);          // Pointer not needed
};
//---------------------------------------------------------------------------------------------
// ** END: Create combobox simple control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Add string to combobox
//---------------------------------------------------------------------------------------------
UINT AddStringCombo(const HWND hCombo, const char szText[])
{
    return static_cast<UINT>(SendMessage(hCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(szText)));
};
//---------------------------------------------------------------------------------------------
// ** END: Add string to combobox
//---------------------------------------------------------------------------------------------



