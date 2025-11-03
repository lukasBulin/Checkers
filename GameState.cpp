#include "GameState.h"
#include "CheckerBoard.h"

void CGameState::HandleMouseClick(int row, int col)
{
	//player selects start checker
	if (playerAction == EPlayerAction::SelectStartChecker)
	{
		if (board->IsValidPosition(row, col, activePlayer))
		{
			playerAction = EPlayerAction::SelectEndPosition;
			nextMove.startRow = row;
			nextMove.startCol = col;
		}
	}
	//player selects end position
	else if (playerAction == EPlayerAction::SelectEndPosition)
	{
		nextMove.endRow = row;
		nextMove.endCol = col;
		nextMove.checkerType = activePlayer;

		if (board->ValidateMove(nextMove))
		{
			board->MoveChecker(nextMove);
			playerAction = EPlayerAction::SelectStartChecker;
			activePlayer = activePlayer == ECheckerType::red ? ECheckerType::black : ECheckerType::red;
		}
		else if (board->IsValidPosition(row, col, activePlayer))
		{
			nextMove.startRow = row;
			nextMove.startCol = col;
		}
	}
}

void CGameState::SetBoard(CCheckerBoard* inBoard)
{
	board = inBoard;
}

bool CGameState::GetSelectedSquare(int& outRow, int& outCol) const
{
	outRow = nextMove.startRow;
	outCol = nextMove.startCol;

	return (outRow >= 0 && outCol >= 0 && outRow < 8 && outCol < 8);
}