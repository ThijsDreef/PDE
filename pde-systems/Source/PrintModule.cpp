#include <iostream>
#include "Windows.h"
#include "glad/glad.h"

extern "C" {

    void print_init() {

    }

    void print_update() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        Sleep(60);
        // std::cout << "deeedee\n";
    }

    void print_close() {

    }
}
