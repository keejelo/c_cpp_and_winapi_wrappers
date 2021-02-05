//---------------------------------------------------------------------------------------------
// ** GetErrorMessage.cpp
//---------------------------------------------------------------------------------------------
// Translates "GetLastError()" codes into readable error messages
// Usage:
// GetErrorMessage(GetLastError());
// ..or with a title..
// GetErrorMessage(GetLastError(), "Error");
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "GetErrorMessage.h"


//---------------------------------------------------------------------------------------------
// ** Translate errorcode to error message
//---------------------------------------------------------------------------------------------
BOOL GetErrorMessage(DWORD err, LPTSTR strTitle)
{
    // DWORD err = GetLastError();

    // ** Translate errorcode
    LPTSTR strError = 0;
    if(::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL,
                        err,
                        0,
                        (LPTSTR)&strError,
                        0,
                        NULL) == 0)
    {
       return 0; // Failed in translating
    }

    // ** Display message
    MessageBox(NULL, strError, strTitle, MB_OK | MB_ICONEXCLAMATION);

    // ** Free the buffer
    if( strError )
    {
       ::LocalFree( strError );
       strError = 0;
    }

    return 1;
};
//---------------------------------------------------------------------------------------------
// ** END: Translate errorcode to error message
//---------------------------------------------------------------------------------------------

