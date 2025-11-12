#pragma once

#include "CheckerBoard.h"
#include "PlayerInput.h"
#include <vector>

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

	std::vector<std::pair<int, int>> GetPotentialMoves() const;

	void CalculatePotentialMoves(int row, int col, ECheckerType player);

private:

	ECheckerType activePlayer = ECheckerType::red;
	EPlayerAction playerAction = SelectStartChecker;
	CCheckerBoard* board = nullptr;
	SNextMove nextMove;
	std::vector<std::pair<int, int>> potentialMoves;
};