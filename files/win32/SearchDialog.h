#pragma once
//---------------------------------------------------------------------------------------------
// ** SearchWindow.h
//---------------------------------------------------------------------------------------------
#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>


//---------------------------------------------------------------------------------------------
// ** Variables
//---------------------------------------------------------------------------------------------
extern int SearchList(char *str); // <-- function in another file


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
// ** Dialog message handler
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ** Custom message handler for control 
LRESULT CALLBACK EditProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

void RegisterDialogClass(HINSTANCE hInstance);
HWND CreateDialogBox(HWND hWnd, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight);
BOOL CALLBACK SetCtrlFont(HWND hWnd, LPARAM lParam);
void ValidateSearch(HWND hWnd);





//---------------------------------------------------------------------------------------------
#endif // SEARCH_WINDOW_H
//---------------------------------------------------------------------------------------------
