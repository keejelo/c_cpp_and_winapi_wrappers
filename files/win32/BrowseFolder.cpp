//---------------------------------------------------------------------------------------------
// ** BrowseFolder.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** INCLUDE FILES
//---------------------------------------------------------------------------------------------
#include "BrowseFolder.h"
#include <ShlObj.h>


//---------------------------------------------------------------------------------------------
// ** FUNCTIONS
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Browse for folder and return its path as string
//---------------------------------------------------------------------------------------------
std::string BrowseFolder(HWND hWnd, std::string strInitialDir)
{
    // ** Create a buffer to store the path
    char path[MAX_PATH];

    const char *path_param = strInitialDir.c_str();

    // ** Create BROWSEINFO structure
    BROWSEINFO bi = { 0 };
    bi.hwndOwner = hWnd;
    //bi.lpszTitle = "Some text here";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lParam = (LPARAM)path_param;
    bi.lpfn = BrowseCallbackProc;

    // ** Show the dialog and get the itemIDList for the selected folder
    LPITEMIDLIST pIDL = SHBrowseForFolder(&bi);

    if (pIDL != NULL)
    {
        SHGetPathFromIDList(pIDL, path);

        // ** Free memory used
        IMalloc *imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pIDL);
            imalloc->Release();
        }

        // ** Return the string
        return path;
    }

    return "";
};
//---------------------------------------------------------------------------------------------
// ** END: Browse for folder and return its path as string
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Callback to show initial dir specified in the calling functions parameter
//---------------------------------------------------------------------------------------------
static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    switch (uMsg)
    {
        case BFFM_INITIALIZED:
            // ** Expand the tree view
            SendMessage(hWnd, BFFM_SETEXPANDED, TRUE, lpData);
            // ** Select the item
            SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);
            break;

        case BFFM_SELCHANGED:
            EnumChildWindows(hWnd, EnumCallback, 0);
            break;
    }
    return 0;
};
//---------------------------------------------------------------------------------------------
// ** END: Callback to show initial dir ...
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** EnumCallback - Callback function for EnumWindows (search and expands)
//---------------------------------------------------------------------------------------------
static BOOL CALLBACK EnumCallback(HWND hWndChild, LPARAM lParam)
{
    char szClass[MAX_PATH];
    HTREEITEM hNode;
    if (GetClassName(hWndChild, szClass, sizeof(szClass)) && strcmp(szClass, "SysTreeView32") == 0)
    {
        // ** Found the tree view window
        hNode = TreeView_GetSelection(hWndChild);

        // ** Ensure its selection is visible
        TreeView_EnsureVisible(hWndChild, hNode);

        // ** Done; stop enumerating
        return false;	
    }

    // ** Continue enumerating
    return true;
};
//---------------------------------------------------------------------------------------------
// ** END: EnumCallback - Callback function for EnumWindows 
//---------------------------------------------------------------------------------------------




/*

// ** EXAMPLE

#include <stdio.h>
#include "BrowseFolder.h"

int main()
{
    std::string folder = BrowseFolder(hWnd, "c:\\windows");

    printf("%s\n", folder.c_str());

    return 0;
};

*/
