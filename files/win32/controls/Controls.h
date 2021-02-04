#pragma once
//---------------------------------------------------------------------------------------------
// ** Controls.h
//---------------------------------------------------------------------------------------------
#ifndef CONTROLS_H
#define CONTROLS_H
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include <windows.h>


//---------------------------------------------------------------------------------------------
// ** Function prototypes
//---------------------------------------------------------------------------------------------
// ** Controls  (using long long in case of 64-bit build, works in 32-bit as well)

HWND CreateStaticTextCtrl(HWND hParentWnd, const char szText[], int x, int y, int w = 100, int h = 30, long long int ctrlID = -1, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateStaticLineHoriz(HWND hParentWnd, int x, int y, int w = 100, int h = 5, long long int ctrlID = -1, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateStaticLineVert(HWND hParentWnd, int x, int y, int h = 100, int w = 5, long long int ctrlID = -1, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateButtonCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w = 40, int h = 12, DWORD dwStyle = NULL, DWORD dwExStyle = NULL, void *fnCallback = NULL);
HWND CreateEditCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w = 50, int h = 14, DWORD dwStyle = NULL, DWORD dwExStyle = NULL, int iMaxLength = 0);
HWND CreateComboBoxDropDownCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w = 50, int h = 12, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateComboBoxSimpleCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w = 50, int h = 50, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateDropDownListCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w = 50, int h = 12, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateListBoxCtrl(HWND hParentWnd, long long int ctrlID, int x, int y, int w = 50, int h = 50, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateCheckBoxCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w = 50, int h = 12, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateRadioButtonCtrl(HWND hParentWnd, long long int ctrlID, const char szText[], int x, int y, int w = 50, int h = 12, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);
HWND CreateGroupBoxCtrl(HWND hParentWnd, const char szText[], int x, int y, int w = 100, int h = 50, long long int ctrlID = -1, DWORD dwStyle = NULL, DWORD dwExStyle = NULL);

// ** Control helpers
UINT AddStringCombo(const HWND hComboCtrl, const char szText[]);
UINT AddStringListBox(const HWND hListBoxCtrl, const char szText[]);




//---------------------------------------------------------------------------------------------
#endif // CONTROLS_H
//---------------------------------------------------------------------------------------------
