#pragma once

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

	bool IsValidMove(int startRow, int startCol, int endRow, int endCol) const;
	void MoveChecker(int startRow, int startCol, int endRow, int endCol);

private:

	static const int boardSize = 8;

	ECheckerType board[boardSize][boardSize];
};