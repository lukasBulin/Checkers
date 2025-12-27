#include "GameState.h"
#include "CheckerBoard.h"

void CGameState::HandleMouseClick(int row, int col)
{
	//player selects start checker
	if (playerAction == EPlayerAction::SelectStartChecker)
	{
		if (board->IsValidPosition(row, col, activePlayer))
		{
			playerAction = EPlayerAction::SelectEndPosition;
			nextMove.startRow = row;
			nextMove.startCol = col;

			//nextMove.checkerType = board->GetTypeAt(row, col); // check piece type

			nextMove.checkerType = board->GetCheckerAt(row, col).type;

			CalculatePotentialMoves(row, col, activePlayer);
		}
	}
	//player selects end position
	else if (playerAction == EPlayerAction::SelectEndPosition)
	{
		nextMove.endRow = row;
		nextMove.endCol = col;
		nextMove.checkerColor = activePlayer;

		//if clicked correct move, switch to black
		if (board->ValidateMove(nextMove))
		{
			board->MoveChecker(nextMove);
			
			bool isCapture = abs(nextMove.endRow - nextMove.startRow) == 2;

			if (isCapture)
			{
				// Recalculate potential moves for chaining
				CalculatePotentialMoves(nextMove.endRow, nextMove.endCol, activePlayer);

				// Filter only capture moves
				for (auto it = potentialMoves.begin(); it != potentialMoves.end(); )
				{
					if (abs(nextMove.endRow - it->first) != 2 || abs(nextMove.endCol - it->second) != 2)
					{
						it = potentialMoves.erase(it); // erase returns next iterator
					}
					else
					{
						++it;
					}
				}
				if (!potentialMoves.empty())
				{
					// Keep same player and allow chaining
					nextMove.startRow = nextMove.endRow;
					nextMove.startCol = nextMove.endCol;
					return; // Exit early, don't switch turn
				}

			}
			
			playerAction = EPlayerAction::SelectStartChecker;
			activePlayer = activePlayer == ECheckerColor::red ? ECheckerColor::black : ECheckerColor::red;
			potentialMoves.clear();
		}
		// if clicked from red to a different red or black to a different black
		else if (board->IsValidPosition(row, col, activePlayer))
		{
			nextMove.startRow = row;
			nextMove.startCol = col;
			CalculatePotentialMoves(row, col, activePlayer);
		}
	}
}

void CGameState::SetBoard(CCheckerBoard* inBoard)
{
	board = inBoard;
}

bool CGameState::GetSelectedSquare(int& outRow, int& outCol) const
{
	outRow = nextMove.startRow;
	outCol = nextMove.startCol;

	return (outRow >= 0 && outCol >= 0 && outRow < 8 && outCol < 8);
}

std::vector<std::pair<int, int>> CGameState::GetPotentialMoves() const
{
	return potentialMoves;
}

void CGameState::CalculatePotentialMoves(int row, int col, ECheckerColor player)
{
	potentialMoves.clear();

	SNextMove nMove;
	nMove.startRow = row;
	nMove.startCol = col;
	nMove.checkerColor = player;

	// check the piece type
	const ECheckerType pieceType = board->GetCheckerAt(row, col).type;
	//ECheckerType pieceType = board->GetTypeAt(row, col);
	// assign the piece type
	nMove.checkerType = pieceType;

	// pawn logic
	if (pieceType == ECheckerType::pawn)
	{
		// Determine direction based on player
		const int direction = (player == ECheckerColor::red) ? 1 : -1;

		// Normal move: diagonal left
		nMove.endRow = row + direction;
		nMove.endCol = col - 1;
		if (board->ValidateMove(nMove))
		{
			potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
		}

		// Normal move: diagonal right
		nMove.endCol = col + 1;
		if (board->ValidateMove(nMove))
		{
			potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
		}

		// Capture move: diagonal left
		nMove.endRow = row + 2 * direction;
		nMove.endCol = col - 2;
		if (board->ValidateMove(nMove))
		{
			potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
		}

		// Capture move: diagonal right
		nMove.endCol = col + 2;
		if (board->ValidateMove(nMove))
		{
			potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
		}

		return;
	}

	// queen logic
	if (pieceType == ECheckerType::queen)
	{
		// All 4 diagonal directions
		const int directions[4][2] =
		{
			{ 1,  1},   // up-right
			{ 1, -1},   // up-left
			{-1,  1},   // down-right
			{-1, -1}    // down-left
		};

		for (auto& d : directions)
		{
			int r = row + d[0];
			int c = col + d[1];

			bool foundEnemy = false;
			int enemyRow = -1;
			int enemyCol = -1;

			while (r >= 0 && r < 8 && c >= 0 && c < 8)
			{
				//// OWN piece blocks everything
				//if (board->GetColorAt(r, c) == player)
				//	break;

				//// Empty square
				//if (board->GetColorAt(r, c) == ECheckerColor::noColor)
				//{

				const ECheckerColor atColor = board->GetCheckerAt(r, c).color;

				// OWN piece blocks everything
				if (atColor == player)
					break;

				// Empty square
				if (atColor == ECheckerColor::noColor)
				{

					if (!foundEnemy)
					{
						// Normal slide
						nMove.endRow = r;
						nMove.endCol = c;
						if (board->ValidateMove(nMove))
							potentialMoves.emplace_back(r, c);
					}
					else
					{
						// Landing after capture
						nMove.endRow = r;
						nMove.endCol = c;
						if (board->ValidateMove(nMove))
							potentialMoves.emplace_back(r, c);

						// Can't keep jumping after the capture
						break;
					}
				}
				else
				{
					// Enemy piece
					if (!foundEnemy)
					{
						foundEnemy = true;
						enemyRow = r;
						enemyCol = c;
					}
					else
					{
						// Two enemies ? blocked
						break;
					}
				}

				r += d[0];
				c += d[1];
			}
		}

		return;
	}
}
