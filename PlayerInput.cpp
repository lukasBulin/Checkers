#include "PlayerInput.h"
#include "CheckerBoard.h"
#include <iostream>
using namespace std;

SNextMove CPlayerInput::ProcessPlayerInput(const CCheckerBoard* board)
{
	SNextMove nextMove;

	char SCol = 0;
	char SRow = 0;
	char ECol = 0;
	char ERow = 0;

	//Start C & R

	do {
		cout << "Enter start Column (a-h): ";
		cin >> SCol;
		cin.ignore();

		cout << "Enter start Row (1-8): ";
		cin >> SRow;
		cin.ignore();

		nextMove.startCol = SCol - 'a';
		nextMove.startRow = board->GetBoardSize() - (SRow - '0');

		if (IsValidPosition(nextMove.startRow, nextMove.startCol, board)) {
			break;
		}

		cout << "Invalid start row or start column, try again!" << endl;

	} while (true);


	//End C & R

	//error with invalid input; enter d and 111 leads to error

	do {
		cout << "Enter end Column (a-h): ";
		cin >> ECol;
		cin.ignore();

		cout << "Enter end Row (1-8): ";
		cin >> ERow;
		cin.ignore();

		nextMove.endCol = ECol - 'a';
		nextMove.endRow = board->GetBoardSize() - (ERow - '0');

		if (IsValidPosition(nextMove.endRow, nextMove.endCol, board)) {
			break;
		}

		cout << "Invalid end row or end column, try again!" << endl;
	
	} while (true);

	return nextMove;
}

bool CPlayerInput::IsValidPosition(int row, int col, const CCheckerBoard* board)
{
	return row >= 0 && row < board->GetBoardSize() && col >= 0 && col < board->GetBoardSize();
}

bool CPlayerInput::IsValidMove(int startRow, int startCol, int endRow, int endCol)
{
	return 0;
}