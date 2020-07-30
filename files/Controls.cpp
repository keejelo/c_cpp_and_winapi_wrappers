//---------------------------------------------------------------------------------------------
// ** Controls.cpp
//---------------------------------------------------------------------------------------------

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
		NULL,			// Extended window style
		"static",		// Predefined system class
		szText,			// Window name, or control captiontext
		dwStyle,		// Window style
		x,              // Horizontal position
		y,              // Vertical position
		w,              // Width
		h,              // Height
		hParentWnd,		// Handle to parent window
		(HMENU)-1,		// Handle to a menu
		(HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),	// Handle to the instance of the module
		NULL);			// No pointer
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
		NULL,			// Extended window style
		"static",		// Predefined system class
		szText,			// Window name, or control captiontext
		dwStyle,		// Window style
		x,				// Horizontal position
		y,				// Vertical position
		w,				// Width
		h,				// Height
		hParentWnd,		// Handle to parent window
		(HMENU)-1,		// Handle to a menu
		(HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),	// Handle to the instance of the module
		NULL);			// No pointer
};
//---------------------------------------------------------------------------------------------
// ** END: Create static line horizontal
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

	return CreateWindowEx(
		NULL,			// Extended window style
		"button",		// Predefined system class
		szText,			// Window name, or control captiontext
		dwStyle,		// Window style
		x,				// Horizontal position
		y,				// Vertical position
		w,				// Width
		h,				// Height
		hParentWnd,		// Handle to parent window
		(HMENU)-1,		// Handle to a menu
		(HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),	// Handle to the instance of the module
		NULL);			// No pointer

	// ** ? TODO: push button object into vector array so its ID and callback function is saved for use in "OnButtonClick"  ?

	// ** add an icon to the button
	//HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // ** large icon
	//SendMessage(ID_BTN_OK, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);
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
	
	HWND ctrl = CreateWindowEx(
		dwExStyle,		// Extended window style, this makes border native 3D or if manifested then OS colors and response
		"edit",			// Predefined system class
		szText,			// Window name, or control captiontext
		dwStyle,		// Window style
		x,				// Horizontal position
		y,				// Vertical position
		w,				// Width
		h,				// Height
		hParentWnd,		// Handle to parent window
		(HMENU)-1,		// Handle to a menu
		(HINSTANCE)GetWindowLongPtr(hParentWnd, GWLP_HINSTANCE),	// Handle to the instance of the module
		NULL);			// No pointer

	// ** Set max limit if specified
	if (iMaxLength != NULL)
	{
		SendMessage(ctrl, EM_SETLIMITTEXT, iMaxLength, NULL);
	}

	return ctrl;
};
//---------------------------------------------------------------------------------------------
// ** END: Create edit control
//---------------------------------------------------------------------------------------------

