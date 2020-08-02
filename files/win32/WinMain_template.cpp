//---------------------------------------------------------------------------------------------
// ** Defines
//---------------------------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>
//#include "resource.h"


//---------------------------------------------------------------------------------------------
// ** Enable visual style on controls (initialize common controls)
//---------------------------------------------------------------------------------------------
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------
char g_szWinTitle[] = "Window title";
int g_iPosX = 0;
int g_iPosY = 0;
int g_iWidth  = 800;
int g_iHeight = 600;


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
    static char szAppName[] = "WindowClassName";        // Define window class name
    HWND hWnd;                                          // Window handle
    MSG msg;                                            // Window message structure
    WNDCLASSEX wc;                                      // Structure to hold window's attributes

    // ** Define window class
    wc.cbSize        = sizeof(WNDCLASSEX);              // Set size of structure
    wc.style         = CS_HREDRAW | CS_VREDRAW;         // Redraw if size changes
    wc.lpfnWndProc   = WndProc;                         // Window function
    wc.cbClsExtra    = 0;                               // No extra bytes after the window class-
    wc.cbWndExtra    = 0;                               // structure or the window instance
    wc.hInstance     = hInstance;                       // Handle to this instance
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // Large icon
    //wc.hIcon       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hIconSm       = NULL;                            // Small icon
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);     // Cursor style
    wc.lpszMenuName  = NULL;                            // Name of menu resource (if any)
    wc.lpszClassName = szAppName;                       // Set window classname

    // ** Window background color set to native OS dialogbox backgroundcolor
    wc.hbrBackground = (HBRUSH)GetSysColorBrush(COLOR_3DFACE);

    // ** Register the window class
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    DWORD dwStyle = WS_SYSMENU | WS_MINIMIZEBOX;
    
    // ** Create the window
    hWnd = CreateWindow(
        szAppName,      // Window classname
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

    ShowWindow(hWnd, nCmdShow); // Display the window
    UpdateWindow(hWnd);         // Cause window client area to be drawn

    // ** The message loop
    while(GetMessage(&msg, NULL, 0, 0) > 0) // Get any messages (prevents returning: -1)
    {
        if(!IsDialogMessage(hWnd, &msg))    // Enable tabstop for controls (if not a dialog)
        {
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
            //OnCreate(hWnd);
            CenterWindow(hWnd);
            EnumChildWindows(hWnd, EnumChildProc, 0);
            break;

        case WM_PAINT:
        {
            HDC hDC;
            PAINTSTRUCT ps;
            hDC = BeginPaint(hWnd, &ps);
            //OnPaint(hWnd);
            EndPaint(hWnd, &ps);
            break; 
        }

        case WM_COMMAND:
            switch (HIWORD(wParam))
            {
                case BN_CLICKED:
                    //OnButtonClick(hWnd, (HWND)lParam);
                    break;
            }
            break;
        
        case WM_CLOSE:
            //OnQuit();
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
// ** Enumerates the child windows that belong to the specified parent window
//---------------------------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
    // ** Set default GUI font to all controls
    HFONT hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hWnd, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(TRUE, 0));
    // ** END: Set default GUI font to all controls
    
    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Enumerates the child windows that belong to the specified parent window
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Center window on screen
//---------------------------------------------------------------------------------------------
void CenterWindow(HWND hWnd)
{
    RECT rc;
    GetWindowRect(hWnd, &rc);
    int x = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
    SetWindowPos(hWnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
};
//---------------------------------------------------------------------------------------------
// ** END: Center window on screen
//---------------------------------------------------------------------------------------------

