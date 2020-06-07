#include "pde/Modules/Module.h"

class PrintModule : public Module {
private:
    double r = 0;
    double g = 0;
    double b = 0;
public:
    void init();
    void update();
    void exit();
};