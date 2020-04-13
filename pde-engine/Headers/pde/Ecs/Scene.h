#pragma once
#include "pde/Modules/Module.h"
#include <vector>
#include <map>

class Scene {
private:
    std::map<unsigned long, unsigned int> currentModules;
    std::vector<Module> modules;
public:
    void exit();
    void init();
    void update();
};