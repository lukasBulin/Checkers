#pragma once

class CCheckerBoard;

struct SNextMove
{
	static const int invalidCoordinate = -1;

	int startCol = invalidCoordinate;
	int startRow = invalidCoordinate;

	int endCol = invalidCoordinate;
	int endRow = invalidCoordinate;

	//add info about which tile should be removed, int RowTodelete & colToDeltete

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

};