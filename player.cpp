#include <iostream>
#include "player.h"

//set up player
Player::Player(int player_number)
{
    player_id = player_number;
    total_rolls = 0;
    player_position[0] = 0;
    player_position[1] = 0;
}

//Return a dice roll
int Player::roll_dice()
{
    int roll = rand() % 6;

    return roll + 1;
}

//Return Players ID
int Player::get_id()
{
    return player_id;
}

//Get the number of rolls on current turn
int Player::get_rolls()
{
    return total_rolls;
}

//Set both array and display position of player
void Player::set_position(int array_pos,int display_pos)
{
    player_position[0] = array_pos;
    player_position[1] = display_pos;
}

//Get only the array position of player
int Player::get_array_position()
{
    return player_position[0];
}

//Get only the display position of player
int Player::get_display_position()
{
    return player_position[1];
}

//Set only the display position of player
void Player::set_display_position(int position)
{
    player_position[1] = position;
}
