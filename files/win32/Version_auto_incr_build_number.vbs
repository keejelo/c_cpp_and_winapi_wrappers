'-----------------------------------------------------------------------------------------
' Version_auto_incr_build_number.vbs
'-----------------------------------------------------------------------------------------
' Auto increments build version number (x.x.x.build) in the "Version.h" file
' Run this file in the "pre-compile" stage to have auto versioning of buildnumber
'-----------------------------------------------------------------------------------------
' Author: keejelo 2021
' https://github.com/keejelo/c_cpp_and_winapi_wrappers/tree/master/files/win32
' Find and replace source: https://ss64.com/vb/syntax-replace.html
'-----------------------------------------------------------------------------------------

Option Explicit
Dim fso,strFilename,strSearch,strReplace,objFile,oldContent,newContent,BUILD_VERSION

' Initial build version number, this updates each time file is run (writes to this file)
BUILD_VERSION=0

' File and strings to search and replace
strFilename = "Version.h"
strSearch   = "#define VERSION_BUILD               " & BUILD_VERSION
strReplace  = "#define VERSION_BUILD               " & Int(BUILD_VERSION + 1)

' Does file exist?
Set fso = CreateObject("Scripting.FileSystemObject")
If fso.FileExists(strFilename) = False Then
    WScript.Echo "Error, file not found: " & strFilename
    WScript.Quit
End If
 
' Read file
Set objFile = fso.OpenTextFile(strFilename,1)
oldContent=objFile.ReadAll
 
' Write file
newContent = Replace(oldContent,strSearch,strReplace,1,-1,0)
Set objFile = fso.OpenTextFile(strFilename,2)
objFile.Write newContent
objFile.Close 

' Increment BUILD_VERSION number each time this file is run
strFilename = WScript.ScriptFullName
strSearch   = "BUILD_VERSION=" & BUILD_VERSION
strReplace  = "BUILD_VERSION=" & Int(BUILD_VERSION + 1)

' Read file
Set objFile = fso.OpenTextFile(strFilename,1)
oldContent = objFile.ReadAll
 
' Write file
newContent = Replace(oldContent,strSearch,strReplace)
Set objFile = fso.OpenTextFile(strFilename,2)
objFile.Write newContent
objFile.Close 

WScript.Quit
