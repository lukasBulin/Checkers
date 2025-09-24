#include "CheckerBoard.h"

#include <assert.h>

CCheckerBoard::CCheckerBoard() 
{
	for (int row = 0; row < boardSize; row++)
	{
		for (int col = 0; col < boardSize; col++)
		{
			board[row][col] = ECheckerType::none;
		}
	}
}

int CCheckerBoard::GetBoardSize() const
{
	return boardSize;
}

ECheckerType CCheckerBoard::GetValueAt(int row, int col) const
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	return board[row][col];
}

void CCheckerBoard::SetValueAt(int row, int col, ECheckerType value)
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	
	board[row][col] = value;
}

void CCheckerBoard::ResetBoard()
{
	for (int row = 0; row < boardSize; row++)
	{
		for (int col = 0; col < boardSize; col++)
		{
			//white checkers (o), even row
			if ((row <= 2) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col] = ECheckerType::white;
			}
			//white checkers (o), odd row
			else if ((row <= 2) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col] = ECheckerType::white;
			}

			//black checkers (x), even row
			if ((row >= 5 && row <= 7) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col] = ECheckerType::black;
			}
			//black checkers (x), odd row
			else if ((row >= 5 && row <= 7) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col] = ECheckerType::black;
			}
		}
	}
}