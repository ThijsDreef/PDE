#pragma once
#include <vector>
#include <bitset>
#include <unordered_map>
#include <assert.h>

#define MAX_COMPONENT 128

using Entity = uint64_t;
using ComponentId = Entity;
using ArcheType = std::bitset<MAX_COMPONENT>;

struct ComponentInfo {
    size_t size;
    size_t maskPosition;
};

class ComponentIterator {
    void** components[MAX_COMPONENT];
    size_t sizes[MAX_COMPONENT];
    size_t index;
    size_t count;

    void* getComponentByIndex(size_t maskPosition) {
        return components[maskPosition * index];
    }

    bool next() {
        index++;
        return index < count;
    }
};

class ComponentBuffer {
private:
    size_t m_ComponentSize;
    void* m_Components;
    size_t m_BufferSize;
public:
    ComponentBuffer(ComponentInfo info);
    ~ComponentBuffer();

    void removeComponent(unsigned int index);
    void pushComponent();
    void swapComponent(unsigned int first, unsigned int second);
    
    template<class T>
    T* getComponent(unsigned int index) {
        assertm(index >= m_BufferSize, "component buffer out of bounds");
        return m_Components[index];
    }
};

class ArcheTypeBuffer {
private:
    std::vector<ComponentBuffer> m_Buffers;
    std::vector<Entity> m_Entities;
public:
    ArcheTypeBuffer();
    ~ArcheTypeBuffer();

    void addEntity(Entity e);
    void removeEntity(Entity e);
};