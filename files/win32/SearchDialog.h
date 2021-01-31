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
extern int SearchList(char *str);  // <-- this is a function in another file, just passing it


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EditProc(HWND hEditWnd, UINT msg, WPARAM wParam, LPARAM lParam);  // <-- EditCtrl msg handler
HWND CreateDialogBox(HWND hWnd, HINSTANCE hInstance, const char *sTitle, int iWidth, int iHeight);
void RegisterDialogClass(HINSTANCE hInstance);
BOOL CALLBACK EnumDialogChildProc(HWND hWnd, LPARAM lParam);
void Search(HWND hWnd);  // <-- function that executes the extern function "SearchList"


//---------------------------------------------------------------------------------------------
#endif // SEARCH_DIALOG_H
//---------------------------------------------------------------------------------------------
