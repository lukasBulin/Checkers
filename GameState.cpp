#include "GameState.h"
#include "CheckerBoard.h"

void CGameState::HandleMouseClick(int row, int col)
{
	//player selects start checker
	if (playerAction == EPlayerAction::SelectStartChecker)
	{
		captureOnly = false;

		if (board->IsValidPosition(row, col, activePlayer))
		{
			playerAction = EPlayerAction::SelectEndPosition;
			nextMove.startRow = row;
			nextMove.startCol = col;

			nextMove.checkerType = board->GetCheckerAt(row, col).type;

			CalculatePotentialMoves(row, col, activePlayer);
		}
	}
	//player selects end position
	else if (playerAction == EPlayerAction::SelectEndPosition)
	{
		// lock player during chaining
		if (captureOnly)
		{
			bool valid = false;
			for (const auto& move : potentialMoves)
			{
				if (move.first == row && move.second == col)
				{
					valid = true;
					break;
				}
			}

			if (!valid)
				return; // Ignore illegal clicks
		}

		nextMove.endRow = row;
		nextMove.endCol = col;
		nextMove.checkerColor = activePlayer;

		//if clicked correct move, switch to black
		if (board->ValidateMove(nextMove))
		{
			board->MoveChecker(nextMove);
			
			bool isCapture = (nextMove.rowToDelete != SNextMove::invalidCoordinate);

			bool wasPromoted = board->WasPromoted(nextMove);

			// Promotion always ends the turn
			if (wasPromoted)
			{
				playerAction = EPlayerAction::SelectStartChecker;
				activePlayer = (activePlayer == ECheckerColor::red) ? ECheckerColor::black : ECheckerColor::red;
				potentialMoves.clear();
				return;
			}

			if (isCapture)
			{
				captureOnly = true;

				CalculatePotentialMoves(nextMove.endRow, nextMove.endCol, activePlayer);

				if (!potentialMoves.empty())
				{
					nextMove.startRow = nextMove.endRow;
					nextMove.startCol = nextMove.endCol;
					return; // Continue chaining
				}

				captureOnly = false; // No chain possible
			}
			
			playerAction = EPlayerAction::SelectStartChecker;
			activePlayer = activePlayer == ECheckerColor::red ? ECheckerColor::black : ECheckerColor::red;
			potentialMoves.clear();
		}
		// lock chaining (only can move that specific piece that has been granted chaining)
		else if (!captureOnly && board->IsValidPosition(row, col, activePlayer))
		{
			nextMove.startRow = row;
			nextMove.startCol = col;
			nextMove.checkerType = board->GetCheckerAt(row, col).type;
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
	// assign the piece type
	nMove.checkerType = pieceType;

	// pawn logic
	if (pieceType == ECheckerType::pawn)
	{
		// Determine direction based on player
		const int direction = (player == ECheckerColor::red) ? 1 : -1;

		if (!captureOnly)
		{
			// Normal move: diagonal left
			nMove.endRow = row + direction;
			nMove.endCol = col - 1;
			if (board->ValidateMove(nMove))
				potentialMoves.emplace_back(nMove.endRow, nMove.endCol);

			// Normal move: diagonal right
			nMove.endCol = col + 1;
			if (board->ValidateMove(nMove))
				potentialMoves.emplace_back(nMove.endRow, nMove.endCol);
		}

		// Capture move: diagonal left
		{
			int midRow = row + direction;
			int midCol = col - 1;
			int landRow = row + 2 * direction;
			int landCol = col - 2;

			if (midRow >= 0 && midRow < 8 &&
				midCol >= 0 && midCol < 8 &&
				landRow >= 0 && landRow < 8 &&
				landCol >= 0 && landCol < 8)
			{
				if (board->GetCheckerAt(midRow, midCol).color != ECheckerColor::noColor &&
					board->GetCheckerAt(midRow, midCol).color != player &&
					board->GetCheckerAt(landRow, landCol).color == ECheckerColor::noColor)
				{
					nMove.endRow = landRow;
					nMove.endCol = landCol;
					potentialMoves.emplace_back(landRow, landCol);
				}
			}
		}

		// Capture move: diagonal right
		{
			int midRow = row + direction;
			int midCol = col + 1;
			int landRow = row + 2 * direction;
			int landCol = col + 2;

			if (midRow >= 0 && midRow < 8 &&
				midCol >= 0 && midCol < 8 &&
				landRow >= 0 && landRow < 8 &&
				landCol >= 0 && landCol < 8)
			{
				if (board->GetCheckerAt(midRow, midCol).color != ECheckerColor::noColor &&
					board->GetCheckerAt(midRow, midCol).color != player &&
					board->GetCheckerAt(landRow, landCol).color == ECheckerColor::noColor)
				{
					nMove.endRow = landRow;
					nMove.endCol = landCol;
					potentialMoves.emplace_back(landRow, landCol);
				}
			}
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

		// chaining mode
		if (captureOnly)
		{
			for (auto& d : directions)
			{
				int enemyRow = row + d[0];
				int enemyCol = col + d[1];
				int landRow = row + 2 * d[0];
				int landCol = col + 2 * d[1];

				if (enemyRow < 0 || enemyRow >= 8 || enemyCol < 0 || enemyCol >= 8)
					continue;
				if (landRow < 0 || landRow >= 8 || landCol < 0 || landCol >= 8)
					continue;

				const auto& enemy = board->GetCheckerAt(enemyRow, enemyCol);
				const auto& landing = board->GetCheckerAt(landRow, landCol);

				if (enemy.color != ECheckerColor::noColor &&
					enemy.color != player &&
					landing.color == ECheckerColor::noColor)
				{
					nMove.endRow = landRow;
					nMove.endCol = landCol;
					potentialMoves.emplace_back(landRow, landCol);
				}
			}

			return;
		}

		// normal mode (slides + captures)
		for (auto& d : directions)
		{
			int r = row + d[0];
			int c = col + d[1];
			bool foundEnemy = false;

			while (r >= 0 && r < 8 && c >= 0 && c < 8)
			{
				const ECheckerColor atColor = board->GetCheckerAt(r, c).color;

				// OWN piece blocks everything
				if (atColor == player)
					break;

				// Empty square
				if (atColor == ECheckerColor::noColor)
				{
					if (!foundEnemy && !captureOnly)
					{
						nMove.endRow = r;
						nMove.endCol = c;
						if (board->ValidateMove(nMove))
							potentialMoves.emplace_back(r, c);
					}
					else if (foundEnemy)
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
					if (foundEnemy)
						break;

					foundEnemy = true;
				}

				r += d[0];
				c += d[1];
			}
		}

		return;
	}
}
