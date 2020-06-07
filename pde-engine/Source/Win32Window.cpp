#include "pde/Window.h"
#include <iostream>

void Window::createWindow(char* title, unsigned int width, unsigned int height, bool fullscreen) {
    this->title = title;
    WNDCLASS wc;
    DWORD dwExStyle;
    DWORD dwStyle;

    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    RECT windowRect;
    windowRect.left = 0;
    windowRect.right = fullscreen ? desktop.right : width;
    windowRect.top = 0;
    windowRect.bottom = fullscreen ? desktop.bottom : height;

    parameters.hInstance = GetModuleHandle(NULL);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.hInstance = parameters.hInstance;

    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    wc.lpfnWndProc = (WNDPROC)Window::WndProc;
    
    wc.lpszClassName = title;

    //register class with windows
    if (!RegisterClass(&wc)) {
      return;
    }

    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;

    if (fullscreen) {
      DEVMODE dmScreenSettings;
      memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
      dmScreenSettings.dmSize = sizeof(dmScreenSettings);
      dmScreenSettings.dmPelsWidth = width;
      dmScreenSettings.dmPelsHeight = height;
      dmScreenSettings.dmBitsPerPel = 32;
      dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
      if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {        
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP | WS_VISIBLE;
      }
    }

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
    if (!(parameters.hWnd = CreateWindowExA(dwExStyle, title, title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, parameters.hInstance, NULL))) {
      
    }
    SetWindowPos(parameters.hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetPropA(parameters.hWnd, "PDEWindow", this);
    ShowWindow(parameters.hWnd, SW_SHOW);
    SetForegroundWindow(parameters.hWnd);
    SetFocus(parameters.hWnd);
    RECT size;
    GetClientRect(parameters.hWnd, &size);
    width = size.right;
    height = size.bottom;
}

void Window::updateWindow() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::deleteWindow() {
    if (parameters.hWnd) DestroyWindow(parameters.hWnd);
    if (parameters.hInstance) UnregisterClass(title, parameters.hInstance);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* pThis = static_cast<Window*>(GetPropA(hWnd, "PDEWindow"));
    if (pThis) return pThis->realWndProc(hWnd, uMsg, wParam, lParam);
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Window::realWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            // TODO: call exit 
            return 0;
        case WM_SIZING:
        case WM_SIZE:
            // TODO: allow for resizing
            return 0;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_KEYDOWN:
        case WM_KEYUP:
            // TODO: post input messages
        default:
            return DefWindowProc(hWnd,  uMsg, wParam, lParam);
    }

}
