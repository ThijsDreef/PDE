#pragma once
#include "pde/Modules/Module.h"
#include <vector>
#include <map>

class Scene {
private:
    std::vector<Module*> m_modules;
public:
    ~Scene();
    Scene();
    void addModule(Module* module);
    void exit();
    void init();
    void update();
};