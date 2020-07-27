#include <iostream>
#include "PrintModule.h"
#include "Windows.h"
#include "glad/glad.h"

MAKE_MODULE(PrintModule)

void PrintModule::init() {
    std::cout << "init\n";
    lerp = 0;
    color = randColor();
    targetColor = randColor();
}

Vector3F PrintModule::randColor() {
    Vector3F o;
    o.x = rand()/static_cast<double>(RAND_MAX);
    o.y = rand()/static_cast<double>(RAND_MAX);
    o.z = rand()/static_cast<double>(RAND_MAX);
    return o;
}

void PrintModule::update() {
    lerp += 1/75.0f;
    if (lerp > 1.0f) {
        lerp = 0;
        color = targetColor;
        targetColor = randColor();
    }
    Vector3F c = color + (targetColor - color) * lerp;

    glClearColor(c.x, c.y, c.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Sleep(16);
}

void PrintModule::exit() {
    std::cout << "exit\n";
}