#ifndef BOARD_H
#define BOARD_h
#include "player.h"

class Board
{
    public:
        void print_board();
        void reset_board();
        void update_board(Player& player_moving, Player& player_idle);

        Board();

    protected:
        int board[100][4];
};

#endif
