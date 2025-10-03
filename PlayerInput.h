#pragma once

class CCheckerBoard;

struct SNextMove
{
	static const int invalidCoordinate = -1;

	int startCol = invalidCoordinate;
	int startRow = invalidCoordinate;

	int endCol = invalidCoordinate;
	int endRow = invalidCoordinate;

	bool IsValid() const
	{
		return startCol != invalidCoordinate && startRow != invalidCoordinate
			   && endCol != invalidCoordinate && endRow != invalidCoordinate;
	}
};

class CPlayerInput
{
public:

	SNextMove ProcessPlayerInput(const CCheckerBoard* board);

private:

	bool IsValidPosition(int row, int col, const CCheckerBoard* board);
	bool IsValidMove(int startRow, int startCol, int endRow, int endCol);

};