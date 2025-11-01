#include "CheckerBoard.h"
#include "GameState.h"
#include "RenderBoardConsole.h"
#include "RenderBoardGL.h"
#include "PlayerInput.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main() {

	CCheckerBoard board;
	//CRenderBoardConsole render;
	CRenderBoardGL render;
	//CPlayerInput playerWhite;
	//CPlayerInput playerBlack;
	CGameState gameState;

	gameState.SetBoard(&board);

	if (!render.CreateWindow(&gameState))
	{
		return -1;
	}

	/*if (!render.InitializeRender())
	{
		return -1;
	}*/

	bool whiteTurn = true;

	board.ResetBoard();

	bool bWindowClosed = false;

	while (!bWindowClosed)
	{
		render.RenderCheckerBoard(&board);

		//cout << (whiteTurn ? "White Turn!" : "Black Turn!") << endl;

		//SNextMove nextMove = whiteTurn ? playerWhite.ProcessPlayerInput(&board) : playerBlack.ProcessPlayerInput(&board);

		//nextMove.checkerType = whiteTurn ? ECheckerType::white : ECheckerType::black;

		//if (board.ValidateMove(nextMove))
		//{
		//	board.MoveChecker(nextMove);

		//	whiteTurn = !whiteTurn;
		//}
		//else
		//{
		//	//player chose invalid tile
		//	cout << "Invalid Move, Try Again!, Press Any Key" << endl;
		//	_getch();
		//}

		bWindowClosed = render.IsWindowClosed();
	}

	render.DeinitializeWindow();

	return 0;
}