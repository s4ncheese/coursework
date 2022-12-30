#ifndef SQUARE_CUBES_H
#define SQUARE_CUBES_H

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>

struct cubes {
    void roll_the_dice();

    std::pair<unsigned, unsigned> numbers();

    [[nodiscard]] unsigned sum() const;
private:
    unsigned _first;
    unsigned _second;
};

#endif //SQUARE_CUBES_H
