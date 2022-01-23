#include "Game.h"

int main()
{
	Game game;
	game.requestPlayerSymbol();

	while (1)
	{
		game.requestPlayerMove();
		game.renderBoard();

		if (game.status() == GameStatus::PlayerWins)
		{
			std::cout << "Player Wins" << std::endl;

			break;
		}

		game.computeAIMove();
		game.renderBoard();

		if (game.status() == GameStatus::ComputerWins)
		{
			std::cout << "Computer Wins" << std::endl;

			break;
		}
	}

	std::cout << "Thanks for playing";

	return 0;
}