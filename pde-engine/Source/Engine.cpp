#include "pde/Engine.h"
#include <iostream> 


Engine::Engine() : m_window("hello world", 520, 380, false), m_graphics(m_window.getParameters()) {
    m_running = false;
    copyFile((char*)SYSTEMS_DLL, (char*)COPY_SYSTEMS_DLL_NAME);
    m_moduleLoader.load(COPY_SYSTEMS_DLL_NAME, MANIFEST_FILE);
}

Engine::~Engine() {

}

void Engine::start() {
    m_running = true;
    run();
}

void Engine::checkHotReload() {
    if (!fileExists("lock.txt") && compareFileTime(&getFileTime(SYSTEMS_DLL), &getFileTime(COPY_SYSTEMS_DLL_NAME)) != 0) {
        std::cout << "start reload\n";
        m_moduleLoader.freeModule();
        if (!copyFile((char*)SYSTEMS_DLL, (char*)COPY_SYSTEMS_DLL_NAME)) return;
        if (m_moduleLoader.load(COPY_SYSTEMS_DLL_NAME, MANIFEST_FILE)) std::cout << "reloaded\n";
    }
}

void Engine::run() {
    while (m_running) {
        checkHotReload();
        Module* t = *m_moduleLoader.getModule(hash("PrintModule"));
        if (t) t->update();
        m_window.update();
        m_graphics.update();
    }
}

void Engine::exit() {
    m_running = false;
}
