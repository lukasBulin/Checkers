#pragma once

#include "CheckerBoard.h"
#include "PlayerInput.h"
#include <vector>

enum EPlayerAction
{
	SelectStartChecker,
	SelectEndPosition
};

enum EGamePhase
{
	StartGameMenu,
	InGame,
	GameOver
};

class CGameState
{
public:

	void HandleMouseClick(int row, int col);

	void SetBoard(CCheckerBoard* inBoard);

	bool GetSelectedSquare(int& outRow, int& outCol) const;

	std::vector<std::pair<int, int>> GetPotentialMoves() const;

	void CalculatePotentialMoves(int row, int col, ECheckerColor player);

	EGamePhase GetGamePhase() const;
	ECheckerColor GetWinner() const;

	bool HasPlayerWon(ECheckerColor player) const;

private:

	EGamePhase currentGamePhase = EGamePhase::InGame;

	ECheckerColor activePlayer = ECheckerColor::red;
	EPlayerAction playerAction = SelectStartChecker;
	CCheckerBoard* board = nullptr;
	SNextMove nextMove;
	std::vector<std::pair<int, int>> potentialMoves;
	bool captureOnly = false;
	ECheckerColor winner = ECheckerColor::noColor;

};