//---------------------------------------------------------------------------------------------
// ** Controls.cpp
//---------------------------------------------------------------------------------------------

// TODO: Add more controls. The goal is to have a simple wrapper for each standard control for 
//       easier creation of controls at runtime.

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "Controls.h"


//---------------------------------------------------------------------------------------------
// ** Create static text control
//---------------------------------------------------------------------------------------------
HWND CreateStaticTextCtrl(HWND hParentWnd, const char szText[], int x, int y, int w, int h, long long int ctrlID, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    //dwExStyle |= WS_EX_TRANSPARENT;
    dwStyle |= WS_CHILD | WS_VISIBLE;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "static",       // Predefined system class
        szText,         // Text to display
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Static controls usually have ID = -1  (This can also be an id (IDC_STATIC_TEXT1))
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static text control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create static line horizontal
//---------------------------------------------------------------------------------------------
HWND CreateStaticLineHoriz(HWND hParentWnd, int x, int y, int w, int h, long long int ctrlID, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "static",       // Predefined system class
        "",             // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Static controls usually have ID = -1   (This can also be an id (IDC_STATIC_LINE1))
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static line horizontal
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create static line vertical
//---------------------------------------------------------------------------------------------
HWND CreateStaticLineVert(HWND hParentWnd, int x, int y, int h, int w, long long int ctrlID, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_CHILD | WS_VISIBLE | SS_ETCHEDVERT;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "static",       // Predefined system class
        "",             // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Static controls usually have ID = -1   (This can also be an id (IDC_STATIC_LINE2))
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static line vertical
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create pushbutton control
//---------------------------------------------------------------------------------------------
HWND CreateButtonCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle, void *fnCallback)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;

    HWND hWndBtnCtrl = CreateWindowEx(
        dwExStyle,      // Extended window style
        "button",       // Predefined system class
        szText,         // Buttontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_BUTTON1)
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
HWND CreateEditCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle, int iMaxLength)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 10);

    dwExStyle |= WS_EX_CLIENTEDGE;
    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD;
    //dwStyle |= ES_WANTRETURN | ES_MULTILINE; // <--- for multiline editboxes

    HWND hWndEditCtrl = CreateWindowEx(
        dwExStyle,      // Extended window style, this makes border native 3D or if manifested then OS colors and response
        "edit",         // Predefined system class
        szText,         // Text to display
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_EDIT1)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer

    // ** Set max limit if specified
    if (iMaxLength > 0)
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
HWND CreateComboBoxDropDownCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);  // 50
    h = MulDiv(HIWORD(units), h, 10); // 12

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWN;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "combobox",     // Predefined system class
        "",             // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_COMBO1)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create combobox dropdown control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create combobox simple control
//---------------------------------------------------------------------------------------------
HWND CreateComboBoxSimpleCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);  // 50
    h = MulDiv(HIWORD(units), h, 10); // 12

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_SIMPLE;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "combobox",     // Predefined system class
        "",             // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_COMBO2)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create combobox simple control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create combobox dropdownlist control
//---------------------------------------------------------------------------------------------
HWND CreateDropDownListCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);   // 50
    h = MulDiv(HIWORD(units), h, 10);  // 12

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "combobox",     // Predefined system class
        "",             // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_DROPDOWN1)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create combobox dropdownlist control
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


//---------------------------------------------------------------------------------------------
// ** Create listbox control
//---------------------------------------------------------------------------------------------
HWND CreateListBoxCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);   // 50
    h = MulDiv(HIWORD(units), h, 10);  // 12

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | LBS_STANDARD;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "listbox",      // Predefined class in "windows.h"
        "",             // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_LISTBOX1)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create listbox control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Add string to listbox
//---------------------------------------------------------------------------------------------
UINT AddStringListBox(const HWND hListBoxCtrl, const char szText[])
{
    return static_cast<UINT>(SendMessage(hListBoxCtrl, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(szText)));
};
//---------------------------------------------------------------------------------------------
// ** END: Add string to listbox
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create checkbox control
//---------------------------------------------------------------------------------------------
HWND CreateCheckBoxCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "button",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_CHECKBOX1)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create checkbox control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create radiobutton control
//---------------------------------------------------------------------------------------------
HWND CreateRadioButtonCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w, int h, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_TABSTOP | WS_VISIBLE | WS_CHILD /*| WS_GROUP */ | BS_AUTORADIOBUTTON;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "button",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  // Handle to a menu. This can also be an id (IDC_RADIOBUTTON1)
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer

        /*
        Group the radio boxes:
        Put the WS_GROUP in the first radio button's style.
        It will group the current radio button until it see the second WS_GROUP
        */
};
//---------------------------------------------------------------------------------------------
// ** END: Create radiobutton control
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Create groupbox control
//---------------------------------------------------------------------------------------------
HWND CreateGroupBoxCtrl(HWND hParentWnd, const char szText[], int x, int y, int w, int h, long long int ctrlID, DWORD dwStyle, DWORD dwExStyle)
{
    LONG units = GetDialogBaseUnits();
    w = MulDiv(LOWORD(units), w, 4);
    h = MulDiv(HIWORD(units), h, 8);

    dwStyle |= WS_VISIBLE | WS_CHILD | BS_GROUPBOX;

    return CreateWindowEx(
        dwExStyle,      // Extended window style
        "button",       // Predefined system class
        szText,         // Window name, or control captiontext
        dwStyle,        // Window style
        x,              // Horizontal position
        y,              // Vertical position
        w,              // Width
        h,              // Height
        hParentWnd,     // Handle to parent window
        (HMENU)ctrlID,  //  Static controls usually have ID = -1   (This can also be an id (IDC_GROUP1))
        (HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),    // Handle to the instance of the module
        NULL);          // No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create groupbox control
//---------------------------------------------------------------------------------------------
