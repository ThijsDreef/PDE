#include "pde/Modules/ModuleLoader.h"
#include "pde/util/hash.h"
#include <iostream>
#include <fstream>
#include <string>

ModuleLoader::ModuleLoader() {
    library = nullptr;
}

ModuleLoader::~ModuleLoader() {
    freeModules();
}

void ModuleLoader::freeModules() {
    for (const auto module : modules) {
        module.second->exit();
        delete module.second;
    }
}

void ModuleLoader::freeModule() {
    freeModules();
    if (!freeLibrary(library)) return;
    library = 0;
}

bool ModuleLoader::load(const char* dllName, const char* manifest) {
    std::ifstream manifestFile(manifest);
    if (!manifestFile.is_open()) return false;
    if (library) return false;
    library = openLibrary(dllName);
    if (!library) return false;
    std::string line;
    while (std::getline(manifestFile, line)) {
        unsigned long moduleHash = hash(line.c_str());
        Module*(*getModule)() = (Module*(*)())(getLibraryFunction(library, ("pde_make_" + line).c_str()));

        if (getModule) {
            modules[moduleHash] = getModule();
            modules[moduleHash]->init();
        }
        else modules[moduleHash] = nullptr;
    }

    return true;
}

Module** ModuleLoader::getModule(unsigned long module) {
    return &modules[module];
}
