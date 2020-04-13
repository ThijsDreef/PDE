#pragma once
#include "pde/Memory/Buffer.h"

class ComponentBuffer {
private:
    Buffer components;
    unsigned long long componentSize;
public:
    void addComponent(void* component);
    ComponentBuffer();
    ~ComponentBuffer();
};