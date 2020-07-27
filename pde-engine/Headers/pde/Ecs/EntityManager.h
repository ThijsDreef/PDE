#pragma once
#include "pde/Ecs/Entity.h"
#include "pde/Util/hash.h"
#include <array>
#include <stack>
#include <bitset>
#include <typeindex>
#include <unordered_map>

class EntityManager {
private:
    std::unordered_map<Entity, ArcheType> m_entityMap;
    std::unordered_map<ArcheType, ArcheTypeBuffer> m_archeTypes;
    std::unordered_map<std::type_index, ComponentInfo> m_components;
    size_t m_freeList[MAX_COMPONENT];
    unsigned int currentIndex;
public:
    EntityManager();
    ~EntityManager();
    Entity createEntity();

    template<class T>
    void addComponent(Entity e, T component) {
        std::type_index(T);

        ArcheType lastMask = m_entityMap[e];
        
    }

    template<class T>
    void unRegisterComponent() {
        // decrement currentIndex
        // remove component from all archetypes
    }

    template<class T> 
    void registerComponent() {
        std::type_index type = std::type_index(T);
        
        if (!m_components.contains(type)) {
            m_components[type].maskPosition = m_freeList[currentIndex++];
            m_components[type].size = sizeof(T);
        } else {
            m_components[type].size = sizeof(T);
            // let buffers know they need to resize and copy old over new because of size change
            // or give error message saying expected memory layout changed
        }
    }
};
