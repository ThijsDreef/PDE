#pragma once
#include "pde/Modules/ModuleLoader.h"
#include "pde/Window.h"
#include "pde/Graphics/Graphics.h"

#include "pde/Util/hash.h"
#include <vector>

#define SYSTEMS_DLL "pde-systems.dll"
#define COPY_SYSTEMS_DLL_NAME "pde-systems-copy.dll"
#define MANIFEST_FILE "systems.mf"

class Engine {
private:
    ModuleLoader m_moduleLoader;
    Window m_window;
    Graphics m_graphics;
    bool m_running;
    void checkHotReload();
public:
    void start();
    void run();
    void exit();
    Engine();
    ~Engine();
};