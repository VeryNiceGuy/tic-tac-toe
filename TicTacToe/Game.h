#pragma once
#define NOMINMAX
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <cctype>
#include <ctime>
#include <deque>

enum class PlayerType
{
	Min, Max
};

enum class GameStatus
{
	On, PlayerWins, ComputerWins, Draw
};

class Game
{
public:
	Game();
	~Game();

	void requestPlayerSymbol();
	void requestPlayerMove();
	void renderBoard();
	GameStatus status();
	int computeAIMove(PlayerType type = PlayerType::Max, bool root = true);
	int evaluate();

private:
	char playerSymbol;
	char computerSymbol;
	char activeSymbol;

	std::vector<char> board;
	std::vector<char> bestMoves;
};