#include "GameState.h"

void CGameState::HandleMouseClick(int row, int col)
{
	// Convert screen coordinates to board coordinates
	//int boardX = static_cast<int>(xpos / (800 / 8)); // assuming 8x8 board
	//int boardY = static_cast<int>(ypos / (800 / 8));

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