#include "RenderBoard.h"
#include "CheckerBoard.h"

#include <cstdlib>
#include <assert.h>
#include <iostream>
using namespace std;

void CRenderBoard::RenderCheckerBoard(CCheckerBoard* board)
{
	//clear console
	system("cls");

	assert(board != nullptr);

	for (int row = 0; row < board->GetBoardSize(); row++)
	{
		for (int col = 0; col < board->GetBoardSize(); col++)
		{
			const ECheckerType value = board->GetValueAt(row, col);

			cout << "|";

			switch (value)
			{
			case ECheckerType::white:
				cout << "o";
				break;
			case ECheckerType::black:
				cout << "x";
				break;
			default:
				cout << " ";
			}
		}
		
		cout << "|" << endl;
	}
}