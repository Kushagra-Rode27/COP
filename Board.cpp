// Board.cpp
// Board class member-functions definition.
//
// Author: yat0 - https://github.com/yat0

#include "Board.h"

Board::Board() { restart(); }

// clear the game board
void Board::restart()
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i][j] = PIECE_EMPTY;

    occupiedPlaces = 0;
}

// check for win conditions
bool Board::hasWinner() const
{
    return (checkRows() || checkColumns() || checkDiagonals());
}

bool Board::isDraw() const
{
    return occupiedPlaces == 9;
}

// place a piece (human/pc) at (x,y) spot in the board
void Board::place(int row, int col, bool humanPiece)
{
    if(row>=0 && row<3 && col>=0 && col<3 && occupiedPlaces<9)
    {
        m[row][col] = humanPiece ? PIECE_X : PIECE_O;
        occupiedPlaces++;
    }
}

// return whether the (x,y) spot is empty
bool Board::isFieldEmpty(int row, int col) const
{
    if(row>=0 && row<3 && col>=0 && col<3)
        return m[row][col] == PIECE_EMPTY;

    return false;
}

// return whether the (x,y) spot is filled with piece X
bool Board::isFieldCross(int row, int col) const
{
    if(row>=0 && row<3 && col>=0 && col<3)
        return m[row][col] == PIECE_X;

    return false;
}

// return whether the (x,y) spot is filled with piece O
bool Board::isFieldCircle(int row, int col) const
{
    if(row>=0 && row<3 && col>=0 && col<3)
        return m[row][col] == PIECE_O;

    return false;
}

// render player piece

// check row win conditions
bool Board::checkRows() const
{
    if(m[0][0] == m[0][1] && m[0][1] == m[0][2] && !isFieldEmpty(0,2))
        return true;
    else if(m[1][0] == m[1][1] && m[1][1] == m[1][2] && !isFieldEmpty(1,2))
        return true;
    else if(m[2][0] == m[2][1] && m[2][1] == m[2][2] && !isFieldEmpty(2,2))
        return true;

    return false;
}

// check column win conditions
bool Board::checkColumns() const
{
    if(m[0][0] == m[1][0] && m[1][0] == m[2][0] && !isFieldEmpty(2,0))
        return true;
    else if(m[0][1] == m[1][1] && m[1][1] == m[2][1] && !isFieldEmpty(2,1))
        return true;
    else if(m[0][2] == m[1][2] && m[1][2] == m[2][2] && !isFieldEmpty(2,2))
        return true;

    return false;
}

// check diagonal win conditions
bool Board::checkDiagonals() const
{
    if(m[0][0] == m[1][1] && m[1][1] == m[2][2] && !isFieldEmpty(2,2))
        return true;
    else if(m[0][2] == m[1][1] && m[1][1] == m[2][0] && !isFieldEmpty(2,0))
        return true;

    return false;
}