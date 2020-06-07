#pragma once

#define MAKE_MODULE(name) extern "C" { Module* pde_make_##name() { return new name(); }}
class Module {
public:
    virtual void update() {};
    virtual void init() {};
    virtual void exit() {};
};
