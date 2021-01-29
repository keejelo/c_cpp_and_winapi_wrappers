'-----------------------------------------------------------------------------------------
' Version_auto_incr_build_number.vbs
'-----------------------------------------------------------------------------------------
' Auto increments build version number (x.x.x.build) in the "Version.h" file
' Run this file in the project "pre-build" event to have auto versioning of buildnumber
' Command line: wscript.exe Version_auto_incr_build_number.vbs
'-----------------------------------------------------------------------------------------
' Author: keejelo 2021
' https://github.com/keejelo/c_cpp_and_winapi_wrappers/tree/master/files/win32
' Find and replace source: https://ss64.com/vb/syntax-replace.html
'-----------------------------------------------------------------------------------------

Option Explicit
Dim fso,strFilename,strSearch,strReplace,objFile,oldContent,newContent,BUILD_VERSION

' Initial build version number, this updates each time this file is run (writes to self).
' Must match the number in "Version.h" from the start, to work as we want.
BUILD_VERSION=39

' File and strings to search and replace in file "Version.h"
strFilename = "Version.h"
strSearch   = "#define VERSION_BUILD               " & BUILD_VERSION
strReplace  = "#define VERSION_BUILD               " & (BUILD_VERSION * 1) + 1

' Does file exist? ("Version.h")
Set fso = CreateObject("Scripting.FileSystemObject")
If fso.FileExists(strFilename) = False Then
    WScript.Echo "Error, file not found: " & strFilename
    WScript.Quit
End If
 
' Read file "Version.h", ready for search and replace
Set objFile = fso.OpenTextFile(strFilename,1)
oldContent = objFile.ReadAll
 
' Write the new build version number to file "Version.h"
newContent = Replace(oldContent,strSearch,strReplace,1,1,0)
Set objFile = fso.OpenTextFile(strFilename,2)
objFile.Write newContent
objFile.Close 

' Increment BUILD_VERSION number variable in this file (self)
strFilename = WScript.ScriptFullName
strSearch   = "BUILD_VERSION=" & BUILD_VERSION
strReplace  = "BUILD_VERSION=" & (BUILD_VERSION * 1) + 1

' Read file (self), ready for search and replace
Set objFile = fso.OpenTextFile(strFilename,1)
oldContent = objFile.ReadAll
 
' Write the new build version number to variable in this file (self) to keep track
newContent = Replace(oldContent,strSearch,strReplace,1,1,0)
Set objFile = fso.OpenTextFile(strFilename,2)
objFile.Write newContent
objFile.Close 

WScript.Quit

