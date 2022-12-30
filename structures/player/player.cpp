#include "player.h"

void player::upd_square(const unsigned a, const unsigned b) {
    _square += a * b;
}

unsigned player::color() const {
    return player::_color;
}

char player::symbol() const {
    return _symbol;
}

unsigned player::square() {
    return _square;
}

std::string player::name() {
    return _name;
}

void player::set_color(unsigned color) {
    _color = color;
}
