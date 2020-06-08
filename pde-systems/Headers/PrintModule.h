#include "pde/Modules/Module.h"
#include "pde/Math/Vector3F.h"

class PrintModule : public Module {
private:
    Vector3F color;
    Vector3F targetColor;
    float lerp;
    Vector3F randColor();
public:
    void init();
    void update();
    void exit();
};