#include <iostream>
using namespace std;

int main()
{
    char board[3][3]{{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    int row;
    int column;
    char player = 'X';
    bool tie = false;

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