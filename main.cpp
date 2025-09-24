#include <random>
#include "CheckerBoard.h"
#include "RenderBoard.h"
#include "PlayerInput.h"
using namespace std;

int main() {

	CCheckerBoard board;
	CRenderBoard render;
	CPlayerInput player;

	/*random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distBoardLocation(0, 7);
	uniform_int_distribution<> distCheckerType(0, 2);*/

	board.ResetBoard();

	while (true)
	{
		/*board.SetValueAt(distBoardLocation(gen), distBoardLocation(gen), static_cast<ECheckerType>(distCheckerType(gen)));*/
		render.RenderCheckerBoard(&board);
		player.ProcessPlayerInput(&board);
	}

	return 0;
}

