//---------------------------------------------------------------------------------------------
// ** FindBytePattern.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "FindBytePattern.h"
#include <string>
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
// ** Search for byte pattern inside a bigger byte array (loaded from a file into a buffer)
//---------------------------------------------------------------------------------------------
//    Returns the offset starting position where the pattern is found.
//    If pattern is not found it returns: std::string::npos
//    which is the size of an "unsigned int" or "size_t", in other words "end of file".
//
//    Should works for files up to 4GB  (size of "unsigned int" in Microsoft C++ compilers)
//
//    Tip: to get "patternSize" you can do: int patternSize = sizeof(pattern) / sizeof(pattern[0]);
//         And then supply it to the function before calling it.
//         We cannot do it in the function because we lose its value when passing it ..
//         Same goes for "fileSize" needs to be supplied before calling function ..
//---------------------------------------------------------------------------------------------

// ** Get the size of the array before calling the function
// int patternSize = sizeof(pattern) / sizeof(pattern[0]);

//---------------------------------------------------------------------------------------------
// ** Search for byte pattern inside a bigger byte array (loaded from a file into a buffer)
//---------------------------------------------------------------------------------------------
unsigned int FindBytePattern(unsigned char *pattern, unsigned char *fileBuffer, unsigned int fileSize, unsigned int patternSize)
{	
// ** Create strings
    std::string needle(pattern, pattern + patternSize);
    std::string haystack(fileBuffer, fileBuffer + fileSize);
    
    unsigned int offsetPos = haystack.find(needle);                                                             
    return offsetPos;
};
//---------------------------------------------------------------------------------------------
// ** END: Search for byte pattern
//---------------------------------------------------------------------------------------------
