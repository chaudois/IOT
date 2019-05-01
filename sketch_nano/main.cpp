#include <iostream>
#include "Mockup.h"
int main() {
    Mockup *m=new Mockup();
    m->setup();
    m->loop();
    return 0;
}