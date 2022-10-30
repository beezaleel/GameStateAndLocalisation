#include "GameState.h"

GameState::GameState(): mData({})
{
}

GameState::~GameState()
{
}

Data GameState::Read()
{
	pugi::xml_document guessANumber;
	pugi::xml_parse_result result = guessANumber.load_file("guess_a_number.xml");
	if (!result)
		hasData = false;

	pugi::xml_object_range<pugi::xml_node_iterator> states = guessANumber.child("guessANumber").children();
	if (states.empty())
		hasData = false;

	pugi::xml_node_iterator guessANumberIt;
	for (guessANumberIt = states.begin(); guessANumberIt != states.end(); guessANumberIt++) {
		pugi::xml_node guessANumberNode = *guessANumberIt;;

		pugi::xml_attribute category = guessANumberNode.attribute("category");

		pugi::xml_node_iterator guessANumberInfoIt;
		for (guessANumberInfoIt = guessANumberNode.children().begin();
			guessANumberInfoIt != guessANumberNode.children().end();
			guessANumberInfoIt++) {

			pugi::xml_node guessANumberInfoNode = *guessANumberInfoIt;
			if (std::string(category.value()) == "player1") {
				if (std::string(guessANumberInfoNode.name()) == "name")
					mData.playerOne.name = guessANumberInfoNode.child_value();
				if (std::string(guessANumberInfoNode.name()) == "totalAttempt")
					mData.playerOne.totalAttempt = atoi(guessANumberInfoNode.child_value());
				if (std::string(guessANumberInfoNode.name()) == "score")
					mData.playerOne.score = atoi(guessANumberInfoNode.child_value());
			}

			if (std::string(category.value()) == "player2") {
				if (std::string(guessANumberInfoNode.name()) == "name")
					mData.playerTwo.name = guessANumberInfoNode.child_value();
				if (std::string(guessANumberInfoNode.name()) == "totalAttempt")
					mData.playerTwo.totalAttempt = atoi(guessANumberInfoNode.child_value());
				if (std::string(guessANumberInfoNode.name()) == "score")
					mData.playerTwo.score = atoi(guessANumberInfoNode.child_value());
			}
		}

		if (std::string(guessANumberNode.name()) == "gameOver")
			mData.gameOver = atoi(guessANumberNode.child_value());

		if (std::string(guessANumberNode.name()) == "playerTwosTurn")
			mData.playerTwosTurn = atoi(guessANumberNode.child_value());
	}

	hasData = true;
	return mData;
}

void GameState::Write(Data data)
{
	pugi::xml_document guessANumber = pugi::xml_document();
	pugi::xml_node guessANumberNode = guessANumber.append_child("guessANumber");

	pugi::xml_node playerOneNode = guessANumberNode.append_child("player");
	playerOneNode.append_attribute("category") = "player1";

	pugi::xml_node playerOneNameNode = playerOneNode.append_child("name");
	playerOneNameNode.append_child(pugi::node_pcdata).set_value(data.playerOne.name.c_str());

	pugi::xml_node playerOneTotalAttemptNode = playerOneNode.append_child("totalAttempt");
	playerOneTotalAttemptNode.append_child(pugi::node_pcdata).set_value(std::to_string(data.playerOne.totalAttempt).c_str());

	pugi::xml_node playerOneScoreNode = playerOneNode.append_child("score");
	playerOneScoreNode.append_child(pugi::node_pcdata).set_value(std::to_string(data.playerOne.score).c_str());

	pugi::xml_node playerTwoNode = guessANumberNode.append_child("player");
	playerTwoNode.append_attribute("category") = "player2";

	pugi::xml_node playerTwoNameNode = playerTwoNode.append_child("name");
	playerTwoNameNode.append_child(pugi::node_pcdata).set_value(data.playerTwo.name.c_str());

	pugi::xml_node playerTwoTotalAttemptNode = playerTwoNode.append_child("totalAttempt");
	playerTwoTotalAttemptNode.append_child(pugi::node_pcdata).set_value(std::to_string(data.playerTwo.totalAttempt).c_str());

	pugi::xml_node playerTwoScoreNode = playerTwoNode.append_child("score");
	playerTwoScoreNode.append_child(pugi::node_pcdata).set_value(std::to_string(data.playerTwo.score).c_str());

	pugi::xml_node gameOverNode = guessANumberNode.append_child("gameOverNode");
	gameOverNode.append_child(pugi::node_pcdata).set_value(std::to_string((int)data.gameOver).c_str());

	pugi::xml_node playerTwosTurnNode = guessANumberNode.append_child("playerTwosTurn");
	playerTwosTurnNode.append_child(pugi::node_pcdata).set_value(std::to_string((int)data.playerTwosTurn).c_str());

	guessANumber.save_file("guess_a_number.xml");
}
