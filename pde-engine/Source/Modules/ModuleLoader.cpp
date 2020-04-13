#include "pde/Modules/ModuleLoader.h"
#include "pde/util/hash.h"
#include <iostream>
#include <fstream>
#include <string>

ModuleLoader::ModuleLoader() {
    library = 0;

}

ModuleLoader::~ModuleLoader() {

}

void ModuleLoader::freeModule() {
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
        Module*m = &modules[moduleHash];
        if (m->exit) m->exit();
        m->init = (void(*)())(getLibraryFunction(library, (line + "_init").c_str()));
        m->update = (void(*)())(getLibraryFunction(library, (line + "_update").c_str()));
        m->exit = (void(*)())(getLibraryFunction(library, (line + "_exit").c_str()));
        if (m->init) m->init();
    }

    return true;
}

Module* ModuleLoader::getModule(unsigned long module) {
    return &modules[module];
}
