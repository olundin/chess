#ifndef PIECE_H
#define PIECE_H

enum Piece {
    outside = -1,
    none = 0,

    white_pawn = 1,
    white_rook = 2,
    white_knight = 3,
    white_bishop = 4,
    white_queen = 5,
    white_king = 6,

    black_pawn = 7,
    black_rook = 8,
    black_knight = 9,
    black_bishop = 10,
    black_queen = 11,
    black_king = 12
};

#endif // PIECE_H
