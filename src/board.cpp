#include "board.h"

Board::Board() {
    // Load starting board
    reload();
}

Board::~Board() {}

void Board::reload() {
    //  Init squares
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            set_piece(Position(x, y), none);
        }
    }

    // Add pawns
    for(int x = 0; x < 8; x++) {
        set_piece(Position(x, 6), white_pawn);
        set_piece(Position(x, 1), black_pawn);
    }

    // Add other pieces
    set_piece(Position(0, 7), white_rook);
    set_piece(Position(1, 7), white_knight);
    set_piece(Position(2, 7), white_bishop);
    set_piece(Position(3, 7), white_queen);
    set_piece(Position(4, 7), white_king);
    set_piece(Position(5, 7), white_bishop);
    set_piece(Position(6, 7), white_knight);
    set_piece(Position(7, 7), white_rook);

    set_piece(Position(0, 0), black_rook);
    set_piece(Position(1, 0), black_knight);
    set_piece(Position(2, 0), black_bishop);
    set_piece(Position(3, 0), black_queen);
    set_piece(Position(4, 0), black_king);
    set_piece(Position(5, 0), black_bishop);
    set_piece(Position(6, 0), black_knight);
    set_piece(Position(7, 0), black_rook);
}

void Board::print() {
    for(int y = 0; y < 8; y++) {
        std::cout << std::endl;
        for(int x = 0; x < 8; x++) {
            switch(get_piece(Position(x, y))) {
            case white_pawn:
                std::cout << "[wPn]";
                break;
            case white_rook:
                std::cout << "[wRk]";
                break;
            case white_knight:
                std::cout << "[wKt]";
                break;
            case white_bishop:
                std::cout << "[wBp]";
                break;
            case white_queen:
                std::cout << "[wQn]";
                break;
            case white_king:
                std::cout << "[wKg]";
                break;
            case black_pawn:
                std::cout << "[bPn]";
                break;
            case black_rook:
                std::cout << "[bRk]";
                break;
            case black_knight:
                std::cout << "[bKt]";
                break;
            case black_bishop:
                std::cout << "[bBp]";
                break;
            case black_queen:
                std::cout << "[bQn]";
                break;
            case black_king:
                std::cout << "[bKg]";
                break;
            default:
                std::cout << "[...]";
                break;
            }
        }
    }
}


bool Board::in_bounds(Position pos) {
    return (0 <= pos.x && pos.x < 8 && 0 <= pos.y && pos.y < 8);
}

Piece Board::get_piece(Position pos) {
    if(!in_bounds(pos)) {
        return outside;
    } else {
        return squares[pos.y][pos.x];
    }
}

void Board::set_piece(Position pos, Piece piece) {
    if(in_bounds(pos)) {
        squares[pos.y][pos.x] = piece;
    }
}

bool Board::move_piece(Position origin, Position destination) {
    // Try to move piece. Return true if move was successful
    std::vector<Position> available = get_moves(origin);
    for(Position p : available) {
        if(destination.x == p.x && destination.y == p.y) {
            // Wanted destination is an allowed move
            set_piece(destination, get_piece(origin));
            set_piece(origin, none);
            return true;
        }
    }
    return false;
}

Side Board::get_side(Piece piece) {
    if(piece <= 0)
        return Side::neutral;
    if(piece <= 6)
        return Side::white;
    else
        return Side::black;
}

bool Board::is_opposing(Piece p1, Piece p2) {
    if(get_side(p1) == Side::neutral || get_side(p2) == Side::neutral) {
        return false;
    } else {
        return get_side(p1) != get_side(p2);
    }
}

std::vector<Position> Board::get_moves(Position from) {
    std::vector<Position> moves;
    switch(get_piece(from)) {

    case white_pawn:
    case black_pawn: {

        int direction = (get_piece(from) == white_pawn) ? -1 : 1;

        // Check if position in front of pawn is free
        if(get_piece(Position(from.x, from.y + direction)) == none) {
            // Pawn can move one step forward
            moves.push_back(Position(from.x, from.y + direction));
            // Check if pawn can move two steps
            int start_row = (get_piece(from) == white_pawn) ? 6 : 1;

            if(from.y == start_row && get_piece(Position(from.x, from.y + direction*2)) == none) {
                moves.push_back(Position(from.x, from.y + direction*2));
            }
        }
        // Check for diagonal moves (attacks)
        if(is_opposing(get_piece(from), get_piece(Position(from.x - 1, from.y + direction)))) {
            // Diagonal left is black, can move here
            moves.push_back(Position(from.x - 1, from.y + direction));
        }
        if(is_opposing(get_piece(from), get_piece(Position(from.x + 1, from.y + direction)))) {
            // Diagonal right is black, can move here
            moves.push_back(Position(from.x + 1, from.y + direction));
        }

    } break;

    case white_rook:
    case black_rook: {

        // Check all straight directions
        // Left, up, right, down
        int x_offset[4] = {-1, 0, 1, 0};
        int y_offset[4] = {0, -1, 0, 1};

        for(int dir = 0; dir < 4; dir++) {
            Position check = Position(from.x + x_offset[dir], from.y + y_offset[dir]);

            if(is_opposing(get_piece(from), get_piece(check))) {
                // Next piece is enemy. Add it and stop current direction
                moves.push_back(check);
            }

            while(get_piece(check) == none) {
                moves.push_back(check);

                check.x += x_offset[dir];
                check.y += y_offset[dir];

                if(is_opposing(get_piece(from), get_piece(check))) {
                    // Next piece is enemy. Add it and stop current direction
                    moves.push_back(check);
                    break;
                }
            }
        }

    } break;

    case white_knight:
    case black_knight: {

        // Check all L-shapes
        bool check = false;
        for(int y = -2; y <= 2; y++) {
            for(int x = -2; x <= 2; x++) {
                if(check && (x == -2 || x == 2 || y == -2 || y == 2)) {
                    Position target(from.x + x, from.y + y);
                    if(is_opposing(get_piece(from), get_piece(target)) || get_piece(target) == none) {
                        moves.push_back(target);
                    }
                }
                check = !check;
            }
        }

    } break;

    case white_bishop:
    case black_bishop: {

        // Check all diagonals
        // Top-left, top-right, bottom-right, bottom-left
        int x_offset[4] = {-1, 1, 1, -1};
        int y_offset[4] = {-1, -1, 1, 1};

        for(int dir = 0; dir < 4; dir++) {
            Position check = Position(from.x + x_offset[dir], from.y + y_offset[dir]);

            if(is_opposing(get_piece(from), get_piece(check))) {
                // Next piece is enemy. Add it and stop current direction
                moves.push_back(check);
            }

            while(get_piece(check) == none) {
                moves.push_back(check);

                check.x += x_offset[dir];
                check.y += y_offset[dir];

                if(is_opposing(get_piece(from), get_piece(check))) {
                    // Next piece is enemy. Add it and stop current direction
                    moves.push_back(check);
                    break;
                }
            }
        }

    } break;

    case white_queen:
    case black_queen: {

        // Check all straights and diagonals
        // Left, top-left, top, top-right, right, bottom-right, bottom, bottom-left
        int x_offset[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
        int y_offset[8] = {0, -1, -1, -1, 0, 1, 1, 1};

        for(int dir = 0; dir < 8; dir++) {
            Position check = Position(from.x + x_offset[dir], from.y + y_offset[dir]);

            if(is_opposing(get_piece(from), get_piece(check))) {
                // Next piece is enemy. Add it and stop current direction
                moves.push_back(check);
            }

            while(get_piece(check) == none) {
                moves.push_back(check);

                check.x += x_offset[dir];
                check.y += y_offset[dir];

                if(is_opposing(get_piece(from), get_piece(check))) {
                    // Next piece is enemy. Add it and stop current direction
                    moves.push_back(check);
                    break;
                }
            }
        }

    } break;

    case white_king:
    case black_king: {

        // Check all straights and diagonals, one step
        // Left, top-left, top, top-right, right, bottom-right, bottom, bottom-left
        int x_offset[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
        int y_offset[8] = {0, -1, -1, -1, 0, 1, 1, 1};

        for(int dir = 0; dir < 8; dir++) {
            Position check = Position(from.x + x_offset[dir], from.y + y_offset[dir]);
            if(get_piece(check) == none || is_opposing(get_piece(from), get_piece(check))) {
                // Square is either empty or contains enemy. Position is allowed.
                moves.push_back(check);
            }
        }

    } break;

    default:
        break;
    }
    return moves;
}
