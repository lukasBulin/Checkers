#pragma once

#include "CheckerBoard.h"

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

private:

	ECheckerType activePlayer = ECheckerType::red;
	EPlayerAction playerAction = SelectStartChecker;
	CCheckerBoard* board = nullptr;
};