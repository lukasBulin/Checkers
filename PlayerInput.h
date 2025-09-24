#pragma once

class CCheckerBoard;

struct SNextMove
{
	static const int invalidCoordinate = -1;

	int startRow = invalidCoordinate;
	int startCol = invalidCoordinate;

	int endRow = invalidCoordinate;
	int endCol = invalidCoordinate;

	bool IsValid() const
	{
		return startRow != invalidCoordinate && startCol != invalidCoordinate
			   && endRow != invalidCoordinate && endCol != invalidCoordinate;
	}
};

class CPlayerInput
{
public:

	SNextMove ProcessPlayerInput(const CCheckerBoard* board);

private:

};