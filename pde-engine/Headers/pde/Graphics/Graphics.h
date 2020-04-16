#include "pde/Window.h"

class Graphics {
private:
    HDC hDc;
    HGLRC context;
    WindowParameters windowParameters;

    void freeContext();
    void initContext(WindowParameters paramters);
public:
    Graphics(WindowParameters parameters);
    ~Graphics();
    void update();
};