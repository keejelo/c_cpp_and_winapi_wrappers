#pragma once
//---------------------------------------------------------------------------------------------
// ** Global_defines.h  - (similar to "Resource.h" in MS Visual Studio IDE)
//---------------------------------------------------------------------------------------------
#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H
//---------------------------------------------------------------------------------------------
// A file to define all your global ID's, similar to what MSVS does for you with "Resource.h".
// So if you're adding alot of resources to your project, you're better off using "Resource.h"
// and a resource file (.rc) so things don't get mixed up.
// http://www.winprog.org/tutorial/resources.html
// https://www.codeproject.com/Articles/1244/Resource-ID-Organiser-Add-In-for-Visual-C-5-0-6-0
//
// If all you need is defines, then here we go:
// As we have to manage and control it all ourselves, it's easier to have it all in one file
// than scattered around in different files, and in worst case some ID's are conflicted and
// resulting in strange and unknown errors. Keeping them together in one file is easier and 
// you have better control.
//
// The names and values are arbitrary, does not matter what you name them (kinda),
// but each name and value must be unique. Valid range for ID values is 1 through 65565.
//
// There are some reserved names and values that it's maybe best to stay away from:
// https://docs.microsoft.com/en-us/cpp/windows/predefined-symbol-ids
// 
//---------------------------------------------------------------------------------------------
// This file must be included everywhere you the ID's are used.
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Defines           
//---------------------------------------------------------------------------------------------
/*
// Examples
#define ID_EDIT1        100
#define ID_BUTTON1      101
#define ID_BUTTON2      102
#define ID_OPEN         103
#define ID_SAVE         104
#define ID_EXIT         105
#define ID_ABOUT        106
*/










//---------------------------------------------------------------------------------------------
#endif // GLOBAL_DEFINES_H
//---------------------------------------------------------------------------------------------
