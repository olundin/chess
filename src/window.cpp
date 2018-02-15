#include "window.h"

Window::Window(Chess& chess) : chess(chess) {
    // Create window
    window.create(sf::VideoMode(8 * SIZE, 8 * SIZE), "chess");

    // Load textures
    squares_texture.loadFromFile("res/squares.png", sf::IntRect(0, 0, 32, 16));
    pieces_texture.loadFromFile("res/pieces.png", sf::IntRect(0, 0, 96, 32));

    // Load sprites
    white_square_sprite = sprite_from_texture(0, 0, 16, 16, squares_texture);
    black_square_sprite = sprite_from_texture(16, 0, 16, 16, squares_texture);

    white_pawn_sprite= sprite_from_texture(0, 0, 16, 16, pieces_texture);
    white_rook_sprite = sprite_from_texture(16, 0, 16, 16, pieces_texture);
    white_knight_sprite = sprite_from_texture(32, 0, 16, 16, pieces_texture);
    white_bishop_sprite = sprite_from_texture(48, 0, 16, 16, pieces_texture);
    white_queen_sprite = sprite_from_texture(64, 0, 16, 16, pieces_texture);
    white_king_sprite = sprite_from_texture(80, 0, 16, 16, pieces_texture);

    black_pawn_sprite = sprite_from_texture(0, 16, 16, 16, pieces_texture);
    black_rook_sprite = sprite_from_texture(16, 16, 16, 16, pieces_texture);
    black_knight_sprite = sprite_from_texture(32, 16, 16, 16, pieces_texture);
    black_bishop_sprite = sprite_from_texture(48, 16, 16, 16, pieces_texture);
    black_queen_sprite = sprite_from_texture(64, 16, 16, 16, pieces_texture);
    black_king_sprite = sprite_from_texture(80, 16, 16, 16, pieces_texture);
}

Window::~Window() {}

bool Window::is_open() {
    return window.isOpen();
}


// VIEW

void Window::draw() {
    window.clear();

    // Counter and offset used to generate correct board pattern
    int square_offset = 0;
    int square_counter = 0;
    for(int y = 0; y < 8; y++) {
        square_offset++;
        for(int x = 0; x < 8; x++) {
            // Draw board square
            if((square_offset + square_counter) % 2 == 0)
                draw_sprite(x * SIZE, y * SIZE, black_square_sprite);
            else
                draw_sprite(x * SIZE, y * SIZE, white_square_sprite);

            square_counter++;

            // Draw piece
            draw_sprite(x * SIZE, y * SIZE, get_sprite(chess.board.get_piece(Position(x, y))));

            // Highlight selected position
            highlight(first_selected, sf::Color::Red);

            // Highlight available moves
            for(Position p : chess.board.get_moves(first_selected)) {
                highlight(p, sf::Color::Green);
            }
        }
    }

    window.display();
}

void Window::draw_sprite(const float& x, const float& y, sf::Sprite& sprite) {
    sprite.setPosition(x, y);
    window.draw(sprite);
}

sf::Sprite Window::sprite_from_texture(const int& x, const int& y, const int& width, const int& height, const sf::Texture& texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture, false);
    sprite.setTextureRect(sf::IntRect(x, y, width, height));
    sprite.setScale((SIZE / width), (SIZE / width));
    return sprite;
}

sf::Sprite& Window::get_sprite(Piece piece) {
        switch(piece) {
        case white_pawn:
            return white_pawn_sprite; break;
        case white_rook:
            return white_rook_sprite;
        case white_knight:
            return white_knight_sprite;
        case white_bishop:
            return white_bishop_sprite;
        case white_queen:
            return white_queen_sprite;
        case white_king:
            return white_king_sprite;
        case black_pawn:
            return black_pawn_sprite;
        case black_rook:
            return black_rook_sprite;
        case black_knight:
            return black_knight_sprite;
        case black_bishop:
            return black_bishop_sprite;
        case black_queen:
            return black_queen_sprite;
        case black_king:
            return black_king_sprite;
        default:
            return empty_sprite;
        }
}

void Window::highlight(Position pos, sf::Color color) {
    sf::RectangleShape rect(sf::Vector2f(SIZE, SIZE));

    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(color);
    rect.setOutlineThickness(-4.0f);

    rect.setPosition(pos.x * SIZE, pos.y * SIZE);

    window.draw(rect);
}


// CONTROLLER

void Window::update() {
    // Event processing
    sf::Event event;
    while (window.pollEvent(event)) {
        // Request for closing the window
        switch(event.type) {
        case sf::Event::MouseButtonPressed:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Position board_position = mouse_position();

                if(chess.board.in_bounds(board_position)) {
                    if(first_selected.x == -1 && first_selected.y == -1) {

                        // Set first position if it is unset
                        first_selected = board_position;

                    } else if(board_position.x != first_selected.x || board_position.y != second_selected.y) {

                        // Set second position if selected is not the same as first
                        second_selected = board_position;

                        // Make move and reset positions
                        chess.board.move_piece(first_selected, second_selected);

                        first_selected = Position(-1, -1);
                        second_selected = Position(-1, -1);
                    }
                }
            }
            break;

        case sf::Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }
}

Position Window::mouse_position() {
    sf::Vector2i window_position = sf::Mouse::getPosition(window);
    Position board_position(window_position.x / SIZE, window_position.y / SIZE);
    return board_position;
}

