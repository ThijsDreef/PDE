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
        if (modules[moduleHash]) delete modules[moduleHash];
        Module*(*getModule)() = (Module*(*)())(getLibraryFunction(library, ("pde_make_" + line).c_str()));
        if (getModule) {
            modules[moduleHash] = getModule();
            std::cout << "made module\n";
        } else  {
            std::cout << "failed module\n";
            modules[moduleHash] = nullptr;
        }
    }

    return true;
}

Module* ModuleLoader::getModule(unsigned long module) {
    return modules[module];
}
