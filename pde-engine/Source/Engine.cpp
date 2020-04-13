#include "pde/Engine.h"
#include <iostream> 

Engine::Engine() : w("hello world", 520, 380, false) {
    running = false;
    copyFile((char*)SYSTEMS_DLL, (char*)COPY_SYSTEMS_DLL_NAME);
    moduleLoader.load(COPY_SYSTEMS_DLL_NAME, MANIFEST_FILE);
}

Engine::~Engine() {

}

void Engine::start() {
    running = true;
    run();
}

void Engine::run() {
    while (running) {
        w.update();
        WIN32_FILE_ATTRIBUTE_DATA Ignored;
        if (CompareFileTime(&getFileTime(SYSTEMS_DLL), &getFileTime(COPY_SYSTEMS_DLL_NAME)) != 0 && !GetFileAttributesExA("lock.txt", GetFileExInfoStandard, &Ignored)) {
            std::cout << "start reload\n";
            moduleLoader.freeModule();
            if (!copyFile((char*)SYSTEMS_DLL, (char*)COPY_SYSTEMS_DLL_NAME)) continue;
            if (moduleLoader.load(COPY_SYSTEMS_DLL_NAME, MANIFEST_FILE)) std::cout << "reloaded\n";
        } else {
            moduleLoader.getModule(0)->update();    
        }
    }
}

void Engine::exit() {
    running = false;
}