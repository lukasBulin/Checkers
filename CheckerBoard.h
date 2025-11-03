#pragma once

struct SNextMove;
class CPlayerInput;

enum ECheckerType 
{
	red,
	black,
	none
};

class CCheckerBoard 
{
public:
	
	CCheckerBoard();

	void ResetBoard();

	int GetBoardSize() const;

	ECheckerType GetValueAt(int row, int col) const;
	void SetValueAt(int row, int col, ECheckerType value);

	bool ValidateMove(SNextMove& nextMove) const;
	void MoveChecker(const SNextMove& nextMove);

	bool IsValidPosition(int row, int col, ECheckerType playerSide) const;

private:

	static const int boardSize = 8;

	ECheckerType board[boardSize][boardSize];
};