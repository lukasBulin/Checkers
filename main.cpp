#include <iostream>
#include <random>
#include "CheckerBoard.h"
#include "RenderBoard.h"
using namespace std;

int main() {

	CCheckerBoard board;
	CRenderBoard render;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distBoardLocation(0, 7);
	uniform_int_distribution<> distCheckerType(0, 2);

	while (true)
	{
		board.SetValueAt(distBoardLocation(gen), distBoardLocation(gen), static_cast<ECheckerType>(distCheckerType(gen)));
		render.RenderCheckerBoard(&board);

		//test code
		int tempVal;
		cin >> (tempVal);
		cin.clear();
		cin.ignore();
	}

	return 0;
}

