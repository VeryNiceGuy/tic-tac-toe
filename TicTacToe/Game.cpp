#include "Game.h"

namespace
{
	const int Infinity = 99999999;
}

Game::Game()
{
	srand((unsigned)time(NULL));

	board.resize(9);
	bestMoves.resize(9);

	for (std::vector<char>::iterator iter = board.begin(); iter != board.end(); ++iter)
		*iter = 0;
}

Game::~Game() {}

void Game::requestPlayerSymbol()
{
	std::cout << "Enter your symbol, either X or O: ";
	std::cin >> playerSymbol;

	playerSymbol = std::tolower(playerSymbol);
	computerSymbol = playerSymbol == 'x' ? 'o' : 'x';
}

void Game::requestPlayerMove()
{
	std::string coordStr;
	std::string xStr;
	std::string yStr;

	int x;
	int y;

	size_t delimiterPosition;

	activeSymbol = playerSymbol;

	std::cout << "Enter your move from 0,0 to 2,2: ";
	std::cin >> coordStr;

	delimiterPosition  = coordStr.find(',');

	xStr = coordStr.substr(0, delimiterPosition);
	yStr = coordStr.substr(delimiterPosition + 1);

	x = std::stoi(xStr);
	y = std::stoi(yStr);

	board[x + y * 3] = playerSymbol;
}

void Game::renderBoard()
{
	std::cout
		<< board[0] << " | " << board[1] << " | " << board[2] << std::endl
		<< board[3] << " | " << board[4] << " | " << board[5] << std::endl
		<< board[6] << " | " << board[7] << " | " << board[8] << std::endl << std::endl;
}

GameStatus Game::status()
{
	if ((board[0] == playerSymbol && board[1] == playerSymbol && board[2] == playerSymbol) ||
		(board[3] == playerSymbol && board[4] == playerSymbol && board[5] == playerSymbol) ||
		(board[6] == playerSymbol && board[7] == playerSymbol && board[8] == playerSymbol) ||

		(board[0] == playerSymbol && board[3] == playerSymbol && board[6] == playerSymbol) ||
		(board[1] == playerSymbol && board[4] == playerSymbol && board[7] == playerSymbol) ||
		(board[2] == playerSymbol && board[5] == playerSymbol && board[8] == playerSymbol) ||

		(board[0] == playerSymbol && board[4] == playerSymbol && board[8] == playerSymbol) ||
		(board[2] == playerSymbol && board[4] == playerSymbol && board[6] == playerSymbol))
	{
		return GameStatus::PlayerWins;
	}
	else if ((board[0] == computerSymbol && board[1] == computerSymbol && board[2] == computerSymbol) ||
		(board[3] == computerSymbol && board[4] == computerSymbol && board[5] == computerSymbol) ||
		(board[6] == computerSymbol && board[7] == computerSymbol && board[8] == computerSymbol) ||

		(board[0] == computerSymbol && board[3] == computerSymbol && board[6] == computerSymbol) ||
		(board[1] == computerSymbol && board[4] == computerSymbol && board[7] == computerSymbol) ||
		(board[2] == computerSymbol && board[5] == computerSymbol && board[8] == computerSymbol) ||

		(board[0] == computerSymbol && board[4] == computerSymbol && board[8] == computerSymbol) ||
		(board[2] == computerSymbol && board[4] == computerSymbol && board[6] == computerSymbol))
	{
		return GameStatus::ComputerWins;
	}
	else
	{
		for (std::vector<char>::iterator iter = board.begin(); iter != board.end(); ++iter)
			if (!*iter) return GameStatus::Draw;
	}

	return GameStatus::On;
}


int Game::computeAIMove(PlayerType type, bool root) {

	if (!root)
	{
		int result = evaluate();
		if (result != 1) {
			return result;
		}
	}

	std::deque<int> moves;

	for (int i = 0; i < 9; ++i)
		if (!board[i])
			moves.push_back(i);

	char symbol;
	int best;

	activeSymbol = playerSymbol;

	if (type == PlayerType::Min)
	{
		symbol = playerSymbol;
		best = Infinity;
	}
	else
	{
		symbol = computerSymbol;
		best = -Infinity;
	}

	if (root)
	{
		for (std::vector<char>::iterator iter = bestMoves.begin(); iter != bestMoves.end(); ++iter)
			*iter = 0;
	}

	int index = 0;

	while (!moves.empty()) {
		board[moves.front()] = symbol;

		if (type == PlayerType::Min)
			best = std::min(computeAIMove(PlayerType::Max, false), best);
		else
		{
			int value = computeAIMove(PlayerType::Min, false);

			if (!root)
				best = std::max(value, best);
			else
			{
				if (value > best) {
					best = value;
					index = 0;
					bestMoves[index] = moves.front();
				}
				else if (value == best)
					bestMoves[++index] = moves.front();
			}
		}

		board[moves.front()] = 0;
		moves.pop_front();
	}

	if (!root)
		return best;
	else
	{
		if (index > 0)
			index = rand() % index;

		board[bestMoves[index]] = computerSymbol;

		return 0;
	}
}

int Game::evaluate()
{
	switch (status())
	{
	case GameStatus::ComputerWins:
		return Infinity;

	case GameStatus::PlayerWins:
		return -Infinity;

	case GameStatus::Draw:
		return 0;
	}

	return 1;
}