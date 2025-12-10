#pragma once

struct SNextMove;
class CPlayerInput;

enum ECheckerColor 
{
	red,
	black,
	noColor
};

enum ECheckerType
{
	pawn,
	queen,
	noType
};

struct SChecker
{
	ECheckerColor color = ECheckerColor::noColor;
	ECheckerType type = ECheckerType::noType;
};

class CCheckerBoard 
{
public:
	
	CCheckerBoard();

	void ResetBoard();

	int GetBoardSize() const;

	ECheckerColor GetValueAt(int row, int col) const;
	void SetValueAt(int row, int col, ECheckerColor value);

	bool ValidateMove(SNextMove& nextMove) const;
	void MoveChecker(const SNextMove& nextMove);

	bool IsValidPosition(int row, int col, ECheckerColor playerSide) const;

private:

	static const int boardSize = 8;

	SChecker board[boardSize][boardSize];
};