#include "PlayerInput.h"
#include "CheckerBoard.h"
#include <iostream>
#include <conio.h>
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
		cout << "Enter start Column (a-h) : ";
		SCol = _getch();
		cout << SCol << endl;

		cout << "Enter start Row (1-8): ";
		SRow = _getch();
		cout << SRow << endl;

		nextMove.startCol = SCol - 'a';
		nextMove.startRow = SRow - '1';

		if (IsValidPosition(nextMove.startRow, nextMove.startCol, board)) {
			break;
		}

		cout << "Invalid start row or start column, try again!" << endl;

	} while (true);


	//End C & R

	do {
		cout << "Enter end Column (a-h): ";
		ECol = _getch();
		cout << ECol << endl;

		cout << "Enter end Row (1-8): ";
		ERow = _getch();
		cout << ERow << endl;

		nextMove.endCol = ECol - 'a';
		nextMove.endRow = ERow - '1';

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