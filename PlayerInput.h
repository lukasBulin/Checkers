#pragma once
#include "CheckerBoard.h"

class CCheckerBoard;

struct SNextMove
{
	static const int invalidCoordinate = -1;

	int startCol = invalidCoordinate;
	int startRow = invalidCoordinate;

	int endCol = invalidCoordinate;
	int endRow = invalidCoordinate;

	ECheckerType checkerType = ECheckerType::none;

	int colToDelete = invalidCoordinate;
	int rowToDelete = invalidCoordinate;

	bool IsValid() const
	{
		return startCol != invalidCoordinate && startRow != invalidCoordinate
			   && endCol != invalidCoordinate && endRow != invalidCoordinate
			   && checkerType != ECheckerType::none;
	}
};

class CPlayerInput
{
public:

	SNextMove ProcessPlayerInput(const CCheckerBoard* board);

protected:

	bool IsValidPosition(int row, int col, const CCheckerBoard* board);

};