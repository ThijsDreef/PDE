#include <iostream>
#include "PrintModule.h"
#include "Windows.h"
#include "glad/glad.h"

MAKE_MODULE(PrintModule)

void PrintModule::init() {

}

void PrintModule::update() {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Sleep(60);
}

void PrintModule::exit() {

}