#include "CheckerBoard.h"
#include <iostream>
#include <assert.h>
using namespace std;

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
			// white checkers (o), even row
			if ((row <= 2) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col] = ECheckerType::white;
			}
			// white checkers (o), odd row
			else if ((row <= 2) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col] = ECheckerType::white;
			}

			// black checkers (x), even row
			if ((row >= 5 && row <= 7) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col] = ECheckerType::black;
			}
			// black checkers (x), odd row
			else if ((row >= 5 && row <= 7) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col] = ECheckerType::black;
			}
		}
	}
}

bool CCheckerBoard::IsValidMove(int startRow, int startCol, int endRow, int endCol, ECheckerType checkerType) const
{
	// starting cordinates are not on a checker
	if (board[startRow][startCol] != checkerType)
	{
		return false;
	}

	// ending cordinates are not on an open tile
	if (board[endRow][endCol] != ECheckerType::none)
	{
		return false;
	}

	// even row, odd col
	if (endRow % 2 == 0 && endCol % 2 == 1)
	{
		return false;
	}

	// odd row, even col
	if (endRow % 2 == 1 && endCol % 2 == 0)
	{
		return false;
	}

	// white takes black
	if (checkerType == ECheckerType::white && endRow == startRow + 2)
	{
		if ((endCol == startCol + 2 && board[startRow + 1][startCol + 1] == ECheckerType::black) ||
			(endCol == startCol - 2 && board[startRow + 1][startCol - 1] == ECheckerType::black))
		{
			return true;
		}

		return false;
	}

	// black takes white
	if (checkerType == ECheckerType::black && endRow == startRow - 2)
	{
		if ((endCol == startCol + 2 && board[startRow - 1][startCol + 1] == ECheckerType::white) ||
			(endCol == startCol - 2 && board[startRow - 1][startCol - 1] == ECheckerType::white))
		{
			return true;
		}

		return false;
	}

	// white checker, row change by +1
	if ((checkerType == ECheckerType::white) && (endRow - startRow != 1))
	{
		return false;
	}

	// black checker, row change by -1
	if ((checkerType == ECheckerType::black) && (endRow - startRow != -1))
	{
		return false;
	}

	// white/black checker, col change by 1 or -1
	if (endCol - startCol != -1 && endCol - startCol != 1)
	{
		return false;
	}

	return true;
}

void CCheckerBoard::MoveChecker(int startRow, int startCol, int endRow, int endCol)
{
	ECheckerType checkerType = GetValueAt(startRow, startCol);

	SetValueAt(endRow, endCol, checkerType);

	SetValueAt(startRow, startCol, ECheckerType::none);
}