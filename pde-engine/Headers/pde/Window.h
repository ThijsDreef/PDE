#pragma once
#include "pde/PlatformLayer.h"

class Window {
private:
    WindowParameters parameters;

    #ifdef _WIN32
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK realWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    #endif

    void createWindow(char* title, unsigned int w, unsigned int h, bool fullscreen);
    void updateWindow();
    void deleteWindow();
    char* title;
public:
    void update() { updateWindow(); };
    Window(char* title, unsigned int w, unsigned int h, bool fullscreen) { createWindow(title, w, h, fullscreen); }
    ~Window() { deleteWindow(); };
};