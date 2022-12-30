#ifndef SQUARE_PLAYER_H
#define SQUARE_PLAYER_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "../color/color.h"

struct player{
private:
    std::string _name;
    char _symbol;
    unsigned _color;
    unsigned _square = 0;

public:
    player(std::string &name, unsigned color, char symbol) :
    _name(std::move(name)), _color(color), _symbol(symbol) {};

    player() : _name("Бот"), _color(1), _symbol('b') {};

    void set_name(std::string &name) {
        _name = name;
    }

    void upd_square(unsigned a, unsigned b);

    [[nodiscard]] unsigned color() const;

    [[nodiscard]] char symbol() const;

    unsigned square();

    std::string name();

    void set_color(unsigned color);
};



#endif //SQUARE_PLAYER_H
