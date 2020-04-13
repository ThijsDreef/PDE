#pragma once
#ifdef __linux__
    #include "pde/Platform/LinuxLayer.h"
#elif defined(_WIN32)
    #include "pde/Platform/Win32Layer.h"
#endif

