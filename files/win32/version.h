//---------------------------------------------------------------------------------------------
// ** version.h 
//---------------------------------------------------------------------------------------------
// Add this file and "version.rc" to any project to have versioning, just compile, that's it!
//---------------------------------------------------------------------------------------------
// Inspiration:
// https://www.zachburlingame.com/2011/02/versioning-a-native-cc-binary-with-visual-studio/
//---------------------------------------------------------------------------------------------

#define APP_NAME      "My_app_name"          // .exe will be added automatically
#define APP_DESCRIPT  "My description"
#define APP_COPYRIGHT "Copyright (C) 2021"

//---------------------------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------------------------

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)
 
#define VERSION_MAJOR               1
#define VERSION_MINOR               0
#define VERSION_REVISION            0
#define VERSION_BUILD               0
 
#define VER_FILE_DESCRIPTION_STR    APP_DESCRIPT
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_MAJOR)        \
                                    "." STRINGIZE(VERSION_MINOR)    \
                                    "." STRINGIZE(VERSION_REVISION) \
                                    "." STRINGIZE(VERSION_BUILD)    \
 
#define VER_PRODUCTNAME_STR         APP_NAME
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNAL_NAME_STR       VER_ORIGINAL_FILENAME_STR
#define VER_COPYRIGHT_STR           APP_COPYRIGHT
 
#ifdef _DEBUG
  #define VER_VER_DEBUG             VS_FF_DEBUG
#else
  #define VER_VER_DEBUG             0
#endif
 
#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                VFT_APP
