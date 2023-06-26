#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <SFML/Graphics.hpp>
#include <sstream>
#include "puzzle15.h"
#include "game.h"


// макроси для визначення, чи знаходиться курсор миші в просторі кнопок
#define scramble_button_hovered (sf::Mouse::getPosition(window).x>btn_scramble.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_scramble.getGlobalBounds().left+btn_scramble.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_scramble.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_scramble.getGlobalBounds().top+btn_scramble.getGlobalBounds().height)
#define solve_button_hovered (sf::Mouse::getPosition(window).x>btn_solve.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_solve.getGlobalBounds().left+btn_solve.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_solve.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_solve.getGlobalBounds().top+btn_solve.getGlobalBounds().height)
#define hard_button_hovered (sf::Mouse::getPosition(window).x>btn_hard.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_hard.getGlobalBounds().left+btn_hard.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_hard.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_hard.getGlobalBounds().top+btn_hard.getGlobalBounds().height)
#define random_button_hovered (sf::Mouse::getPosition(window).x>btn_random.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_random.getGlobalBounds().left+btn_random.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_random.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_random.getGlobalBounds().top+btn_random.getGlobalBounds().height)
#define easy_button_hovered (sf::Mouse::getPosition(window).x>btn_easy.getGlobalBounds().left&&sf::Mouse::getPosition(window).x<btn_easy.getGlobalBounds().left+btn_easy.getGlobalBounds().width&&sf::Mouse::getPosition(window).y>btn_easy.getGlobalBounds().top&&sf::Mouse::getPosition(window).y<btn_easy.getGlobalBounds().top+btn_easy.getGlobalBounds().height)

// ініціалізація основних кольорів 
sf::Color Light_Blue = sf::Color(0, 0, 0);
sf::Color White = sf::Color(255, 255, 255);
sf::Color Dark_Blue_Grey = sf::Color(33, 42, 47);
sf::Color Dark_Blue_Grey_Hover = sf::Color(27, 34, 38);
// ініціалізація вікна програми та background board
sf::RenderWindow window(sf::VideoMode(440, 640), "15 Puzzle", sf::Style::Close);
sf::RenderWindow window1(sf::VideoMode(440, 640), "15 Puzzle", sf::Style::Close);
sf::RectangleShape board(sf::Vector2f(440, 640));

// ініціалізація всіх фігур програми
sf::RectangleShape btn_scramble(sf::Vector2f(180, 70));
sf::RectangleShape btn_solve(sf::Vector2f(180, 70));
sf::RectangleShape btn_time(sf::Vector2f(260, 50));
sf::RectangleShape btn_timer(sf::Vector2f(260, 50));
sf::RectangleShape generator_title(sf::Vector2f(260, 50));
sf::RectangleShape end_game(sf::Vector2f(360, 50));
sf::RectangleShape btn_hard(sf::Vector2f(100, 50));
sf::RectangleShape btn_random(sf::Vector2f(150, 50));
sf::RectangleShape btn_easy(sf::Vector2f(100, 50));
sf::RectangleShape solving_btn(sf::Vector2f(260, 50));
sf::RectangleShape choose_state(sf::Vector2f(360, 50));

// ініціалізація картинок
sf::Image im_texture, im_void_tile;
// ініціалізація текстури та спрайту
sf::Texture texture, texture_void_tile;
sf::Sprite tile[4][4];

// нормальний (розв'язаний) стан пластин
unsigned short int normal_state[4][4] =
{
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,0}
};

void set_position_of_tiles(unsigned short int state[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            puzzle15::position normal_position = puzzle15::search_in(normal_state, state[i][j]);
            tile[normal_position.y][normal_position.x].setPosition(i * 100 + 30, j * 100 + 130);
        }

    }
}

sf::Font font;
sf::Text text_scramble, text_solve, text_time, text_generator, end_text, text_hard, text_random, solving_text, text_easy, choose_text;

// функція задання текстури для плит 
void made_texture_properly()
{
    im_texture.loadFromFile("png.png");
    im_void_tile.create(80, 80, White);
    texture_void_tile.loadFromImage(im_void_tile);
    texture.loadFromImage(im_texture);
}
// функція задання позиції та налаштування всіх графічних компонентів 
void set_start_gui() {
    font.loadFromFile("MontserratAlternates-ExtraLight.otf");
    board.setFillColor(sf::Color(255, 255, 255));
    board.setPosition(0, 0);

    btn_hard.setFillColor(Dark_Blue_Grey);
    btn_hard.setPosition(30, 290);

    btn_random.setFillColor(Dark_Blue_Grey);
    btn_random.setPosition(145, 290);

    btn_easy.setFillColor(Dark_Blue_Grey);
    btn_easy.setPosition(310, 290);

    choose_state.setFillColor(Dark_Blue_Grey);
    choose_state.setPosition(40, 200);

    text_hard.setFont(font);
    text_hard.setString("Hard");
    text_hard.setCharacterSize(30);
    text_hard.setPosition(40, 295);

    text_random.setFont(font);
    text_random.setString("Random");
    text_random.setCharacterSize(30);
    text_random.setPosition(155, 295);

    text_easy.setFont(font);
    text_easy.setString("Easy");
    text_easy.setCharacterSize(30);
    text_easy.setPosition(320, 295);

    choose_text.setFont(font);
    choose_text.setString("Choose state of tiles.");
    choose_text.setCharacterSize(30);
    choose_text.setPosition(60, 205);
}
void draw_start_gui() {
    window1.draw(board);
    window1.draw(btn_hard);
    window1.draw(btn_random);
    window1.draw(btn_easy);
    window1.draw(text_hard);
    window1.draw(text_random);
    window1.draw(text_easy);
    window1.draw(choose_state);
    window1.draw(choose_text);
}
void set_position_of_gui(int count)
{

    //GUI
    board.setFillColor(Light_Blue);
    board.setPosition(0, 0);

    btn_scramble.setFillColor(Dark_Blue_Grey);
    btn_scramble.setPosition(30, 30);

    btn_solve.setFillColor(Dark_Blue_Grey);
    btn_solve.setPosition(230, 30);

    btn_time.setFillColor(Dark_Blue_Grey);
    btn_time.setPosition(90, 550);

    generator_title.setFillColor(Dark_Blue_Grey);
    generator_title.setPosition(90, 290);

    end_game.setFillColor(Dark_Blue_Grey);
    end_game.setPosition(40, 290);

    solving_btn.setFillColor(Dark_Blue_Grey);
    solving_btn.setPosition(90, 290);


    //tiles
    made_texture_properly();
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tile[i][j].setTexture(texture);
        }
    }
    tile[3][3].setTexture(texture_void_tile);
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tile[i][j].setTextureRect(sf::IntRect(i * 80, j * 80, 80, 80));
        }
    }
    
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tile[i][j].setPosition(i * 100 + 30, j * 100 + 130);
        }
    }
    

    //text
    font.loadFromFile("MontserratAlternates-ExtraLight.otf");
    text_scramble.setFont(font);
    text_scramble.setString("Shuffle");
    text_scramble.setCharacterSize(30);
    text_scramble.setPosition(65, 44);

    text_solve.setFont(font);
    text_solve.setString("Solve");
    text_solve.setCharacterSize(30);
    text_solve.setPosition(280, 44);
        
    text_time.setFont(font);
    std::stringstream s;
    s << "K-ct operations: " << count;
    text_time.setString(s.str());
    text_time.setCharacterSize(25);
    text_time.setPosition(100, 560);
    
    end_text.setFont(font);
    end_text.setString("Check file for solution!");
    end_text.setCharacterSize(30);
    end_text.setPosition(50, 295);

    solving_text.setFont(font);
    solving_text.setString("Solving...");
    solving_text.setCharacterSize(30);
    solving_text.setPosition(155, 295);
}
// функція малювання всіх графічних компонентів
void draw_gui()
{

    window.draw(board);
    window.draw(btn_scramble);
    window.draw(btn_solve);
    window.draw(btn_time);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            window.draw(tile[i][j]);
        }
    }

    window.draw(text_scramble);
    window.draw(text_solve);
    window.draw(text_time);
}


#endif // GRAPHICS_H
