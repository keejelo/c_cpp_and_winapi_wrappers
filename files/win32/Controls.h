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
// ** Controls
HWND CreateStaticTextCtrl(HWND hWnd, const char szText[], int x, int y, int w = 100, int h = 30, DWORD dwStyle = NULL);
HWND CreateStaticLineHoriz(HWND hWnd, int x, int y, int w = 100, int h = 5, DWORD dwStyle = NULL);
HWND CreateStaticLineVert(HWND hWnd, int x, int y, int h = 100, int w = 5, DWORD dwStyle = NULL);
HWND CreateButtonCtrl(HWND hWnd, const char szText[], int x, int y, int w = 50, int h = 14, DWORD dwStyle = NULL, void *fnCallback = NULL);
HWND CreateEditCtrl(HWND hWnd, const char szText[], int x, int y, int w = 100, int h = 20, DWORD dwStyle = NULL, int iMaxLength = NULL);
HWND CreateComboBoxDropDownCtrl(HWND hWnd, int x, int y, int w = 50, int h = 12);
HWND CreateComboBoxSimpleCtrl(HWND hWnd, int x, int y, int w = 50, int h = 50);
HWND CreateDropDownListCtrl(HWND hWnd, int x, int y, int w = 50, int h = 12);

// ** Control helpers
UINT AddStringCombo(const HWND hComboCtrl, const char szText[]);




//---------------------------------------------------------------------------------------------
#endif // CONTROLS_H
//---------------------------------------------------------------------------------------------
