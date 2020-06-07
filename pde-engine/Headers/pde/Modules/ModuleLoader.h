#pragma once
#include "pde/Modules/Module.h"
#include "pde/PlatformLayer.h"
#include <map>
class ModuleLoader {
private:
    LibraryType library;
    std::map<unsigned long, Module*> modules;
public:
    ~ModuleLoader();
    ModuleLoader();
    void freeModule();
    bool load(const char* dllName, const char* manifest);
    Module* getModule(unsigned long module);
};