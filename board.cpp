#include <windows.h>
#include <iostream>
#include "board.h"

using namespace std;

//returns the current attributes for color handling
WORD GetConsoleTextAttribute (HANDLE hCon)
{
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    GetConsoleScreenBufferInfo(hCon, &con_info);
    return con_info.wAttributes;
}

//text color code
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int saved_colors = GetConsoleTextAttribute(hConsole);

Board::Board()
{
    reset_board();
}

//--Restore the board to dafault values --//
void Board::reset_board()
{
    //----> {Array Position, Board Display, Ladder111-Snake222, Jump (To ARRAY POSITION) } <-----//
    board=
    {
        {0,100,0,0},{1,99,0,0}, {2,98,0,0}, {3,97,0,0}, {4,96,0,0}, {5,95,333,36}, {6,94,0,0}, {7,93,0,0}, {8,92,0,0}, {9,91,0,0},
        {10,81,0,0},{11,82,111,0},{12,83,0,0},{13,84,0,0},{14,85,0,0},{15,86,0,0},{16,87,333,0},{17,88,0,0},{18,89,0,0},{19,90,0,0},
        {20,80,0,0},{21,79,0,0},{22,78,111,0},{23,77,0,0},{24,76,0,0},{25,75,333,0},{26,74,0,0},{27,73,0,0},{28,72,0,0},{29,71,111,0},
        {30,61,0,0},{31,62,0,0},{32,63,0,0},{33,64,111,0},{34,65,0,0},{35,66,0,0},{36,67,333,0},{37,68,0,0},{38,69,111,0},{39,70,0,0},
        {40,60,0,0},{41,59,0,0},{42,58,0,0},{43,57,0,0},{44,56,111,11},{45,55,0,0},{46,54,0,0},{47,53,111,29},{48,52,0,0},{49,51,0,0},
        {50,41,0,0},{51,42,333,91},{52,43,0,0},{53,44,0,0},{54,45,0,0},{55,46,0,0},{56,47,0,0},{57,48,0,0},{58,49,0,0},{59,50,0,0},
        {60,40,0,0},{61,39,0,0},{62,38,333,0},{63,37,0,0},{64,36,0,0},{65,35,0,0},{66,34,333,97},{67,33,0,0},{68,32,0,0},{69,31,111,0},
        {70,21,0,0},{71,22,333,0},{72,23,111,0},{73,24,0,0},{74,25,0,0},{75,26,111,0},{76,27,0,0},{77,28,333,0},{78,29,111,0},{79,30,0,0},
        {80,20,0,0},{81,19,111,0},{82,18,333,0},{83,17,0,0},{84,16,111,0},{85,15,0,0},{86,14,0,0},{87,13,111,0},{88,12,333,0},{89,11,0,0},
        {90,1,111,72}, {91,2,333,0}, {92,3,0,0}, {93,4,111,75}, {94,5,0,0}, {95,6,0,0}, {96,7,111,69}, {97,8,333,0}, {98,9,0,0}, {99,10,0,0}
    };
}

//--- Display the board - including player, ladder, and snake positions --//
void Board::print_board()
{
    for (int i = 0; i < 100; i++)
    {
        if (i % 10 == 0)
        {
            cout << endl;
        }

        if (board[i][2] == 111)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            cout << "[ L  ]";
            SetConsoleTextAttribute(hConsole, 7 );
        }
        else if (board[i][2] == 222)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "[ P1 ]";
            SetConsoleTextAttribute(hConsole, 7 );
        }
        else if (board[i][2] == 333)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "[ S  ]";
            SetConsoleTextAttribute(hConsole, 7 );

        }
        else if (board[i][2] == 444)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "[ P2 ]";
            SetConsoleTextAttribute(hConsole, 7 );
        }
        else
        {
            cout << "[ " << board[i][1];
        }

        if (board[i][1] < 10 && board[i][2] == 0)
        {
            cout << "  ]";
        }
        else if(board[i][1] < 100 && board[i][2] == 0)
        {
            cout << " ]";
        }
        else if (board[i][1] == 100)
        {
            cout << "]";
        }
        cout << " ";
    }
    cout << endl;
}

//--Update the board with the new player position and--//
//--reinsert the non moving player position-----------//
void Board::update_board(Player& player_moving, Player& player_idle)
{

    //Handle the moving Player
    int display_pos = player_moving.get_display_position();

    //Lookup and Update Array Position for player
    int i = 0;

    while (board[i][1] != display_pos && i <= 100)
    {
        i++;
    }
    if (i <= 100)
    {
        player_moving.set_position(board[i][0], board[i][1]);
    }

    int array_pos = player_moving.get_array_position();

    //Check if player hit a snake or ladder
    if (board[array_pos][3] != 0)
    {
        if (board[array_pos][2] == 111)
        {
            cout << "You landed on a ladder!" << endl;
            array_pos = board[array_pos][3];
        }
        else
        {
            cout << "You landed on a snake!" << endl;
            array_pos = board[array_pos][3];
        }
    }

    player_moving.set_position(board[array_pos][0],board[array_pos][1]);

    //Update player position on board
    if (player_moving.get_id() == 1)
    {
        board[array_pos][2] = 222;

        //reinsert idle player position
        array_pos = player_idle.get_array_position();
        board[array_pos][2] = 444;
    }
    else
    {
        board[array_pos][2] = 444;

        //reinsert idle player position
        array_pos = player_idle.get_array_position();
        board[array_pos][2] = 222;
    }
}
