#pragma once
#include "./Entity.h"
#include <array>

class ComponentBuffer {
private:
    void* m_components;
    std::array<Entity, MAX_ENTITIES> m_translationTable;
    std::array<unsigned int, MAX_ENTITIES> m_reverseTranslationTable;
public:
    void addComponent(Entity e, void* component);
    void removeComponent(Entity e);
    ComponentBuffer();
    ~ComponentBuffer();
};