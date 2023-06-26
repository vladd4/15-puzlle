#include "graphics.h"


int main()
{
    Game game;  // ініціалізація гри
    
    while (window1.isOpen()) {
        set_start_gui();
        sf::Event event;
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window1.close();
            }
            if (hard_button_hovered)
                btn_hard.setFillColor(Dark_Blue_Grey_Hover);
            else
                btn_hard.setFillColor(Dark_Blue_Grey);
            if (random_button_hovered)
                btn_random.setFillColor(Dark_Blue_Grey_Hover);
            else
                btn_random.setFillColor(Dark_Blue_Grey);
            if (easy_button_hovered)
                btn_easy.setFillColor(Dark_Blue_Grey_Hover);
            else
                btn_easy.setFillColor(Dark_Blue_Grey);
        }
        window1.clear();
        draw_start_gui();
        if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (hard_button_hovered) {
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                game.state_of_tiles[i][j] = game.hard[i][j];
                            }
                        }
                        
                        window1.close();
                    }
                    else if (random_button_hovered) {
                        game.scramble();
                        window1.close();
                    }
                    else if (easy_button_hovered) {
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                game.state_of_tiles[i][j] = game.easy[i][j];
                                
                            }
                        }
                        
                        window1.close();
                    }
                }
            }
        
        window1.display();  
    }
    if (!window1.isOpen()) {
        while (window.isOpen())
        {

            set_position_of_gui(game.count); // задання налаштувань та позиції компонентів

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    write_in_file(game.count, "close button"); // запис даних у вихідний файл
                }
                if (scramble_button_hovered)
                    btn_scramble.setFillColor(Dark_Blue_Grey_Hover);
                else
                    btn_scramble.setFillColor(Dark_Blue_Grey);
                if (solve_button_hovered)
                    btn_solve.setFillColor(Dark_Blue_Grey_Hover);
                else
                    btn_solve.setFillColor(Dark_Blue_Grey);

                // обробка події натискання на кнопки
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (scramble_button_hovered) {
                            write_in_file(game.count, "scramble button"); // запис даних у вихідний файл
                            game.scramble(); // перемішати пластини 
                        }
                        else if (solve_button_hovered) {
                            
                            write_in_file(game.count, "solve button"); // запис даних у вихідний файл
                            bool flag = true;
                            while (flag) {
                                board.setFillColor(sf::Color(255, 255, 255, 225));
                                window.draw(board);
                                window.draw(solving_btn);
                                window.draw(solving_text);
                                window.display();
                                game.solve(flag);       
                            }
                            if (flag == false) {
                                int value = 1;
                                for (int i = 0; i < 4; i++) {
                                    for (int j = 0; j < 4; j++) {
                                        game.state_of_tiles[j][i] = value;
                                        value++;
                                    }
                                }
                                game.state_of_tiles[3][3] = 0;
                            }      
                        }
                    }
                }

                // переміщення пластини в заданому напрямку
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    game.move_tile(Game::up);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    game.move_tile(Game::down);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    game.move_tile(Game::left);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    game.move_tile(Game::right);
                }
            }


            window.clear();
           
            set_position_of_tiles(game.state_of_tiles);

            draw_gui(); // малюємо всі графічні компоненти

          
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (solve_button_hovered) {
                        
                        board.setFillColor(sf::Color(255, 255, 255, 225));
                        window.draw(board);
                        window.draw(end_game);
                        window.draw(end_text);
                        
                    }
                }
            }
            window.display();
        }
    }
}
