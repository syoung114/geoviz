#include <SDL3/SDL.h>

#include "include/world.hpp"

int main(int argc, char* argv[]) {
    geoviz::World w = geoviz::World<>();
    w.printInfo();
}
