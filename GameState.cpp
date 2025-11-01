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
		}
	}
	else if (playerAction == EPlayerAction::SelectEndPosition)
	{

	}
	
	
	
	
	
	//if (!IsValidPosition(boardY, boardX, currentBoard)) {
	//    isCheckerSelected = false;
	//    return;
	//}

	//if (!isCheckerSelected) {
	//    // Select checker
	//    selectedX = boardX;
	//    selectedY = boardY;
	//    isCheckerSelected = true;
	//}
	//else {
	//    // Attempt to move
	//    SNextMove move;
	//    move.startRow = selectedY;
	//    move.startCol = selectedX;
	//    move.endRow = boardY;
	//    move.endCol = boardX;

	//    if (currentBoard->ValidateMove(move)) {
	//        currentBoard->MoveChecker(move);
	//    }

	//    isCheckerSelected = false;

	//}
}

void CGameState::SetBoard(CCheckerBoard* inBoard)
{
	board = inBoard;
}