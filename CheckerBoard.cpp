#include "CheckerBoard.h"
#include "PlayerInput.h"

#include <iostream>
#include <assert.h>
using namespace std;

CCheckerBoard::CCheckerBoard() 
{
	for (int row = 0; row < boardSize; row++)
	{
		for (int col = 0; col < boardSize; col++)
		{
			board[row][col] = ECheckerColor::none;
		}
	}
}

int CCheckerBoard::GetBoardSize() const
{
	return boardSize;
}

ECheckerColor CCheckerBoard::GetValueAt(int row, int col) const
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	return board[row][col];
}

void CCheckerBoard::SetValueAt(int row, int col, ECheckerColor value)
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
			// white checkers (o), even row
			if ((row <= 2) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col] = ECheckerColor::red;
			}
			// white checkers (o), odd row
			else if ((row <= 2) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col] = ECheckerColor::red;
			}

			// black checkers (x), even row
			if ((row >= 5 && row <= 7) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col] = ECheckerColor::black;
			}
			// black checkers (x), odd row
			else if ((row >= 5 && row <= 7) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col] = ECheckerColor::black;
			}
		}
	}
}

bool CCheckerBoard::ValidateMove(SNextMove& nextMove) const
{
	// starting cordinates are not on a checker
	if (board[nextMove.startRow][nextMove.startCol] != nextMove.checkerType)
	{
		return false;
	}

	// ending cordinates are not on an open tile
	if (board[nextMove.endRow][nextMove.endCol] != ECheckerColor::none)
	{
		return false;
	}

	// even row, odd col
	if (nextMove.endRow % 2 == 0 && nextMove.endCol % 2 == 1)
	{
		return false;
	}

	// odd row, even col
	if (nextMove.endRow % 2 == 1 && nextMove.endCol % 2 == 0)
	{
		return false;
	}

	// white takes black
	if (nextMove.checkerType == ECheckerColor::red && nextMove.endRow == nextMove.startRow + 2)
	{
		if (nextMove.endCol == nextMove.startCol + 2 && board[nextMove.startRow + 1][nextMove.startCol + 1] == ECheckerColor::black)
		{
			nextMove.rowToDelete = nextMove.startRow + 1;
			nextMove.colToDelete = nextMove.startCol + 1;
			return true;
		}
		else if	(nextMove.endCol == nextMove.startCol - 2 && board[nextMove.startRow + 1][nextMove.startCol - 1] == ECheckerColor::black)
		{
			nextMove.rowToDelete = nextMove.startRow + 1;
			nextMove.colToDelete = nextMove.startCol - 1;
			return true;
		}

		return false;
	}

	// black takes white
	if (nextMove.checkerType == ECheckerColor::black && nextMove.endRow == nextMove.startRow - 2)
	{
		if (nextMove.endCol == nextMove.startCol + 2 && board[nextMove.startRow - 1][nextMove.startCol + 1] == ECheckerColor::red)
		{
			nextMove.rowToDelete = nextMove.startRow - 1;
			nextMove.colToDelete = nextMove.startCol + 1;
			return true;
		}
		else if (nextMove.endCol == nextMove.startCol - 2 && board[nextMove.startRow - 1][nextMove.startCol - 1] == ECheckerColor::red)
		{
			nextMove.rowToDelete = nextMove.startRow - 1;
			nextMove.colToDelete = nextMove.startCol - 1;
			return true;
		}

		return false;
	}

	// white checker, row change by +1
	if ((nextMove.checkerType == ECheckerColor::red) && (nextMove.endRow - nextMove.startRow != 1))
	{
		return false;
	}

	// black checker, row change by -1
	if ((nextMove.checkerType == ECheckerColor::black) && (nextMove.endRow - nextMove.startRow != -1))
	{
		return false;
	}

	// white/black checker, col change by 1 or -1
	if (nextMove.endCol - nextMove.startCol != -1 && nextMove.endCol - nextMove.startCol != 1)
	{
		return false;
	}

	return true;
}

void CCheckerBoard::MoveChecker(const SNextMove& nextMove)
{
	ECheckerColor checkerType = GetValueAt(nextMove.startRow, nextMove.startCol);

	SetValueAt(nextMove.endRow, nextMove.endCol, checkerType);

	SetValueAt(nextMove.startRow, nextMove.startCol, ECheckerColor::none);

	if (nextMove.rowToDelete != SNextMove::invalidCoordinate && nextMove.colToDelete != SNextMove::invalidCoordinate)
	{
		SetValueAt(nextMove.rowToDelete, nextMove.colToDelete, ECheckerColor::none);
	}
}

bool CCheckerBoard::IsValidPosition(int row, int col, ECheckerColor playerSide) const
{
	return row >= 0 && row < GetBoardSize() && col >= 0 && col < GetBoardSize() && playerSide == GetValueAt(row, col);
}