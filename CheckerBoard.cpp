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
			board[row][col].color = ECheckerColor::noColor;
			board[row][col].type = ECheckerType::noType;
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
	return board[row][col].color;
}

void CCheckerBoard::SetValueAt(int row, int col, ECheckerColor value)
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	
	board[row][col].color = value;
}

void CCheckerBoard::ResetBoard()
{
	for (int row = 0; row < boardSize; row++)
	{
		for (int col = 0; col < boardSize; col++)
		{
			board[row][col].color = ECheckerColor::noColor;
			board[row][col].type = ECheckerType::noType;

			// white checkers (o), even row
			if ((row <= 2) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col].color = ECheckerColor::red;
				board[row][col].type = ECheckerType::pawn;
			}
			// white checkers (o), odd row
			else if ((row <= 2) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col].color = ECheckerColor::red;
				board[row][col].type = ECheckerType::pawn;
			}

			// black checkers (x), even row
			if ((row >= 5 && row <= 7) && (row % 2 == 0) && (col % 2 == 0))
			{
				board[row][col].color = ECheckerColor::black;
				board[row][col].type = ECheckerType::pawn;
			}
			// black checkers (x), odd row
			else if ((row >= 5 && row <= 7) && (row % 2 != 0) && (col % 2 != 0))
			{
				board[row][col].color = ECheckerColor::black;
				board[row][col].type = ECheckerType::pawn;
			}
		}
	}
}

bool CCheckerBoard::ValidateMove(SNextMove& nextMove) const
{
	// starting cordinates are not on a checker
	if (board[nextMove.startRow][nextMove.startCol].color != nextMove.checkerColor)
	{
		return false;
	}

	// ending cordinates are not on an open tile
	if (board[nextMove.endRow][nextMove.endCol].color != ECheckerColor::noColor)
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

	// red takes black
	if (nextMove.checkerColor == ECheckerColor::red && nextMove.endRow == nextMove.startRow + 2)
	{
		if (nextMove.endCol == nextMove.startCol + 2 && board[nextMove.startRow + 1][nextMove.startCol + 1].color == ECheckerColor::black)
		{
			nextMove.rowToDelete = nextMove.startRow + 1;
			nextMove.colToDelete = nextMove.startCol + 1;
			return true;
		}
		else if	(nextMove.endCol == nextMove.startCol - 2 && board[nextMove.startRow + 1][nextMove.startCol - 1].color == ECheckerColor::black)
		{
			nextMove.rowToDelete = nextMove.startRow + 1;
			nextMove.colToDelete = nextMove.startCol - 1;
			return true;
		}

		return false;
	}

	// black takes red
	if (nextMove.checkerColor == ECheckerColor::black && nextMove.endRow == nextMove.startRow - 2)
	{
		if (nextMove.endCol == nextMove.startCol + 2 && board[nextMove.startRow - 1][nextMove.startCol + 1].color == ECheckerColor::red)
		{
			nextMove.rowToDelete = nextMove.startRow - 1;
			nextMove.colToDelete = nextMove.startCol + 1;
			return true;
		}
		else if (nextMove.endCol == nextMove.startCol - 2 && board[nextMove.startRow - 1][nextMove.startCol - 1].color == ECheckerColor::red)
		{
			nextMove.rowToDelete = nextMove.startRow - 1;
			nextMove.colToDelete = nextMove.startCol - 1;
			return true;
		}

		return false;
	}

	// red checker, row change by +1
	if ((nextMove.checkerColor == ECheckerColor::red) && (nextMove.endRow - nextMove.startRow != 1))
	{
		return false;
	}

	// black checker, row change by -1
	if ((nextMove.checkerColor == ECheckerColor::black) && (nextMove.endRow - nextMove.startRow != -1))
	{
		return false;
	}

	// red/black checker, col change by 1 or -1
	if (nextMove.endCol - nextMove.startCol != -1 && nextMove.endCol - nextMove.startCol != 1)
	{
		return false;
	}

	// red/black turns to queen
	if (nextMove.checkerType == ECheckerType::pawn)
	{
		if (nextMove.checkerColor == ECheckerColor::red && nextMove.endRow == 7)
		{
			nextMove.checkerType == ECheckerType::queen;
		}

		if (nextMove.checkerColor == ECheckerColor::black && nextMove.endRow == 0)
		{
			nextMove.checkerType == ECheckerType::queen;
		}
	}

	// queen rules
	if (nextMove.checkerType == ECheckerType::queen)
	{
		// queen must move diagonally
		if (std::abs(nextMove.endRow - nextMove.startRow) != std::abs(nextMove.endCol - nextMove.startCol))
		{
			return false;
		}

		// queen must move at least one square
		if ((nextMove.endRow - nextMove.startRow == 0) || (nextMove.endCol - nextMove.startCol == 0))
		{
			return false;
		}

		// is the queen path clear
		int stepThroughRow = (nextMove.endRow - nextMove.startRow) > 0 ? 1 : -1;
		int stepThroughCol = (nextMove.endCol - nextMove.startCol) > 0 ? 1 : -1;
		
		bool foundOpponent = false;
		int opponentRow = 0;
		int opponentCol = 0;

		ECheckerColor currentColor = nextMove.checkerColor;
		ECheckerColor opponentColor = (currentColor == ECheckerColor::red) ? ECheckerColor::black : ECheckerColor::red;

		// Scan path
		int scanRow = nextMove.startRow + stepThroughRow;
		int scanCol = nextMove.startCol + stepThroughCol;
		while (scanRow != nextMove.endRow || scanCol != nextMove.endCol)
		{
			if (board[scanRow][scanCol].color != ECheckerColor::noColor)
			{
				// Blocked by own piece
				if (board[scanRow][scanCol].color == currentColor)
				{
					return false;
				}

				// Opponent piece
				if (board[scanRow][scanCol].color == opponentColor)
				{
					if (foundOpponent)
					{
						return false; // More than one piece in path
					}
					foundOpponent = true;
					opponentRow = scanRow;
					opponentCol = scanCol;
				}
			}
			scanRow += stepThroughRow;
			scanCol += stepThroughCol;
		}

		// If capture is intended, ensure exactly one opponent piece was found
		if (foundOpponent)
		{
			nextMove.rowToDelete = opponentRow;
			nextMove.colToDelete = opponentCol;
		}

		// If no invalid conditions triggered, it's valid
		return true;
	}

	return true;
}

void CCheckerBoard::MoveChecker(const SNextMove& nextMove)
{
	ECheckerColor checkerColor = GetValueAt(nextMove.startRow, nextMove.startCol);

	SetValueAt(nextMove.endRow, nextMove.endCol, checkerColor);

	SetValueAt(nextMove.startRow, nextMove.startCol, ECheckerColor::noColor);

	if (nextMove.rowToDelete != SNextMove::invalidCoordinate && nextMove.colToDelete != SNextMove::invalidCoordinate)
	{
		SetValueAt(nextMove.rowToDelete, nextMove.colToDelete, ECheckerColor::noColor);
	}
}

bool CCheckerBoard::IsValidPosition(int row, int col, ECheckerColor playerSide) const
{
	return row >= 0 && row < GetBoardSize() && col >= 0 && col < GetBoardSize() && playerSide == GetValueAt(row, col);
}