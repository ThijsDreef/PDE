#pragma once
#include "pde/Modules/Module.h"
#include "pde/PlatformLayer.h"
#include <unordered_map>

class ModuleLoader {
private:
    LibraryType library;
    std::unordered_map<unsigned long, Module*> modules;
    void freeModules();
public:
    ~ModuleLoader();
    ModuleLoader();
    void freeModule();
    bool load(const char* dllName, const char* manifest);
    Module** getModule(unsigned long module);
};