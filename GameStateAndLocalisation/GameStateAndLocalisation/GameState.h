#pragma once
#include <string>
#include <pugixml.hpp>

struct PlayerData {
	std::string name;
	int totalAttempt;
	int score;
};

struct Data {
	bool gameOver;
	bool playerTwosTurn;
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
