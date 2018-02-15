#ifndef CHESS_H
#define CHESS_H

#include "board.h"

/* The Chess class handles rendering and communication between player and board */

class Chess
{
    public:
        Chess();
        ~Chess();

        Board board;
    protected:

    private:
};

#endif // CHESS_H
