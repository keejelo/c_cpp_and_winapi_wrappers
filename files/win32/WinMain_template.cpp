//---------------------------------------------------------------------------------------------
// ** WinMain.cpp  (template)
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Defines
//---------------------------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>
//#include "resource.h"
//#include "MyProgram.h"


//---------------------------------------------------------------------------------------------
// ** Enables visual-styles on controls
//---------------------------------------------------------------------------------------------
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------
char g_szWinTitle[] = "Window title here";
int g_iPosX = 0;
int g_iPosY = 0;
int g_iWidth  = 800;
int g_iHeight = 600;

// ** Window background-color (choose one)
HBRUSH g_bgColor = (HBRUSH)GetSysColorBrush(COLOR_3DFACE);  // dialog bgcolor
//HBRUSH g_bgColor = (HBRUSH)GetStockObject(BLACK_BRUSH);  // black bgcolor
//HBRUSH g_bgColor = (HBRUSH)GetStockObject(WHITE_BRUSH);  // white bgcolor
//HBRUSH g_bgColor = CreateSolidBrush(RGB(255, 255, 255)); // custom bgcolor

// ** Text-color for static controls (custom)
//const COLORREF g_textColor = RGB(0, 0, 0);  // default is black (0,0,0)

HINSTANCE g_hInstance;     // Global handle to instance
HWND g_hActiveDlg = NULL;  // Global handle to active dialog window



//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam);
void CenterWindow(HWND hWnd);



//---------------------------------------------------------------------------------------------
// ** WinMain function, application entry point
//---------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{    
    static char szAppName[] = "WindowName";                    // Window name (window 'class' (not c++ class))
    HWND hWnd;                                                 // Window handle
    MSG msg;                                                   // Window message structure
    WNDCLASSEX wc;                                             // Structure to hold window's attributes

    // ** Define window class
    wc.cbSize        = sizeof(WNDCLASSEX);                     // Set size of structure
    wc.style         = CS_HREDRAW | CS_VREDRAW;                // Redraw if size changes
    wc.lpfnWndProc   = WndProc;                                // Window function
    wc.cbClsExtra    = 0;                                      // No extra bytes after the window class-
    wc.cbWndExtra    = 0;                                      // structure or the window instance
    wc.hInstance     = hInstance;                              // Handle to this instance
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);        // Large icon
    //wc.hIcon       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));  // Declared in "resource.h"
    wc.hIconSm       = NULL;                                   // Small icon
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);            // Cursor style
    wc.lpszMenuName  = NULL;                                   // Name of menu resource (if any)
    wc.lpszClassName = szAppName;                              // Set window 'class'

    // ** Window background color
    wc.hbrBackground = g_bgColor;

    // ** Register the window 'class'
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    DWORD dwStyle = WS_OVERLAPPEDWINDOW; // = WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    
    // ** Create the window
    hWnd = CreateWindow(
        szAppName,      // Window name (window 'class' (not c++ class))
        g_szWinTitle,   // Title of the window
        dwStyle,        // Windowstyle
        g_iPosX,        // X pos
        g_iPosY,        // Y pos
        g_iWidth,       // Width
        g_iHeight,      // Height
        NULL,           // No parent window
        NULL,           // No menu 
        hInstance,      // Handle to instance
        NULL);          // No additional arguments

    if(hWnd == NULL)
    {
        MessageBox(NULL, "Window creation failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);  // Display the window
    UpdateWindow(hWnd);          // Cause window client area to be drawn

    g_hInstance = hInstance;     // Set global instance handle
    
    // ** The message loop
    while(GetMessage(&msg, NULL, 0, 0) > 0)  // Get any messages (prevents returning: -1)
    {
        if (!g_hActiveWindow || !IsDialogMessage(g_hActiveWindow, &msg))  // Enables tabstop and keypresses for controls in dialogs,
        {                                                                 // or any window with handle = g_hActiveWindow
            TranslateMessage(&msg);  // Translate keyboard messages
            DispatchMessage(&msg);   // Return control to Windows (OS)
        }
    }
    return (int)msg.wParam;
};
//---------------------------------------------------------------------------------------------
// ** END: WinMain function
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Window procedure, message handler
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
            //OnCreate(hWnd);  // Declared in "MyProgram.h"
            CenterWindow(hWnd);
            EnumChildWindows(hWnd, EnumChildProc, 0);
            break;

        case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            //OnPaint(hWnd);  // Declared in "MyProgram.h"
            EndPaint(hWnd, &ps);
            break; 
        }
         
        // ** Set background-color of static controls to match window, and optionally the text-color.
        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            //SetTextColor(hdcStatic, g_textColor);
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)g_bgColor;
        }
            
        case WM_COMMAND:
            switch (HIWORD(wParam))
            {
                case BN_CLICKED:
                    //OnMouseButtonClick(hWnd, (HWND)lParam);  // Declared in "MyProgram.h"
                    break;
            }
            break;
        
        case WM_CLOSE:
            //OnQuit();  // Declared in "MyProgram.h"
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);  // Close the program
            break;

        default:
            // ** Give control back to OS so it can process other messages
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;    
};
//---------------------------------------------------------------------------------------------
// ** END: Window procedure, message handler
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Set default GUI font on all controls
//---------------------------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
    HFONT hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(TRUE, 0));    
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Set default GUI font on all controls
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Center window on screen
//---------------------------------------------------------------------------------------------
void CenterWindow(HWND hWnd)
{
    RECT rc = {0};
    GetWindowRect(hWnd, &rc);
    int x = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
    SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
};
//---------------------------------------------------------------------------------------------
// ** END: Center window on screen
//---------------------------------------------------------------------------------------------

