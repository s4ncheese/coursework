#include "cubes.h"

void cubes::roll_the_dice() {
    _first = 1 + rand() % 6;
    _second = 1 + rand() % 6;
}

std::pair<unsigned, unsigned> cubes::numbers() {
    return std::pair<unsigned, unsigned>
            {_first, _second};
}

unsigned cubes::sum() const {
    return _first + _second;
}