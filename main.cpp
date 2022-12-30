#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#include "structures/color/color.h"
#include "structures/playing_field/playing_field.h"
#include "structures/player/player.h"
#include "structures/cubes/cubes.h"

unsigned user_choice;
playing_field f;
std::string name1 = "player 1";
player p1(name1, 12, 'a');

std::string name2 = "player 2";
player p2(name2, 9, 'b');

std::string bot_name = "Бот";
player bot(bot_name, 1, 'z');
unsigned bot_choice;

cubes c;

int x_start, y_start, x_end, y_end;

unsigned get_difference(unsigned x, unsigned y) {
    return std::max(x, y) - std::min(x, y);
}

bool is_chance() {
    if (f.step())
        return f.free_area() + p1.square() >=
               p2.square();
    else
        return f.free_area() + p2.square() >=
               p1.square();
}

bool is_chance_bot() {
    if (f.step())
        return f.free_area() + p1.square() >=
               bot.square();
    else
        return f.free_area() + bot.square() >=
               p1.square();
}

void press_enter_to_continue() {
    std::cout << "Нажмите Enter для продолжения..." << std::endl;

    fflush(stdin);

    while (getchar() != '\n');
}

void get_user_choice(unsigned from, unsigned to) {
    std::cin >> user_choice;

    if (user_choice < from || user_choice > to) {
        std::cerr << "Неверные значения. Повторите попытку >>>\n";
        std::cin >> user_choice;
    }
}

void get_bot_random() {
    c.roll_the_dice();
    bot_choice = c.sum();
}

void print_interface_center(std::string &s, bool is_need_frame) {
    unsigned f_size = f.size() * 3 + 4;
    unsigned s_size = f.length(s);
    unsigned space_length = f_size - s_size;
    unsigned frame_length = f_size;

    if (is_need_frame) {
        for (unsigned i = 0; i < frame_length; i++)
            std::cout << termcolor::on_bright_grey <<
                      termcolor::bright_green << '-';

        std::cout << '\n';
    }

    for (unsigned i = 0; i < space_length / 2; i++)
        std::cout << termcolor::on_bright_grey <<
                  termcolor::bright_green << ' ';

    std::cout << s;

    for (unsigned i = space_length / 2; i < space_length; i++)
        std::cout << ' ';

    std::cout << '\n';

    if (is_need_frame) {
        for (unsigned i = 0; i < frame_length; i++)
            std::cout << termcolor::on_bright_grey <<
                      termcolor::bright_green << '-';

        std::cout << '\n';
    }
}

void print_interface_left(std::string &s, bool is_need_frame) {
    unsigned f_size = f.size() * 3 + 4;
    unsigned s_size = f.length(s);
    unsigned space_length = f_size - s_size;
    unsigned frame_length = f_size;

    if (is_need_frame) {
        for (unsigned i = 0; i < frame_length; i++)
            std::cout << termcolor::on_bright_grey <<
                      termcolor::bright_green << '-';

        std::cout << '\n';
    }

    std::cout << termcolor::on_bright_grey <<
              termcolor::bright_green << s;

    for (unsigned i = 0; i < space_length; i++)
        std::cout << ' ';

    std::cout << '\n';

    if (is_need_frame) {
        for (unsigned i = 0; i < frame_length; i++)
            std::cout << termcolor::on_bright_grey <<
                      termcolor::bright_green << '-';

        std::cout << '\n';
    }
}

void print_interface_center(std::vector<std::pair<std::string, bool>> &strings) {
    for (auto &string: strings)
        print_interface_center(string.first, string.second);
}

void print_interface_left(std::vector<std::pair<std::string, bool>> &strings) {
    for (auto &string: strings)
        print_interface_left(string.first, string.second);
}

void print_game_mod_menu() {
    std::string s1 = "Выберите режим игры:";
    std::string s2 = "1. Против игрока";
    std::string s3 = "2. Против бота";

    std::vector<std::pair<std::string, bool>> strings;

    strings.push_back(std::pair<std::string, bool>(s1, true));
    strings.push_back(std::pair<std::string, bool>(s2, false));
    strings.push_back(std::pair<std::string, bool>(s3, false));

    print_interface_center(strings);

    get_user_choice(1, 2);
}

void print_field_size_menu() {
    std::string s1 = "Выберите размер игрового поля:";
    std::string s2 = "1. Маленькое (20 x 20)";
    std::string s3 = "2. Среднее (30 x 30)";
    std::string s4 = "3. Большое (38 x 38)";

    std::vector<std::pair<std::string, bool>> strings;

    strings.push_back(std::pair<std::string, bool>(s1, true));
    strings.push_back(std::pair<std::string, bool>(s2, false));
    strings.push_back(std::pair<std::string, bool>(s3, false));
    strings.push_back(std::pair<std::string, bool>(s4, false));

    print_interface_center(strings);

    get_user_choice(1, 3);
}

void auto_choice_first_step() {
    std::string s1 = "Выбор первого хода";
    print_interface_center(s1, true);

    std::cout << termcolor::reset << p1.name() <<
              ", введите число от 2 до 12 >>>                                  \n";

    get_user_choice(2, 12);
    unsigned first_player_choice = user_choice;

    std::cout << p2.name() <<
              ", ведите число от 2 до 12 >>>                                \n";

    get_user_choice(2, 12);
    unsigned second_player_choice = user_choice;


    c.roll_the_dice();
    unsigned cubes_numbers = c.sum();

    unsigned first_player_difference = get_difference(
            first_player_choice, cubes_numbers);

    unsigned second_player_difference = get_difference(
            second_player_choice, cubes_numbers);

    for (unsigned i = 0; i < f.size() * 3 + 4; i++)
        std::cout << '-';
    std::cout << '\n';

    std::string s2 = "Выпало: ";
    std::string c_string = std::to_string(c.sum());
    s2 += c_string;

    print_interface_center(s2, true);

    if (first_player_difference < second_player_difference) {
        std::cout <<
                  "Ход игрока " << p1.name() << '\n';
    } else {
        std::cout <<
                  "Ход игрока " << p2.name() << '\n';
        f.change_player_step();
    }
}

void create_playing_field(unsigned size_code) {
    switch (size_code) {
        case (1):
            f.set_size(20);
            break;
        case (2):
            f.set_size(30);
            break;
        case (3):
            f.set_size(38);
            break;
        default:
            f.set_size(20);
            break;
    }
}

void print_menu() {
    std::string s1 = "МЕНЮ";
    std::string s2;
    std::string s3 = "1. Играть";
    std::string s4 = "2. Настройки игроков";
    std::string s5 = "3. Правила";

    std::vector<std::pair<std::string, bool>> strings;

    strings.push_back(std::pair<std::string, bool>(s1, true));
    strings.push_back(std::pair<std::string, bool>(s2, false));
    strings.push_back(std::pair<std::string, bool>(s3, false));
    strings.push_back(std::pair<std::string, bool>(s4, false));
    strings.push_back(std::pair<std::string, bool>(s5, false));

    print_interface_center(strings);
}

void print_rules() {
    std::string s = "Выбор первого хода";
    std::vector<std::pair<std::string, bool>> strings;

    print_interface_center(s, true);

    s = "Игроки загадывают по одному числу. Затем выпадает рандомное число.";
    strings.push_back(std::pair<std::string, bool>(s, false));

    s = "Кто загадал число ближе к выпавшему, тот начинает игру.";
    strings.push_back(std::pair<std::string, bool>(s, false));

    print_interface_center(strings);
    strings.clear();

    s = "Правила игры";
    print_interface_center(s, true);

    s = "Игроки по очереди бросают кубики. Задача - составить прямоугольник"
        " со сторонами,";
    strings.push_back(std::pair<std::string, bool>(s, false));

    s = "равными выпавшим числам. Далее игрок размещает свой прямоугольник на"
        "свободной территории.";
    strings.push_back(std::pair<std::string, bool>(s, false));

    s = "Если разместить прямоугольник невозможно, игрок пропускает ход.";
    strings.push_back(std::pair<std::string, bool>(s, false));

    s = "Побеждает тот, кто занял больше площади";
    strings.push_back(std::pair<std::string, bool>(s, false));

    print_interface_center(strings);

    s = "1. Вернуться в меню";
    print_interface_center(s, false);

    get_user_choice(1, 1);
}

void print_cubes_numbers() {
    std::string s1 = "Выпало: ";
    std::string s2 = std::to_string(c.numbers().first);
    std::string s3 = std::to_string(c.numbers().second);

    s1 += s2;
    s1.push_back(' ');
    s1 += s3;

    s2.clear();
    s3.clear();

    print_interface_center(s1, true);
}

void end_the_game(player &loser, player &winner) {
    std::string end = "ИГРА ОКОНЧЕНА";
    std::string win = "Победа: ";
    std::string win_player = winner.name();

    win += win_player;

    win_player.clear();

    std::string points = "Счёт:";
    std::string p1_points = std::to_string(winner.square());
    std::string p2_points = std::to_string(loser.square());

    std::string p1_name = winner.name() + ' ' + p1_points;
    std::string p2_name = loser.name() + ' ' + p2_points;

    p1_points.clear();
    p2_points.clear();

    print_interface_center(end, true);

    std::vector<std::pair<std::string, bool>> strings;
    strings.push_back(std::pair<std::string, bool>(win, false));
    strings.push_back(std::pair<std::string, bool>(points, false));
    strings.push_back(std::pair<std::string, bool>(p1_name, false));
    strings.push_back(std::pair<std::string, bool>(p2_name, false));

    print_interface_left(strings);

    x_start = -1;
}

void get_square();

void play() {
    if (f.step())
        std::cout << termcolor::reset << p1.name();
    else
        std::cout << termcolor::reset << p2.name();

    std::cout << ", выберите действие:\n"
                 "1. Бросить кубики\n"
                 "2. Сдаться\n";

    get_user_choice(1, 2);

    if (user_choice == 1) {
        c.roll_the_dice();
        f.print_field(p1, p2);
        print_cubes_numbers();

        get_square();
        f.print_field(p1, p2);
        f.change_player_step();

    } else if (f.step()) {
        end_the_game(p1, p2);
    } else {
        end_the_game(p2, p1);
    }
}

void get_end_coordinates(player &_p2);

void bot_play();

void get_start_coordinates(player &_p2) {
    std::string s1 = "Чтобы пропустить ход, введите координаты 0 0";
    std::string s2 = "Чтобы сдаться, введите координаты -1 -1";

    std::vector<std::pair<std::string, bool>> strings;
    strings.push_back(std::pair<std::string, bool>(s1, false));
    strings.push_back(std::pair<std::string, bool>(s2, false));

    print_interface_center(strings);

    s1.clear();
    s2.clear();
    strings.clear();

    std::string s = "Введите координаты левого верхнего угла >>> ";
    print_interface_left(s, false);

    std::cin >> y_start >> x_start;

    if (y_start == 0 || x_start == 0) {
        f.change_player_step();
        if (_p2.name() == "Бот")
            bot_play();
        else play();
    } else if (y_start == -1 || x_start == -1) {
        if (f.step())
            end_the_game(p1, _p2);
        else
            end_the_game(_p2, p1);
    }

    else {
        while (!f.check_symbol(x_start, y_start)) {
            std::cerr << "Клетка занята. Укажите другие координаты\n";
            get_start_coordinates(_p2);
        }

        get_end_coordinates(_p2);
    }
}

void get_end_coordinates(player &_p2) {
    std::string s = "Введите координаты правого нижнего угла >>>";
    print_interface_left(s, false);

    std::cin >> y_end >> x_end;

    while (!f.check_square(y_start, x_start, y_end, x_end,
                           c.numbers().first, c.numbers().second)) {
        std::cerr << "Территория занята или размеры сторон не совпадают с выпавшими. Укажите другие координаты\n";
        get_start_coordinates(_p2);
        get_end_coordinates(_p2);
    }
}

void get_square() {
    get_start_coordinates(p2);

    if (x_start != -1) {
        std::cout << termcolor::on_bright_green <<
                  termcolor::bright_white << "Успешно";
        std::cout << termcolor::reset << '\n';

        if (f.step()) {
            f.create_square(y_start, x_start, y_end, x_end, p1);
            p1.upd_square(c.numbers().first, c.numbers().second);
        } else {
            f.create_square(y_start, x_start, y_end, x_end, p2);
            p2.upd_square(c.numbers().first, c.numbers().second);
        }

        f.upd_area(c.numbers().first, c.numbers().second);
    }
}

void get_square_with_bot() {
    get_start_coordinates(bot);

    if (x_start != -1) {
        std::cout << termcolor::on_bright_green <<
                  termcolor::bright_white << "Успешно";
        std::cout << termcolor::reset << '\n';

        f.create_square(y_start, x_start, y_end, x_end, p1);
        p1.upd_square(c.numbers().first, c.numbers().second);

        f.upd_area(c.numbers().first, c.numbers().second);
    }
}

void play_with_player() {
    print_field_size_menu();
    create_playing_field(user_choice);

    f.print_field(p1, p2);
    auto_choice_first_step();

    play();
}

void choice_first_step_bot() {
    std::string s1 = "Выбор первого хода";
    print_interface_center(s1, true);

    std::cout << termcolor::reset << p1.name() <<
              ", введите число от 2 до 12 >>> \n";

    get_user_choice(2, 12);
    unsigned first_player_choice = user_choice;

    get_bot_random();

    std::cout << termcolor::reset << bot.name() <<
              " выбирает " << bot_choice << '\n';

    c.roll_the_dice();
    unsigned cubes_numbers = c.sum();

    unsigned first_player_difference = get_difference(
            first_player_choice, cubes_numbers);

    unsigned bot_difference = get_difference(
            bot_choice, cubes_numbers);

    std::string s2 = "Выпало: ";
    std::string c_string = std::to_string(c.sum());
    s2 += c_string;

    print_interface_center(s2, true);

    if (first_player_difference < bot_difference) {
        std::cout <<
                  "Ход игрока " << p1.name() << '\n';
    } else {
        std::cout <<
                  "Ход игрока " << bot.name() << '\n';
        f.change_player_step();
    }

    press_enter_to_continue();
}

void search_area(bool &is_accommodate, unsigned x, unsigned y) {
    for (unsigned row = 0; row < f.size() - x && !is_accommodate; row++) {
        for (unsigned col = 0; col < f.size() - y && !is_accommodate; col++) {
            if (f.field()[row][col] == '.') {
                for (unsigned i_row = 0; i_row < x; i_row++) {
                    for (unsigned i_col = 0; i_col < y; i_col++) {
                        if (f.field()[i_row + row][i_col + col] == '.' &&
                            i_row == x - 1 && i_col == y - 1) {
                            is_accommodate = true;
                            x_start = row + 1;
                            y_start = col + 1;
                            x_end = row + i_row + 1;
                            y_end = col + i_col + 1;
                        } else if (f.field()[i_row + row][i_col + col] != '.') {
                            i_row = x;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void get_coordinates_bot() {
    unsigned x = c.numbers().first;
    unsigned y = c.numbers().second;

    bool is_accommodate = false;

    search_area(is_accommodate, x, y);

    if (!is_accommodate) {
        unsigned t = x;
        x = y;
        y = t;
        search_area(is_accommodate, x, y);
    }

    if (!is_accommodate)
        x_start = 0, y_start = 0, x_end = 0, y_end = 0;
}

void get_bot_square() {
    get_coordinates_bot();
    f.create_square(y_start, x_start, y_end, x_end, bot);
    bot.upd_square(c.numbers().first, c.numbers().second);
    f.upd_area(c.numbers().first, c.numbers().second);
}

void bot_play() {
    if (f.step()) {
        std::cout << termcolor::reset << p1.name()
                  << ", выберите действие:\n"
                     "1. Бросить кубики\n"
                     "2. Сдаться\n";

        get_user_choice(1, 2);
        if (user_choice == 1) {
            c.roll_the_dice();
            f.print_field(p1, bot);
            print_cubes_numbers();

            bool _f = f.step();
            get_square_with_bot();
            if (x_start != -1) {
                f.print_field(p1, bot);
                if (_f == f.step())
                    f.change_player_step();
            }
        } else {
            end_the_game(p1, bot);
        }
    } else {
        std::string s = "Бот ходит";
        print_interface_center(s, true);

        c.roll_the_dice();
        print_cubes_numbers();

        get_bot_square();
        press_enter_to_continue();
        f.print_field(p1, bot);
        f.change_player_step();
    }
}

void play_with_bot() {
    print_field_size_menu();
    create_playing_field(user_choice);

    f.print_field(p1, bot);
    choice_first_step_bot();

    bot_play();
}

void player_settings(player &p);

void change_name(player &p) {
    std::string s1 = "Чтобы вернуться назад, введите -1";
    print_interface_left(s1, false);
    s1 = "Введите имя >>> ";
    print_interface_left(s1, false);

    std::cin >> s1;
    p.set_name(s1);

    std::cout << termcolor::green << "Успешно";
    press_enter_to_continue();
    player_settings(p);
}

void change_color(player &p) {
    for (int i = 1; i < 15; i++) {
        f.print_color_space(i);
    }
    std::cout << termcolor::reset << '\n';

    for (int i = 1; i < 14; i++) {
        if (i <= 10)
            std::cout << ' ' << i << ' ';
        else std::cout << i << ' ';
    }
    std::cout << '\n';

    std::string s1 = "14. В меню";
    print_interface_left(s1, false);

    s1 = "Введите номер цвета >>>";
    print_interface_left(s1, false);

    get_user_choice(1, 14);
    if (user_choice == 14)
        print_menu();
    else
        p.set_color(user_choice);
}

void player_settings(player &p) {
    std::string s1 = "1. Имя: ";
    s1 += p.name();

    print_interface_left(s1, false);
    s1.clear();

    s1 = "2. Цвет: ";
    std::cout << termcolor::on_bright_grey << s1;

    f.print_color_space(p1.color());
    for (unsigned i = 0; i < 82; i++)
        std::cout << termcolor::on_bright_grey << ' ';

    std::cout << termcolor::reset << '\n';

    s1 = "3. В меню";
    print_interface_left(s1, false);

    s1 = "Выберите пункт, который хотите изменить >>>";
    print_interface_left(s1, false);

    get_user_choice(1, 3);

    if (user_choice == 1) {
        change_name(p);
    } else if (user_choice == 2) {
        change_color(p);
    } else print_menu();
}

void print_user_settings() {
    std::string p1_name = "1. ";
    p1_name += p1.name();

    std::string p2_name = "2. ";
    p2_name += p2.name();

    print_interface_left(p1_name, false);
    print_interface_left(p2_name, false);

    p1_name.clear();
    p2_name.clear();

    std::string s1 = "3. В меню";
    print_interface_left(s1, false);

    s1 = "Введите номер игрока, которого хотите изменить >>>";
    print_interface_left(s1, false);

    s1.clear();

    get_user_choice(1, 3);

    if (user_choice == 1)
        player_settings(p1);
    else if (user_choice == 2)
        player_settings(p2);
    else print_menu();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(nullptr));

    f.set_size(30);

    while (user_choice != 2 && x_start != -1) {
        print_menu();
        get_user_choice(1, 3);

        if (user_choice == 1) {
            print_game_mod_menu();
            if (user_choice == 1) {
                play_with_player();
                while (is_chance() || x_start != -1)
                    play();

            } else {
                play_with_bot();
                while (is_chance_bot() && x_start != -1)
                    bot_play();
            }
        } else if (user_choice == 2) {
            print_user_settings();
        } else {
            print_rules();
        }
    }

    return 0;
}