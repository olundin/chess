#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "chess.h"
#include "window.h"

int main(int argc, char* argcv[]) {

    Chess chess;
    Window window(chess);

    chess.board.print();

    while(window.is_open()) {
        window.update();
        window.draw();
    }
}
