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

			CalculatePotentialMoves(row, col, activePlayer);
		}
	}
	//player selects end position
	else if (playerAction == EPlayerAction::SelectEndPosition)
	{
		nextMove.endRow = row;
		nextMove.endCol = col;
		nextMove.checkerType = activePlayer;

		//if clicked correct move, switch to black
		if (board->ValidateMove(nextMove))
		{
			board->MoveChecker(nextMove);
			playerAction = EPlayerAction::SelectStartChecker;
			activePlayer = activePlayer == ECheckerType::red ? ECheckerType::black : ECheckerType::red;
			potentialMoves.clear();
		}
		// if clicked from red to a different red or black to a different black
		else if (board->IsValidPosition(row, col, activePlayer))
		{
			nextMove.startRow = row;
			nextMove.startCol = col;
			CalculatePotentialMoves(row, col, activePlayer);
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

std::vector<std::pair<int, int>> CGameState::GetPotentialMoves() const
{
	return potentialMoves;
}

void CGameState::CalculatePotentialMoves(int row, int col, ECheckerType player)
{
	potentialMoves.clear();

	SNextMove nMove;
	nMove.startRow = row;
	nMove.startCol = col;

	// Determine direction based on player
	const int direction = (player == ECheckerType::red) ? 1 : -1;
	nMove.checkerType = player;

	// Normal move: diagonal left
	nMove.endRow = row + direction;
	nMove.endCol = col - 1;
	if (board->ValidateMove(nMove))
	{
		potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
	}

	// Normal move: diagonal right
	nMove.endCol = col + 1;
	if (board->ValidateMove(nMove))
	{
		potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
	}

	// Capture move: diagonal left
	nMove.endRow = row + 2 * direction;
	nMove.endCol = col - 2;
	if (board->ValidateMove(nMove))
	{
		potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
	}

	// Capture move: diagonal right
	nMove.endCol = col + 2;
	if (board->ValidateMove(nMove))
	{
		potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
	}
}
