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

		SNextMove nextMove = whiteTurn ? playerWhite.ProcessPlayerInput(&board) : playerBlack.ProcessPlayerInput(&board);

		nextMove.checkerType = whiteTurn ? ECheckerType::white : ECheckerType::black;

		if (board.ValidateMove(nextMove))
		{
			board.MoveChecker(nextMove);

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

