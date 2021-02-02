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
extern int SearchList(char *str);


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND CreateDialogBox(HWND hWnd, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight);
void RegisterDialogClass(HINSTANCE hInstance);

void ValidateSearch(HWND hWnd);
void TabFocus(bool bUpDown);
BOOL CALLBACK EnableTabKey(HWND hWnd, LPARAM lParam);
BOOL CALLBACK SetCtrlFont(HWND hWnd, LPARAM lParam);

// ** Control message handlers
LRESULT CALLBACK EditProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OkBtnProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CancelBtnProc(HWND hCtrlWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//---------------------------------------------------------------------------------------------
#endif // SEARCH_DIALOG_H
//---------------------------------------------------------------------------------------------
