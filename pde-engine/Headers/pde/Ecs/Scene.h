#pragma once
#include "pde/Modules/Module.h"
#include "pde/ECS/EntityManager.h"
#include "pde/Resources.h"
#include <vector>
#include <map>

class Scene {
private:
    Resources resources;
    std::vector<Module*> m_modules;
    EntityManager m_entitiesManager;
public:
    Scene(Resources engineResources);
    ~Scene();
    void addModule(Module* module);
    void exit();
    void init();
    void update();
    EntityManager& getEntityManager();
    bool save(const char* targetFile);
    bool load(const char* targetFile);
};