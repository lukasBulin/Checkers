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
	SChecker() = default;

	SChecker(ECheckerColor inColor, ECheckerType inType)
		: color(inColor)
		, type(inType)
	{}

	ECheckerColor color = ECheckerColor::noColor;
	ECheckerType type = ECheckerType::noType;
};

class CCheckerBoard 
{
public:
	
	CCheckerBoard();

	void ResetBoard();

	int GetBoardSize() const;

	SChecker GetCheckerAt(int row, int col) const;
	void SetCheckerAt(int row, int col, const SChecker& checker);

	bool ValidateMove(SNextMove& nextMove) const;
	void MoveChecker(const SNextMove& nextMove);

	bool IsValidPosition(int row, int col, ECheckerColor playerSide) const;

	bool WasPromoted(const SNextMove& move) const;

private:

	static const int boardSize = 8;

	SChecker board[boardSize][boardSize];
};