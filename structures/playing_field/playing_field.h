#ifndef SQUARE_PLAYING_FIELD_H
#define SQUARE_PLAYING_FIELD_H

#include<iostream>
#include <vector>
#include "../color/color.h"
#include "../player/player.h"

struct playing_field {
private:
    unsigned _size = 20;
    unsigned _free_area = _size * _size;
    std::vector<std::vector<char>> _field;
    bool _is_first_player_step = true;
public:
    playing_field();

    playing_field(unsigned size);

    void set_size(unsigned size);

    void create_field();

    void create_field(unsigned size);

    [[nodiscard]] unsigned size() const;

    void print_field(player &p1, player &p2);

    void create_square(unsigned x_start, unsigned y_start,
                       unsigned x_end, unsigned y_end, player &p);

    void change_player_step();

    bool step();

    unsigned free_area();

    bool check_symbol(unsigned x, unsigned y);

    bool check_square (unsigned x_start, unsigned y_start,
                       unsigned x_end, unsigned y_end,
                       unsigned c_first, unsigned c_second);

    void upd_area(unsigned x, unsigned y);

    unsigned length(std::string &str);

    std::vector<std::vector<char>> field();
    void print_color_space(unsigned color);
};

#endif //SQUARE_PLAYING_FIELD_H
