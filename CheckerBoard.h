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

private:

	static const int boardSize = 8;

	ECheckerType board[boardSize][boardSize];
};