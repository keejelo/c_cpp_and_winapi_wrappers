//---------------------------------------------------------------------------------------------
// ** Menu.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "Menu.h"


//---------------------------------------------------------------------------------------------
// ** Create menu
//---------------------------------------------------------------------------------------------
void CreateWindowMenu(HWND hWnd)
{
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();
    HMENU hSubMenu2 = CreatePopupMenu();

    MENUITEMINFO miInfo;
    miInfo.cbSize = sizeof(MENUITEMINFO);

    //-------------------------------------------------
    // ** Add menu and menuitems
    //-------------------------------------------------

    // ** Create the first menubaritem that contains a submenu with items
    miInfo.fMask = MIIM_SUBMENU | MIIM_STRING | MIIM_ID;
    miInfo.wID = 0;
    miInfo.hSubMenu = hSubMenu;
    miInfo.hbmpChecked = NULL;
    miInfo.hbmpUnchecked = NULL;
    miInfo.dwItemData = 0;
    miInfo.dwTypeData = (LPSTR)"&File";
    InsertMenuItem(hMenu, 0, 0, &miInfo);

    // ** Insert subitem in submenu
    miInfo.wID = ID_OPEN;
    miInfo.fMask = MIIM_STRING | MIIM_ID;
    miInfo.dwTypeData = (LPSTR)"&Open..\tCtrl+O";
    InsertMenuItem(hSubMenu, 1, 0, &miInfo);

    // ** Add separator
    miInfo.fMask = MIIM_FTYPE;
    miInfo.fType = MFT_SEPARATOR;
    miInfo.fState = 0;
    miInfo.wID = 0;
    miInfo.hSubMenu = NULL;
    miInfo.hbmpChecked = NULL;
    miInfo.hbmpUnchecked = NULL;
    miInfo.dwItemData = 0;
    InsertMenuItem(hSubMenu, 2, 0, &miInfo);

    // ** Insert subitem in submenu
    miInfo.fMask = MIIM_STRING | MIIM_ID;
    miInfo.dwTypeData = (LPSTR)"E&xit\tAlt+F4";
    miInfo.wID = ID_EXIT;
    InsertMenuItem(hSubMenu, 3, 0, &miInfo);


    // ** Create the second menubaritem that contains a submenu with items
    miInfo.fMask = MIIM_SUBMENU | MIIM_STRING | MIIM_ID;
    miInfo.wID = 0;
    miInfo.hSubMenu = hSubMenu2;
    miInfo.hbmpChecked = NULL;
    miInfo.hbmpUnchecked = NULL;
    miInfo.dwItemData = 0;
    miInfo.dwTypeData = (LPSTR)"&Help";
    InsertMenuItem(hMenu, 1, 0, &miInfo);

    // ** Insert subitem in submenu
    miInfo.wID = ID_ABOUT;
    miInfo.fMask = MIIM_STRING | MIIM_ID;
    miInfo.dwTypeData = (LPSTR)"&About";
    InsertMenuItem(hSubMenu2, 1, 0, &miInfo);


    //-------------------------------------------------
    // ** END: Edit your menu items
    //-------------------------------------------------

    // ** Adde menu to window
    SetMenu(hWnd, hMenu);
};
//---------------------------------------------------------------------------------------------
// ** END: Create menu
//---------------------------------------------------------------------------------------------




/*
// Example of how to implement in main window procedure


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            CreateMenuBar(hWnd); // <----- add this
            break;

        case WM_COMMAND:         // <----- add this if not existant
            {
                // ** Parse the menu selections   // <----- add this and below ID cases
                switch (LOWORD(wParam))
                {
                    case ID_OPEN:
                        // open something
                        break;

                    case ID_ABOUT:
                        // open about dialog
                        break;
                        
                    case ID_EXIT:
                        DestroyWindow(hWnd);
                        break;
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
};

*/


