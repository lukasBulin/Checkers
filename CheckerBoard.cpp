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

SChecker CCheckerBoard::GetCheckerAt(int row, int col) const
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	return board[row][col].color;
}

void SetCheckerAt(int row, int col, const SChecker& checker)
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);

}

ECheckerColor CCheckerBoard::GetColorAt(int row, int col) const
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	return board[row][col].color;
}

void CCheckerBoard::SetColorAt(int row, int col, ECheckerColor color)
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	board[row][col].color = color;
}

ECheckerType CCheckerBoard::GetTypeAt(int row, int col) const
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	return board[row][col].type;
}

void CCheckerBoard::SetTypeAt(int row, int col, ECheckerType type)
{
	assert(row >= 0 && col >= 0 && row < boardSize && col < boardSize);
	board[row][col].type = type;
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
	// pawn rules
	if (nextMove.checkerType == ECheckerType::pawn)
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
			else if (nextMove.endCol == nextMove.startCol - 2 && board[nextMove.startRow + 1][nextMove.startCol - 1].color == ECheckerColor::black)
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

		// Cannot land on enemy piece; must land beyond it
		if (foundOpponent)
		{
			// The landing square must be empty
			if (board[nextMove.endRow][nextMove.endCol].color != ECheckerColor::noColor)
				return false;

			nextMove.rowToDelete = opponentRow;
			nextMove.colToDelete = opponentCol;
		}
		else
		{
			// Not a capture: landing square must be empty
			if (board[nextMove.endRow][nextMove.endCol].color != ECheckerColor::noColor)
				return false;
		}
	}

	return true;
}

void CCheckerBoard::MoveChecker(const SNextMove& nextMove)
{
	ECheckerColor checkerColor = GetColorAt(nextMove.startRow, nextMove.startCol);
	ECheckerType checkerType = GetTypeAt(nextMove.startRow, nextMove.startCol);

	// move piece at new spot
	SetColorAt(nextMove.endRow, nextMove.endCol, checkerColor);
	SetTypeAt(nextMove.endRow, nextMove.endCol, checkerType);

	// clear old spot
	SetColorAt(nextMove.startRow, nextMove.startCol, ECheckerColor::noColor);
	SetTypeAt(nextMove.startRow, nextMove.startCol, ECheckerType::noType);

	// delete captured piece (color and type)
	if (nextMove.rowToDelete != SNextMove::invalidCoordinate && nextMove.colToDelete != SNextMove::invalidCoordinate)
	{
		SetColorAt(nextMove.rowToDelete, nextMove.colToDelete, ECheckerColor::noColor);
		SetTypeAt(nextMove.rowToDelete, nextMove.colToDelete, ECheckerType::noType);
	}

	// make a PROMOTION if there is one to be made
	if (checkerType == ECheckerType::pawn)
	{
		// red pawn reaches top (row 7)
		if (checkerColor == ECheckerColor::red && checkerType == ECheckerType::pawn && nextMove.endRow == boardSize - 1)
		{
			SChecker temp(ECheckerColor::red, ECheckerType::queen);
			SetCheckerAt(nextMove.endRow, nextMove.endCol, temp);
		}

		// black pawn reaches bottom (row 0)
		if (checkerColor == ECheckerColor::black && checkerType == ECheckerType::pawn && nextMove.endRow == 0)
		{
			SChecker temp(ECheckerColor::black, ECheckerType::queen);
			SetCheckerAt(nextMove.endRow, nextMove.endCol, temp);
		}
	}
}

bool CCheckerBoard::IsValidPosition(int row, int col, ECheckerColor playerSide) const
{
	return row >= 0 && row < GetBoardSize() && col >= 0 && col < GetBoardSize() && playerSide == GetColorAt(row, col);
}