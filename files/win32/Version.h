//---------------------------------------------------------------------------------------------
// ** Version.h
//---------------------------------------------------------------------------------------------
// Add this file and "Version.rc" to any project to have versioning, just compile, that's it!
// Custom the strings and values below to fit your project.
//---------------------------------------------------------------------------------------------
// Source and inspiration:
// https://www.zachburlingame.com/2011/02/versioning-a-native-cc-binary-with-visual-studio/
//---------------------------------------------------------------------------------------------
#include <winver.h>
//---------------------------------------------------------------------------------------------

#define APP_PROD_NAME               "My application name"
#define APP_DESCRIPTN               "My description"
#define APP_COPYRIGHT               "Copyright (C) 2021"
#define APP_DEVELOPER               "My company name"
#define APP_COMMENTS                "My comments"

//---------------------------------------------------------------------------------------------

#define VERSION_MAJOR               1        // major version
#define VERSION_MINOR               0        // minor version
#define VERSION_REVISION            0        // revision
#define VERSION_BUILD               0        // build

//---------------------------------------------------------------------------------------------
// DO NOT EDIT BELOW HERE!
//---------------------------------------------------------------------------------------------

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#define VER_FILE_DESCRIPTION_STR    APP_DESCRIPTN
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_MAJOR)        \
                                    "." STRINGIZE(VERSION_MINOR)    \
                                    "." STRINGIZE(VERSION_REVISION) \
                                    "." STRINGIZE(VERSION_BUILD)    \

#define VER_PRODUCTNAME_STR         APP_PROD_NAME
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNAL_NAME_STR       VER_ORIGINAL_FILENAME_STR
#define VER_COPYRIGHT_STR           APP_COPYRIGHT
#define VER_COMPANY_NAME_STR        APP_DEVELOPER
#define VER_COMMENTS_STR            APP_COMMENTS

#ifdef _DEBUG
#define VER_VER_DEBUG               VS_FF_DEBUG
#else
#define VER_VER_DEBUG               0
#endif

#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                VFT_APP
