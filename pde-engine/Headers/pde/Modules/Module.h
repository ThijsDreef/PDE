#pragma once
struct Module {
    void* data;
    void (*init)();
    void (*update)();
    void (*exit)();
};
