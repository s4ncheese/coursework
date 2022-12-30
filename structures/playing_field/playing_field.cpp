#include "playing_field.h"

playing_field::playing_field() {
    set_size(20);
    create_field();
}

playing_field::playing_field(unsigned size) {
    set_size(size);
    create_field(size);
}

void playing_field::set_size(unsigned size) {
    _size = size;

    create_field();
}

void playing_field::create_field() {
    _field.resize(_size);
    for (auto &v: _field)
        v.resize(_size, '.');
}

void playing_field::create_field(unsigned size) {
    _field.resize(size);
    for (auto &v: _field)
        v.resize(size, '.');
}

unsigned playing_field::size() const {
    return _size;
}

void playing_field::print_color_space(unsigned color) {
    switch (color) {
        case (1):
            std::cout << termcolor::on_red << "   ";

            break;

        case (2):
            std::cout << termcolor::on_green << "   ";

            break;

        case (3):
            std::cout << termcolor::on_yellow << "   ";

            break;

        case (4):
            std::cout << termcolor::on_blue << "   ";

            break;

        case (5):
            std::cout << termcolor::on_magenta << "   ";

            break;

        case (6):
            std::cout << termcolor::on_cyan << "   ";

            break;

        case (7):
            std::cout << termcolor::on_bright_red << "   ";

            break;

        case (8):
            std::cout << termcolor::on_bright_green << "   ";

            break;

        case (9):
            std::cout << termcolor::on_bright_yellow << "   ";

            break;

        case (10):
            std::cout << termcolor::on_bright_blue << "   ";

            break;

        case (11):
            std::cout << termcolor::on_bright_magenta << "   ";

            break;

        case (12):
            std::cout << termcolor::on_bright_cyan << "   ";

            break;

        case (13):
            std::cout << termcolor::on_bright_white << "   ";

            break;
    }
}

void playing_field::print_field(player &p1, player &p2) {
    auto size = this->size() + 1;

    std::string s = "Игровое поле:";

    unsigned f_size = this->size() * 3 + 4;
    unsigned s_size = length(s);
    unsigned space_length = f_size - s_size;
    unsigned frame_length = f_size;

    for (unsigned i = 0; i < frame_length; i++)
        std::cout << termcolor::on_bright_grey <<
                  termcolor::bright_green << '-';

    std::cout << '\n';

    for (unsigned i = 0; i < space_length / 2; i++)
        std::cout << termcolor::on_bright_grey <<
                  termcolor::bright_green << ' ';

    std::cout << s;

    for (unsigned i = space_length / 2; i < space_length; i++)
        std::cout << ' ';

    std::cout << '\n';

    for (unsigned i = 0; i < frame_length; i++)
        std::cout << termcolor::on_bright_grey <<
                  termcolor::bright_green << '-';

    std::cout << '\n';

    for (size_t i_col = 0; i_col < size; i_col++) {
        if (i_col < 9)
            std::cout << termcolor::reset << i_col << "  ";
        else
            std::cout << i_col << ' ';
    }

    std::cout << " 0\n";

    for (unsigned i_row = 0; i_row < size - 1; i_row++) {
        if (i_row < 9)
            std::cout << 1 + i_row << "  ";
        else
            std::cout << 1 + i_row << ' ';

        for (unsigned i_col = 0; i_col < size - 1; i_col++) {
            auto symbol = _field[i_row][i_col];
            if (symbol != '.') {
                unsigned color;
                if (symbol == 'a')
                    color = p1.color();
                else
                    color = p2.color();

                print_color_space(color);
            } else
                std::cout << termcolor::bright_green << termcolor::on_bright_grey
                          << _field[i_row][i_col] << "  ";
        }

        std::cout << termcolor::reset << 1 + i_row << '\n';
    }

    for (unsigned i_col = 0; i_col < size; i_col++) {
        if (i_col < 9) {
            std::cout << i_col << "  ";
        } else {
            std::cout << i_col << ' ';
        }
    }
    std::cout << " 0\n";
}

void playing_field::create_square(unsigned x_start, unsigned y_start,
                                  unsigned x_end, unsigned y_end, player &p) {
    x_start--;
    y_start--;
    x_end--;
    y_end--;

    for (unsigned x = y_start; x <= y_end; x++)
        for (unsigned y = x_start; y <= x_end; y++)
            _field[x][y] = p.symbol();
}

void playing_field::change_player_step() {
    _is_first_player_step = !_is_first_player_step;
}

bool playing_field::step() {
    return _is_first_player_step;
}

unsigned playing_field::free_area() {
    return _free_area;
}

bool playing_field::check_symbol(unsigned x, unsigned y) {
    x--;
    y--;

    return _field[x][y] == '.';
}

bool playing_field::check_square(
        unsigned x_start, unsigned y_start,
        unsigned x_end, unsigned y_end,
        unsigned c_first, unsigned c_second) {
    x_start--;
    y_start--;
    x_end--;
    y_end--;


    if (y_start > y_end || x_start > x_end) return false;

    unsigned x_length = y_end - y_start + 1;
    unsigned y_length = x_end - x_start + 1;

    if (!((c_first == x_length && c_second == y_length) ||
          (c_first == y_length && c_second == x_length)))
        return false;

    for (unsigned x = y_start; x <= y_end; x++)
        for (unsigned y = x_start; y <= x_end; y++)
            if (_field[x][y] != '.')
                return false;

    return true;
}

void playing_field::upd_area(unsigned x, unsigned y) {
    _free_area -= x * y;
}

unsigned playing_field::length(std::string &str) {
    unsigned size = 0;
    for (auto byte: str) {
        size += (((byte & 0x80) == 0) || ((byte & 0xC0) == 0xC0));
    }
    return size;
}

std::vector<std::vector<char>> playing_field::field() {
    return _field;
}

