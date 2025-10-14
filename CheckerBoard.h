#pragma once

struct SNextMove;

enum ECheckerType 
{
	white,
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

private:

	static const int boardSize = 8;

	ECheckerType board[boardSize][boardSize];
};