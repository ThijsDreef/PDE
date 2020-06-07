#include "pde/Engine.h"
#include <iostream> 


Engine::Engine() : w("hello world", 520, 380, false), g(w.getParameters()) {
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

void Engine::checkHotReload() {
    if (compareFileTime(&getFileTime(SYSTEMS_DLL), &getFileTime(COPY_SYSTEMS_DLL_NAME)) != 0 && !fileExists("lock.txt")) {
        std::cout << "start reload\n";
        moduleLoader.freeModule();
        if (!copyFile((char*)SYSTEMS_DLL, (char*)COPY_SYSTEMS_DLL_NAME)) return;
        if (moduleLoader.load(COPY_SYSTEMS_DLL_NAME, MANIFEST_FILE)) std::cout << "reloaded\n";
    }
}

void Engine::run() {
    while (running) {
        checkHotReload();
        w.update();
        Module* t = moduleLoader.getModule(hash("PrintModule"));
        if (t) t->update();
        else {
            std::cout << "no t\n";
        }
        g.update();
    }
}

void Engine::exit() {
    running = false;
}