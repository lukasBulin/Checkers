#include <random>
#include "CheckerBoard.h"
#include "RenderBoard.h"
#include "PlayerInput.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main() {

	CCheckerBoard board;
	CRenderBoard render;
	CPlayerInput playerWhite;
	CPlayerInput playerBlack;

	bool whiteTurn = true;

	board.ResetBoard();

	while (true)
	{
		render.RenderCheckerBoard(&board);

		cout << (whiteTurn ? "White Turn!" : "Black Turn!") << endl;

		const SNextMove nextMove = whiteTurn ? playerWhite.ProcessPlayerInput(&board) : playerBlack.ProcessPlayerInput(&board);

		if (board.IsValidMove(nextMove.startRow, nextMove.startCol, nextMove.endRow, nextMove.endCol, whiteTurn ? ECheckerType::white : ECheckerType::black))
		{
			board.MoveChecker(nextMove.startRow, nextMove.startCol, nextMove.endRow, nextMove.endCol);

			whiteTurn = !whiteTurn;
		}
		else
		{
			//player chose invalid tile
			cout << "Invalid Move, Try Again!, Press Any Key" << endl;
			_getch();
		}
	}

	return 0;
}

