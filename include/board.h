#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <array>
#include <vector>

#include "position.h"
#include "piece.h"
#include "side.h"

class Board {
    public:
        Board();
        ~Board();

        void reload();
        void print();

        Piece get_piece(Position pos);
        void set_piece(Position pos, Piece piece);
        bool move_piece(Position origin, Position destination);
        bool in_bounds(Position pos);

        std::vector<Position> get_moves(Position from);

    protected:

    private:
        std::array<std::array<Piece, 8>, 8> squares;


        Side get_side(Piece piece);
        bool is_opposing(Piece p1, Piece p2);

};

#endif // BOARD_H
