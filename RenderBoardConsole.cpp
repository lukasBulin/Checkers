#include "RenderBoardConsole.h"
#include "CheckerBoard.h"

#include <cstdlib>
#include <assert.h>
#include <iostream>
using namespace std;

void CRenderBoardConsole::RenderCheckerBoard(const CCheckerBoard* board)
{
	//clear console
	system("cls");

	assert(board != nullptr);

	for (int row = board->GetBoardSize() - 1; row >= 0; row--)
	{
		cout << row + 1 << " ";

		for (int col = 0; col < board->GetBoardSize(); col++)
		{
			const SChecker value = board->GetCheckerAt(row, col);

			cout << "|";

			switch (value.color)
			{
			case ECheckerColor::red:
				cout << "o";
				break;
			case ECheckerColor::black:
				cout << "x";
				break;
			default:

				//odd row, even col, dark square
				if ((row % 2 != 0) && (col % 2 != 0))
				{
					cout << static_cast<char>(176);
				}
				//even row, even col
				else if ((row % 2 == 0) && (col % 2 == 0))
				{
					cout << static_cast<char>(176);
				}
				//white square instead
				else
				{
					cout << " ";
				}
			}
		}

		cout << "|" << endl;
	}

	cout << "   ";

	for (int col = 0; col < board->GetBoardSize(); col++)
	{
		cout << static_cast<char>(97 + col) << " ";
	}

	cout << endl;
}