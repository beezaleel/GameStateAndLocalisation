#pragma once
#include <string>
#include <pugixml.hpp>

struct PlayerData {
	std::string name = "";
	int totalAttempt = 0;
	int score = 0;
};

struct Data {
	bool gameOver = false;
	bool playerTwosTurn = false;
	PlayerData playerOne;
	PlayerData playerTwo;
};

class GameState
{
public:
	GameState();
	~GameState();
	bool hasData;
	Data Read();
	void Write(Data data);

private:
	Data mData;
};
