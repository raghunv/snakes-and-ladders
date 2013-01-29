#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Player
{
    public:

    void set_position(int array_pos, int display_pos);
    void set_display_position(int position);
    int get_display_position();
    int get_array_position();
    int roll_dice();
    int get_rolls();
    int get_id();

    Player(int player_number);

    protected:
    int total_rolls;
    int player_position[2];
    int player_id;

};

#endif
