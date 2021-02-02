#pragma once
//---------------------------------------------------------------------------------------------
// ** SearchDialog.h
//---------------------------------------------------------------------------------------------
#ifndef SEARCH_DIALOG_H
#define SEARCH_DIALOG_H
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

// ** Control message handlers
LRESULT CALLBACK EditProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OkBtnProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CancelBtnProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void RegisterDialogClass(HINSTANCE hInstance);
HWND CreateDialogBox(HWND hWnd, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight);

BOOL CALLBACK SetCtrlFont(HWND hWnd, LPARAM lParam);
BOOL CALLBACK EnableTabKey(HWND hWnd, LPARAM lParam);

void TabFocus(bool bUpDown);
void ValidateSearch(HWND hWnd);


//---------------------------------------------------------------------------------------------
#endif // SEARCH_DIALOG_H
//---------------------------------------------------------------------------------------------
