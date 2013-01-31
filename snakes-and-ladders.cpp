/*****************************************************************
* Snakes and Ladders in C++ with a 10x10 board                   *
* by Sam Nunnery                                                 *
* Math 410 - intro project                                       *
* Tested on Windows 7 64 bit using Codeblocks                    *
* Uses a WINDOWS header for handling color                       *
* Last Updated: 1/29/2013                                        *
******************************************************************/

#include <iostream>

#include <string>
#include "board.h"
#include "player.h"


using namespace std;

int main()
{
    bool running = true;  //Game ending bool
    int dice_roll;  //Take input for rolls
    int player_turn = 1; //Control whos turn it is

    //set random seed
    srand(time(NULL));

    //Load game objects
    Board game_board;
    Player p1(1);
    Player p2(2);

    //Show start screen and rules
    cout << "Welcome to Snakes and Ladders" << endl;
    cout << endl << "Rules: " << endl;
    cout << endl << "Roll the dice and advance position on the board. " << endl;
    cout << endl << "If a player rolls a 6, they get to roll again. " << endl;
    cout << endl << "If a player rolls 3 6's in a row, they are moved back to the beginning of the board. " << endl;
    cout << endl << "If a player lands on the bottom of a ladder [ L ], they are transported to the top of it. " << endl;
    cout << endl << "If a player lands on the top of a snake [ S ], they are transported to the bottom of it. " << endl;
    cout << endl << "Once a player reaches tile 100, the game is over. " << endl;
    cout << endl << "You do not have to roll the exact amount to land on 100 in this version." << endl;
    cout << endl << "Enter 1 to start the game" << endl;
    cin >> dice_roll;

    //Clear Screen
    system("CLS");

    //Start Game - Run while there is no winner
    while (running)
    {

        //Show board
        game_board.print_board();

        //Reset the board to default config
        game_board.reset_board();

        //Take input to start roll
        if (player_turn == 1)
        {
            cout << endl << "Player 1's turn: ";
        }
        else
        {
            cout << "Player 2's turn: ";
        }

        cout << "Enter 1 to roll the dice" << endl;
        cin >> dice_roll;

        //Clear Screen
        system("CLS");

        //Get the dice roll
        if (player_turn == 1)
        {
            dice_roll = p1.roll_dice();

            //Find players position
            p1.set_display_position(p1.get_display_position() + dice_roll);

            //Update the board..players new position..other player position
            game_board.update_board(p1,p2);

            //Alert player of current results
            cout << "You rolled " << dice_roll << " and moved to " << p1.get_display_position() << endl;

            //Switch turns unless a 6 was rolled
            if (dice_roll == 6)
            {
                //check if user has rolled 3 6's in a row
                if (p1.get_rolls() < 3)
                {
                    cout << "Since you rolled a 6, you get to go again!" << endl;
                }
            }
            else
            {
                player_turn = 2;
            }

        }
        else
        {
            dice_roll = p2.roll_dice();

            //Find players position
            p2.set_display_position(p2.get_display_position() + dice_roll);

            //Update the board..players new position..other player position
            game_board.update_board(p2,p1);

            //Alert player of current results
            cout << "You rolled " << dice_roll << " and moved to " << p2.get_display_position() << endl;

            //Switch turns unless a 6 was rolled
            if (dice_roll == 6)
            {
                //check if user has rolled 3 6's in a row
                if (p2.get_rolls() < 3)
                {
                    cout << "Since you rolled a 6, you get to go again!" << endl;
                }
            }
            else
            {
                player_turn = 1;
            }
        }

        //Check winning conditions, proceed if no winner
        if (p1.get_display_position() >= 100)
        {
            running = false;

            cout << "Player One wins " << endl;
        }
        else if (p2.get_display_position() >= 100)
        {
            running = false;

            cout << "Player Two wins " << endl;
        }
    }

    return 0;
}
