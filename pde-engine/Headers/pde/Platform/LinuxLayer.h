#pragma once
#define LibraryType void*
#define openLibrary(libname) dlopen((libname), RTLD_LAZY)
#define getLibraryFunction(lib, fn) dlsym((lib), (fn))
#define freeLibrary(lib) dlclose(lib)