//---------------------------------------------------------------------------------------------
// ** BrowseFile.cpp
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// ** Include files
//---------------------------------------------------------------------------------------------
#include "BrowseFile.h"
#include <algorithm>
#include <cctype>
#include <ShlObj.h>


//---------------------------------------------------------------------------------------------
// ** Browse for file (Open/Save dialog), and return its path as string
//---------------------------------------------------------------------------------------------
std::string BrowseFile(HWND hWndParent, bool bOpenOrSave, std::string strInitialDir)
{
    // ** Create string, default full path
    std::string strFullPath = "";

    // ** Transform the string to lowercase before search, makes search "case-insensitive"
    std::transform( strInitialDir.begin(), strInitialDir.end(), strInitialDir.begin(), [](unsigned char c) { return std::tolower(c); } );

    // ** Search for %userprofile% in string (in case the string contains it)
    std::size_t found = strInitialDir.find("%userprofile%");

    // ** If found then make path with %userprofile% (only if string contains it, else we skip this)
    if (found != std::string::npos)
    {
        //puts("%userprofile% was found!\n");

        // ** Get %UserProfile% path string (expand the environment variable and build final string)
        char szProfilePath[MAX_PATH] = { 0 };
        HRESULT result = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, szProfilePath);

        if (result == S_OK)
        {
            strInitialDir.replace(0, 14, "\\"); // Remove %userprofile% from the string since it was just a search symbol, and replace it with a bracket
            strFullPath = szProfilePath;    // Add the proper userprofile from the CSIDL format list
            strFullPath += strInitialDir;   // Add rest of the string to complete the full path
        }
    }
    else
    {
        //puts("%userprofile% not found!\n");
        strFullPath = strInitialDir;
    }

    // ** Buffer for file name
    char szFile[MAX_PATH] = { 0 };

    // ** Create common dialog box structure
    OPENFILENAME ofn = { 0 };

    // ** Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWndParent;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';  // Set lpstrFile[0] to '\0' so GetOpenFileName/GetSaveFileName does not use the contents of szFile to initialize itself.
    ofn.nMaxFile = MAX_PATH;    
    ofn.lpstrFilter = "All files (*.*)\0*.*\0"; // "Text files (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
    ofn.lpstrDefExt = "";
    ofn.lpstrInitialDir = strFullPath.c_str();
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
    
    // ** Check if we're going to show Open (true) or Save (false) dialog
    if(bOpenOrSave)
    {
        ofn.Flags |= OFN_FILEMUSTEXIST;
        
        // ** Open file dialog
        if (GetOpenFileName(&ofn))
        {
            return ofn.lpstrFile; // return filename
        }
    }
    else
    {
        ofn.Flags |= OFN_OVERWRITEPROMPT;
        
        // ** Save file dialog
        if (GetSaveFileName(&ofn))
        {
            return ofn.lpstrFile; // return filename
        }    
    }

    return ""; // return empty if Cancel or not selected any file
};
//---------------------------------------------------------------------------------------------
// ** END: Browse for file (Open/Save dialog), and return its path as string
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
// ** CSIDL - DOCUMENTATION 
//---------------------------------------------------------------------------------------------
/*

https://docs.microsoft.com/en-us/windows/win32/shell/csidl

CSIDL

05/31/2018
9 minutes to read

Note

As of Windows Vista, these values have been replaced by KNOWNFOLDERID values. See that topic for a list of the new constants and their corresponding CSIDL values. For convenience, corresponding KNOWNFOLDERID values are also noted here for each CSIDL value.

The CSIDL system is supported under Windows Vista for compatibility reasons. However, new development should use KNOWNFOLDERID values rather than CSIDL values.



CSIDL (constant special item ID list) values provide a unique system-independent way to identify special folders used frequently by applications, but which may not have the same name or location on any given system. For example, the system folder may be "C:\Windows" on one system and "C:\Winnt" on another. These constants are defined in Shlobj.h.

TABLE 1
Constant/value	Description
CSIDL_ADMINTOOLS
	FOLDERID_AdminTools
	Version 5.0. The file system directory that is used to store administrative tools for an individual user. The MMC will save customized consoles to this directory, and it will roam with the user.
CSIDL_ALTSTARTUP
	FOLDERID_Startup
	The file system directory that corresponds to the user's nonlocalized Startup program group. This value is recognized in Windows Vista for backward compatibility, but the folder itself no longer exists.
CSIDL_APPDATA
	FOLDERID_RoamingAppData
	Version 4.71. The file system directory that serves as a common repository for application-specific data. A typical path is C:\Documents and Settings\username\Application Data.
CSIDL_BITBUCKET
	FOLDERID_RecycleBinFolder
	The virtual folder that contains the objects in the user's Recycle Bin.
CSIDL_CDBURN_AREA
	FOLDERID_CDBurning
	Version 6.0. The file system directory that acts as a staging area for files waiting to be written to a CD. A typical path is C:\Documents and Settings\username\Local Settings\Application Data\Microsoft\CD Burning.
CSIDL_COMMON_ADMINTOOLS
	FOLDERID_CommonAdminTools
	Version 5.0. The file system directory that contains administrative tools for all users of the computer.
CSIDL_COMMON_ALTSTARTUP
	FOLDERID_CommonStartup
	The file system directory that corresponds to the nonlocalized Startup program group for all users. This value is recognized in Windows Vista for backward compatibility, but the folder itself no longer exists.
CSIDL_COMMON_APPDATA
	FOLDERID_ProgramData
	Version 5.0. The file system directory that contains application data for all users. A typical path is C:\Documents and Settings\All Users\Application Data. This folder is used for application data that is not user specific. For example, an application can store a spell-check dictionary, a database of clip art, or a log file in the CSIDL_COMMON_APPDATA folder. This information will not roam and is available to anyone using the computer.
CSIDL_COMMON_DESKTOPDIRECTORY
	FOLDERID_PublicDesktop
	The file system directory that contains files and folders that appear on the desktop for all users. A typical path is C:\Documents and Settings\All Users\Desktop.
CSIDL_COMMON_DOCUMENTS
	FOLDERID_PublicDocuments
	The file system directory that contains documents that are common to all users. A typical path is C:\Documents and Settings\All Users\Documents.
CSIDL_COMMON_FAVORITES
	FOLDERID_Favorites
	The file system directory that serves as a common repository for favorite items common to all users.
CSIDL_COMMON_MUSIC
	FOLDERID_PublicMusic
	Version 6.0. The file system directory that serves as a repository for music files common to all users. A typical path is C:\Documents and Settings\All Users\Documents\My Music.
CSIDL_COMMON_OEM_LINKS
	FOLDERID_CommonOEMLinks
	This value is recognized in Windows Vista for backward compatibility, but the folder itself is no longer used.
CSIDL_COMMON_PICTURES
	FOLDERID_PublicPictures
	Version 6.0. The file system directory that serves as a repository for image files common to all users. A typical path is C:\Documents and Settings\All Users\Documents\My Pictures.
CSIDL_COMMON_PROGRAMS
	FOLDERID_CommonPrograms
	The file system directory that contains the directories for the common program groups that appear on the Start menu for all users. A typical path is C:\Documents and Settings\All Users\Start Menu\Programs.
CSIDL_COMMON_STARTMENU
	FOLDERID_CommonStartMenu
	The file system directory that contains the programs and folders that appear on the Start menu for all users. A typical path is C:\Documents and Settings\All Users\Start Menu.
CSIDL_COMMON_STARTUP
	FOLDERID_CommonStartup
	The file system directory that contains the programs that appear in the Startup folder for all users. A typical path is C:\Documents and Settings\All Users\Start Menu\Programs\Startup.
CSIDL_COMMON_TEMPLATES
	FOLDERID_CommonTemplates
	The file system directory that contains the templates that are available to all users. A typical path is C:\Documents and Settings\All Users\Templates.
CSIDL_COMMON_VIDEO
	FOLDERID_PublicVideos
	Version 6.0. The file system directory that serves as a repository for video files common to all users. A typical path is C:\Documents and Settings\All Users\Documents\My Videos.
CSIDL_COMPUTERSNEARME
	FOLDERID_NetworkFolder
	The folder that represents other computers in your workgroup.
CSIDL_CONNECTIONS
	FOLDERID_ConnectionsFolder
	The virtual folder that represents Network Connections, that contains network and dial-up connections.
CSIDL_CONTROLS
	FOLDERID_ControlPanelFolder
	The virtual folder that contains icons for the Control Panel applications.
CSIDL_COOKIES
	FOLDERID_Cookies
	The file system directory that serves as a common repository for Internet cookies. A typical path is C:\Documents and Settings\username\Cookies.
CSIDL_DESKTOP
	FOLDERID_Desktop
	The virtual folder that represents the Windows desktop, the root of the namespace.
CSIDL_DESKTOPDIRECTORY
	FOLDERID_Desktop
	The file system directory used to physically store file objects on the desktop (not to be confused with the desktop folder itself). A typical path is C:\Documents and Settings\username\Desktop.
CSIDL_DRIVES
	FOLDERID_ComputerFolder
	The virtual folder that represents My Computer, containing everything on the local computer: storage devices, printers, and Control Panel. The folder can also contain mapped network drives.
CSIDL_FAVORITES
	FOLDERID_Favorites
	The file system directory that serves as a common repository for the user's favorite items. A typical path is C:\Documents and Settings\username\Favorites.
CSIDL_FONTS
	FOLDERID_Fonts
	A virtual folder that contains fonts. A typical path is C:\Windows\Fonts.
CSIDL_HISTORY
	FOLDERID_History
	The file system directory that serves as a common repository for Internet history items.
CSIDL_INTERNET
	FOLDERID_InternetFolder
	A virtual folder for Internet Explorer.
CSIDL_INTERNET_CACHE
	FOLDERID_InternetCache
	Version 4.72. The file system directory that serves as a common repository for temporary Internet files. A typical path is C:\Documents and Settings\username\Local Settings\Temporary Internet Files.
CSIDL_LOCAL_APPDATA
	FOLDERID_LocalAppData
	Version 5.0. The file system directory that serves as a data repository for local (nonroaming) applications. A typical path is C:\Documents and Settings\username\Local Settings\Application Data.
CSIDL_MYDOCUMENTS
	FOLDERID_Documents
	Version 6.0. The virtual folder that represents the My Documents desktop item. This value is equivalent to CSIDL_PERSONAL.
CSIDL_MYMUSIC
	FOLDERID_Music
	The file system directory that serves as a common repository for music files. A typical path is C:\Documents and Settings\User\My Documents\My Music.
CSIDL_MYPICTURES
	FOLDERID_Pictures
	Version 5.0. The file system directory that serves as a common repository for image files. A typical path is C:\Documents and Settings\username\My Documents\My Pictures.
CSIDL_MYVIDEO
	FOLDERID_Videos
	Version 6.0. The file system directory that serves as a common repository for video files. A typical path is C:\Documents and Settings\username\My Documents\My Videos.
CSIDL_NETHOOD
	FOLDERID_NetHood
	A file system directory that contains the link objects that may exist in the My Network Places virtual folder. It is not the same as CSIDL_NETWORK, which represents the network namespace root. A typical path is C:\Documents and Settings\username\NetHood.
CSIDL_NETWORK
	FOLDERID_NetworkFolder
	A virtual folder that represents Network Neighborhood, the root of the network namespace hierarchy.
CSIDL_PERSONAL
	FOLDERID_Documents
	Version 6.0. The virtual folder that represents the My Documents desktop item. This is equivalent to CSIDL_MYDOCUMENTS.
	Previous to Version 6.0. The file system directory used to physically store a user's common repository of documents. A typical path is C:\Documents and Settings\username\My Documents. This should be distinguished from the virtual My Documents folder in the namespace. To access that virtual folder, use SHGetFolderLocation, which returns the ITEMIDLIST for the virtual location, or refer to the technique described in Managing the File System.
CSIDL_PRINTERS
	FOLDERID_PrintersFolder
	The virtual folder that contains installed printers.
CSIDL_PRINTHOOD
	FOLDERID_PrintHood
	The file system directory that contains the link objects that can exist in the Printers virtual folder. A typical path is C:\Documents and Settings\username\PrintHood.
CSIDL_PROFILE
	FOLDERID_Profile
	Version 5.0. The user's profile folder. A typical path is C:\Users\username. Applications should not create files or folders at this level; they should put their data under the locations referred to by CSIDL_APPDATA or CSIDL_LOCAL_APPDATA. However, if you are creating a new Known Folder the profile root referred to by CSIDL_PROFILE is appropriate.
CSIDL_PROGRAM_FILES
	FOLDERID_ProgramFiles
	Version 5.0. The Program Files folder. A typical path is C:\Program Files.
CSIDL_PROGRAM_FILESX86
	FOLDERID_ProgramFilesX86
CSIDL_PROGRAM_FILES_COMMON
	FOLDERID_ProgramFilesCommon
	Version 5.0. A folder for components that are shared across applications. A typical path is C:\Program Files\Common. Valid only for Windows XP.
CSIDL_PROGRAM_FILES_COMMONX86
	FOLDERID_ProgramFilesCommonX86
CSIDL_PROGRAMS
	FOLDERID_Programs
	The file system directory that contains the user's program groups (which are themselves file system directories). A typical path is C:\Documents and Settings\username\Start Menu\Programs.
CSIDL_RECENT
	FOLDERID_Recent
	The file system directory that contains shortcuts to the user's most recently used documents. A typical path is C:\Documents and Settings\username\My Recent Documents. To create a shortcut in this folder, use SHAddToRecentDocs. In addition to creating the shortcut, this function updates the Shell's list of recent documents and adds the shortcut to the My Recent Documents submenu of the Start menu.
CSIDL_RESOURCES
	FOLDERID_ResourceDir
	Windows Vista. The file system directory that contains resource data. A typical path is C:\Windows\Resources.
CSIDL_RESOURCES_LOCALIZED
	FOLDERID_LocalizedResourcesDir
CSIDL_SENDTO
	FOLDERID_SendTo
	The file system directory that contains Send To menu items. A typical path is C:\Documents and Settings\username\SendTo.
CSIDL_STARTMENU
	FOLDERID_StartMenu
	The file system directory that contains Start menu items. A typical path is C:\Documents and Settings\username\Start Menu.
CSIDL_STARTUP
	FOLDERID_Startup
	The file system directory that corresponds to the user's Startup program group. The system starts these programs whenever the associated user logs on. A typical path is C:\Documents and Settings\username\Start Menu\Programs\Startup.
CSIDL_SYSTEM
	FOLDERID_System
	Version 5.0. The Windows System folder. A typical path is C:\Windows\System32.
CSIDL_SYSTEMX86
	FOLDERID_SystemX86
CSIDL_TEMPLATES
	FOLDERID_Templates
	The file system directory that serves as a common repository for document templates. A typical path is C:\Documents and Settings\username\Templates.
CSIDL_WINDOWS
	FOLDERID_Windows
	Version 5.0. The Windows directory or SYSROOT. This corresponds to the %windir% or %SYSTEMROOT% environment variables. A typical path is C:\Windows.

Flags

CSIDL_FLAG_CREATE
	KF_FLAG_CREATE
	Version 5.0. Combine with another CSIDL to force the creation of the associated folder if it does not exist.
CSIDL_FLAG_DONT_UNEXPAND
	KF_FLAG_DONT_UNEXPAND
	Combine with another CSIDL constant to ensure the expansion of environment variables.
CSIDL_FLAG_DONT_VERIFY
	KF_FLAG_DONT_VERIFY
	Combine with another CSIDL constant, except for CSIDL_FLAG_CREATE, to return an unverified folder path with no attempt to create or initialize the folder.
CSIDL_FLAG_NO_ALIAS
	KF_FLAG_NO_ALIAS
	Combine with another CSIDL constant to ensure the retrieval of the true system path for the folder, free of any aliased placeholders such as %USERPROFILE%, returned by SHGetFolderLocation. This flag has no effect on paths returned by SHGetFolderPath.
CSIDL_FLAG_PER_USER_INIT
CSIDL_FLAG_MASK
	A mask for any valid CSIDL flag value.

Remarks
These values supersede the use of environment variables for this purpose. They are in turn superseded in Windows Vista and later by the KNOWNFOLDERID values.

A CSIDL is used in conjunction with one of four Shell functions, SHGetFolderLocation, SHGetFolderPath, SHGetSpecialFolderLocation, and SHGetSpecialFolderPath, to retrieve a special folder's path or pointer to an item identifier list (PIDL).

Combine CSIDL_FLAG_CREATE with any of the other CSIDLs, except for CSIDL_FLAG_DONT_VERIFY, to force the creation of the associated folder. The remaining CSIDLs correspond to either file system folders or virtual folders. Where the CSIDL identifies a file system folder, a commonly used path is given as an example. Other paths may be used. Some CSIDLs can be mapped to an equivalent %VariableName% environment variable. CSIDLs are more reliable, however, and should be used if possible.

Requirements

Header:
Shlobj.h

See also
SHGetFolderLocation

SHGetFolderPath

SHGetSpecialFolderLocation

SHGetSpecialFolderPath

KNOWN_FOLDER_FLAG
*/
//---------------------------------------------------------------------------------------------
// ** END: CSIDL - DOCUMENTATION 
//---------------------------------------------------------------------------------------------
