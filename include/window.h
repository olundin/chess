#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "chess.h"
#include "position.h"

class Window {
    public:
        Window(Chess& chess);
        ~Window();

        void update(); // Update controller
        void draw(); // Draw view
        bool is_open(); // Determines whether to run game or not
    protected:

    private:
        Chess& chess; // The model
        sf::RenderWindow window; // Window to receive input from and render to


        // VIEW

        const int SIZE = 100; // Size of each square in pixels

        // Textures
        sf::Texture squares_texture;
        sf::Texture pieces_texture;

        // Sprites
        sf::Sprite white_square_sprite;
        sf::Sprite black_square_sprite;

        sf::Sprite white_pawn_sprite;
        sf::Sprite white_rook_sprite;
        sf::Sprite white_knight_sprite;
        sf::Sprite white_bishop_sprite;
        sf::Sprite white_queen_sprite;
        sf::Sprite white_king_sprite;

        sf::Sprite black_pawn_sprite;
        sf::Sprite black_rook_sprite;
        sf::Sprite black_knight_sprite;
        sf::Sprite black_bishop_sprite;
        sf::Sprite black_queen_sprite;
        sf::Sprite black_king_sprite;

        sf::Sprite empty_sprite;

        // Draw sprite
        void draw_sprite(const float& x, const float& y, sf::Sprite& sprite);

        // Load sprite from texture
        sf::Sprite sprite_from_texture(const int& x, const int& y, const int& width, const int& height, const sf::Texture& texture);

        // Get correct sprite for piece
        sf::Sprite& get_sprite(Piece piece);

        // Highlight position square
        void highlight(Position pos, sf::Color color);


        // CONTROLLER

        Position first_selected;
        Position second_selected;

        Position mouse_position(); // Convert mouse position to board position
};

#endif // WINDOW_H
