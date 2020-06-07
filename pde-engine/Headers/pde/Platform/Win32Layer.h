#pragma once
#include "Windows.h"

#define LibraryType HINSTANCE
#define FileTime FILETIME

#define openLibrary(libname) LoadLibraryA(## libname)
#define getLibraryFunction(lib, fn) GetProcAddress(lib, fn)
#define freeLibrary(lib) FreeLibrary(lib)
#define copyFile(name, dest) CopyFileA(name, dest, FALSE)
#define compareFileTime(fileTime, other) CompareFileTime(fileTime, other)

struct WindowParameters {
    HINSTANCE hInstance;
    HWND hWnd;
};

FileTime inline getFileTime(const char* fileName) {
    FILETIME Result = {};
    WIN32_FILE_ATTRIBUTE_DATA Data;

    if (GetFileAttributesExA(fileName, GetFileExInfoStandard, &Data))
        Result = Data.ftLastWriteTime;
    return Result;
}

bool inline fileExists(const char* name) {
    WIN32_FILE_ATTRIBUTE_DATA Ignored;
    return GetFileAttributesExA(name, GetFileExInfoStandard, &Ignored);

}