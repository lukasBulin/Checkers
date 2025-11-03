#pragma once

#include "CheckerBoard.h"
#include "PlayerInput.h"

enum EPlayerAction
{
	SelectStartChecker,
	SelectEndPosition
};

class CGameState
{
public:

	void HandleMouseClick(int row, int col);

	void SetBoard(CCheckerBoard* inBoard);

	bool GetSelectedSquare(int& outRow, int& outCol) const;

private:

	ECheckerType activePlayer = ECheckerType::red;
	EPlayerAction playerAction = SelectStartChecker;
	CCheckerBoard* board = nullptr;
	SNextMove nextMove;
};