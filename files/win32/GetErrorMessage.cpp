//---------------------------------------------------------------------------------------------
// ** GetErrorMessage.cpp
//---------------------------------------------------------------------------------------------
// Translates "GetLastError()" code into readable error message and show it
// Usage:
// GetErrorMessage(GetLastError());
// ..or with a custom title..
// GetErrorMessage(GetLastError(), "My optional error title");
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "GetErrorMessage.h"
#include <stdio.h>


//---------------------------------------------------------------------------------------------
// ** Translate errorcode to descriptive error message and show it
//---------------------------------------------------------------------------------------------
BOOL GetErrorMessage(DWORD dwErrorCode, const char *strTitle, bool bShowMessageBox)
{
    LPTSTR strError = NULL;
    
    DWORD cchMsg = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,  // (not used with FORMAT_MESSAGE_FROM_SYSTEM)
        dwErrorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&strError,
        0,
        NULL);

    // ** Failed to translate ?
    if (cchMsg == 0)
    {
        if (strError)
        {
            LocalFree(strError);
            strError = NULL;
        }
        return FALSE;
    }

    // ** Display errormessage
    if (bShowMessageBox)
    {
        MessageBox(NULL, strError, strTitle, MB_OK | MB_ICONEXCLAMATION);
    }
    else
    {
        printf("%s\n%s\n", strTitle, strError);
    }

    // ** Free buffer
    if(strError)
    {
       LocalFree(strError);
       strError = NULL;
    }

    return TRUE;
};
//---------------------------------------------------------------------------------------------
// ** END: Translate errorcode
//---------------------------------------------------------------------------------------------

