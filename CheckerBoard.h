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

	int GetBoardSize() const;

	ECheckerType GetValueAt(int row, int col) const;

	void SetValueAt(int row, int col, ECheckerType value);

	void ResetBoard();

	bool IsValidMove(int startRow, int startCol, int endRow, int endCol) const;

private:

	static const int boardSize = 8;

	ECheckerType board[boardSize][boardSize];
};