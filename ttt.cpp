#include <iostream>
using namespace std;

char board[3][3]{{'1','2','3'},{'4','5','6'},{'7','8','9'}};
int row;
int column;
char player = 'X';
bool tie = false;

void printboard();
void playmove();
bool wincheck();

int main()
{
    while(!wincheck())
    {
        printboard();
        playmove();
        wincheck();
    }
    //umm reverse logic cuz i switch players after placing
    if(player == 'O' && tie == false)
    {
        cout << "Player X wins!\n";
        exit(0);
    }
    if(player == 'X' && tie == false)
    {
        cout << "player O wins!\n";
        exit(0);
    }
    else
    {
        cout << "Its a draw!";
        exit(0);
    }
}

void printboard()
{
    cout << endl << endl;
    cout << "    |     |    \n";
    cout << "  "<<board[0][0]<<" |  "<<board[0][1]<<"  | "<<board[0][2]<<" \n";
    cout << "____|_____|____\n";
    cout << "    |     |    \n";
    cout << "  "<<board[1][0]<<" |  "<<board[1][1]<<"  | "<<board[1][2]<<" \n";
    cout << "____|_____|____\n";
    cout << "    |     |    \n";
    cout << "  "<<board[2][0]<<" |  "<<board[2][1]<<"  | "<<board[2][2]<<" \n";
    cout << "    |     |    \n";
}

void playmove()
{
    int move;

    if (player == 'X')
    {
        cout << "Make your move player " << player << endl;
        cin >> move;
    }
    if (player == 'O')
    {
        cout << "Make your move player " << player << endl;
        cin >> move;
    }
    //surely theres a better way to do this right?
    if (move == 1)
    {
        row=0;
        column=0;
    }
    if (move == 2)
    {
        row=0;
        column=1;
    }
    if (move == 3)
    {
        row=0;
        column=2;
    }
    if (move == 4)
    {
        row=1;
        column=0;
    }
    if (move == 5)
    {
        row=1;
        column=1;
    }
    if (move == 6)
    {
        row=1;
        column=2;
    }
    if (move == 7)
    {
        row=2;
        column=0;
    }
    if (move == 8)
    {
        row=2;
        column=1;
    }
    if (move == 9)
    {
        row=2;
        column=2;
    }
    if(move<1 || move>9)
    {
        cout << "dawg what";
    }

    if(player == 'X' && board[row][column] != 'X' && board[row][column] != 'O')
    {
        board[row][column] = 'X';
        player = 'O';
    }
    else if(player == 'O' && board[row][column] != 'X' && board[row][column] != 'O')
    {
        board[row][column] = 'O';
        player = 'X';
    }
    else
    {
        cout << "Not a valid space ! \n";
        //wincheck();
        playmove();
    }
    printboard();
    
}

bool wincheck()
{
    //okay something wrong here cuz this code never actually reaches the end, where tie is set to true
    //nvm im dumb i was setting false at the end lol

    //straights
    for(int i = 0;i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return true;
        }
    }
    //diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] || board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return true;
    }
    //if game not end

    for(int i = 0;i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O')
            {
                //game still going cuz there are spaces with x or o
                return false;
            }
        }
    }
    tie = true;
    return true;
    
}