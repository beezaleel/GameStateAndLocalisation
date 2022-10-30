#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include "GameState.h"
#include <pugixml.hpp>
#include "Language.h"


#define ROBOT_TEXT_COLOR 13
#define USER_TEXT_COLOR 2
#define UMPIRE_TEXT_COLOR 15
#define WRONG 4
#define RIGHT 9
#define TOTAL_ATTEMPS 6

const std::string UMPIRE_NAME = "Umpire";

std::string player1 = "Jane";
std::string player2;

int secretNumber = 0;
unsigned int microsecond = 5000;

bool player2sTurn = false;
bool gameOver = false;

// Stores the secret and the guessed number
struct PlayersInput {
	int secretNo;
	int guessedNo;
};

// Stores the number of attempts and score of each player
struct Result {
	int totalAttempt;
	int score;
};

LanguageData languageData;
Result player1Result;
Result player2Result;

/// <summary>
/// Changes the console color for each user. It helps different the users and adds little live to the game.
/// </summary>
/// <param name="color">The color number</param>
/// <param name="message">The string message</param>
void ChangeConsoleColor(int color, std::string message) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%s\n", message.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), USER_TEXT_COLOR);
}

PlayersInput GetInputFromComputer();
PlayersInput GetInputFromPlayer();
void Update();
void ProcessUserInput(PlayersInput, bool);
void LoadLanguage();
bool LoadState();
void SaveState();

// The main method
int main(int argc, char* argv) {

	srand((unsigned int)time(NULL));

	std::cout << R"(
                                                                                          
  ____  _   _  _____  ____  ____        _       _   _  _   _  __  __  ____   _____  ____  
 / ___|| | | || ____|/ ___|/ ___|      / \     | \ | || | | ||  \/  || __ ) | ____||  _ \ 
| |  _ | | | ||  _|  \___ \\___ \     / _ \    |  \| || | | || |\/| ||  _ \ |  _|  | |_) |
| |_| || |_| || |___  ___) |___) |   / ___ \   | |\  || |_| || |  | || |_) || |___ |  _ < 
 \____| \___/ |_____||____/|____/   /_/   \_\  |_| \_| \___/ |_|  |_||____/ |_____||_| \_\
                                                                                          
		)" << '\n';
		
	LoadLanguage();
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), UMPIRE_TEXT_COLOR);
	int option;


	printf("%s\n", languageData.welcome.c_str());
	printf("%s\n", languageData.newGame.c_str());
	printf("%s\n", languageData.savedGame.c_str());
	printf("--> ");

	std::cin >> option;
	if (option == 1);
	else if (option == 2) {
		if (LoadState()) {
			Update();
			return 0;
		}
	}
	else {
		printf("Invalid input provided, goodbye! \n");
		exit(0);
	}

	printf("\n");
	ChangeConsoleColor(ROBOT_TEXT_COLOR, languageData.hello.c_str());
	printf("--> ");
	std::cin >> player2;

	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.hi2.c_str() + player2 + languageData.hi.c_str());
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.if_.c_str());
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.you.c_str());
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.there.c_str());
	printf("\n");
	printf("\n");

	Update();

	return 0;
}


/// <summary>
/// This is the game loop
/// </summary>
void Update() {
	PlayersInput playersInput;

	while (!gameOver) {
		if (!player2sTurn) {
			playersInput = GetInputFromComputer();
		}
		else {
			playersInput = GetInputFromPlayer();
		}

		ProcessUserInput(playersInput, player2sTurn);
		player2sTurn = !player2sTurn;
		printf("\n");

		// Check if both players have attempted 5 times each
		if ((player1Result.totalAttempt + player2Result.totalAttempt) == TOTAL_ATTEMPS) {
			if (player1Result.score > player2Result.score) {
				ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + languageData.theWinner.c_str() +
					player1 + languageData.withAScore.c_str() + std::to_string(player1Result.score) +
					" " + player2 + languageData.scored.c_str() + std::to_string(player2Result.score));
			}
			else if (player2Result.score > player1Result.score) {
				ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + languageData.theWinner.c_str() +
					player2 + languageData.withAScore.c_str() + std::to_string(player2Result.score) +
					" " + player1 + languageData.scored.c_str() + std::to_string(player1Result.score));
			}
			else {
				ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + languageData.noWinner.c_str() +
					player1 + languageData.and2.c_str() + player2 + languageData.scoredTheSame.c_str() + std::to_string(player1Result.score));
			}

			gameOver = true;
		}
	}
}

/// <summary>
/// Retrive the number the computer is thinking and also the user's guess
/// </summary>
/// <returns></returns>
PlayersInput GetInputFromComputer() {
	int secret, guess;
	PlayersInput input;
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.thinking.c_str());
	secret = rand() % 3 + 1;
	Sleep(microsecond);
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.okay.c_str() + player2 + languageData.canYou.c_str());
	printf("--> ");
	std::cin >> guess;

	if (guess == 0)
		SaveState();

	input.secretNo = secret;
	input.guessedNo = guess;

	return input;
}

/// <summary>
/// Retrieve the number the user is thinking and also the computer's guess
/// </summary>
/// <returns></returns>
PlayersInput GetInputFromPlayer() {
	int secret, guess;
	PlayersInput input;
	ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + languageData.hi2.c_str() + player2 + languageData.enterA.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), USER_TEXT_COLOR);
	printf("--> ");
	std::cin >> secret;
	if (secret == 0)
		SaveState();

	ChangeConsoleColor(USER_TEXT_COLOR, player2 + languageData.okay.c_str() + player1 + languageData.canYou.c_str());
	guess = rand() % 3 + 1;
	Sleep(microsecond);
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + languageData.theNumber.c_str() + std::to_string(guess));

	input.secretNo = secret;
	input.guessedNo = guess;

	return input;
}

/// <summary>
/// Processes the input from both players and return result
/// </summary>
/// <param name="input">Data from both players</param>
/// <param name="player2sTurn">True if it's the turn of the user</param>
void ProcessUserInput(PlayersInput input, bool player2sTurn) {
	if (!player2sTurn) {
		if (input.guessedNo == input.secretNo) {
			player2Result.score += 1;
			player2Result.totalAttempt += 1;
			ChangeConsoleColor(RIGHT, UMPIRE_NAME + languageData.right.c_str() + player2 + languageData.theNumber.c_str() + std::to_string(input.secretNo));
		}
		else {
			player2Result.totalAttempt += 1;
			ChangeConsoleColor(WRONG, UMPIRE_NAME + languageData.wrong.c_str() + player2 + languageData.theNumber.c_str() + std::to_string(input.secretNo));
		}
	}
	else {
		if (input.guessedNo == input.secretNo) {
			player1Result.score += 1;
			player1Result.totalAttempt += 1;
			ChangeConsoleColor(RIGHT, UMPIRE_NAME + languageData.right.c_str() + player1 + languageData.theNumber.c_str() + std::to_string(input.secretNo));
		}
		else {
			player1Result.totalAttempt += 1;
			ChangeConsoleColor(WRONG, UMPIRE_NAME + languageData.wrong.c_str() + player1 + languageData.theNumber.c_str() + std::to_string(input.secretNo));
		}
	}
	ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + languageData.scores.c_str() + player1 + ": " + std::to_string(player1Result.score) + ", " + player2 + ": " + std::to_string(player2Result.score));
}

/// <summary>
/// Retrieve the save state from XML
/// </summary>
/// <returns></returns>
bool LoadState() {
	GameState gameState = GameState();
	Data state = Data();
	state = gameState.Read();

	if (gameState.hasData) {
		printf("%s\n", languageData.loading.c_str());
		printf("\n");
		player1Result.score = state.playerOne.score;
		player1Result.totalAttempt = state.playerOne.totalAttempt;

		player2 = state.playerTwo.name.c_str();
		player2Result.score = state.playerTwo.score;
		player2Result.totalAttempt = state.playerTwo.totalAttempt;

		gameOver = state.gameOver;
		player2sTurn = state.playerTwosTurn;

		printf("Player1: %s, totalAttempt: %d, score: %d \n", player1.c_str(), player1Result.totalAttempt, player1Result.score);
		printf("Player2: %s, totalAttempt: %d, score: %d \n", player2.c_str(), player2Result.totalAttempt, player2Result.score);
		printf("\n");
	}
	else {
		printf("%s\n", languageData.previous.c_str());
	}
	return gameState.hasData;
}

/// <summary>
/// Save game state to xml
/// </summary>
void SaveState() {
	printf("%s\n", languageData.saving.c_str());

	GameState gameState = GameState();
	Data state = Data();

	state.gameOver = gameOver;
	state.playerTwosTurn = player2sTurn;

	state.playerOne.name = player1;
	state.playerOne.score = player1Result.score;
	state.playerOne.totalAttempt = player1Result.totalAttempt;

	state.playerTwo.name = player2;
	state.playerTwo.score = player2Result.score;
	state.playerTwo.totalAttempt = player2Result.totalAttempt;

	gameState.Write(state);
	printf("%s\n", languageData.goodbye.c_str());
	exit(0);
}

/// <summary>
/// Loads the selected language from xml
/// </summary>
void LoadLanguage() {
	int option;
	Language language = Language();
	languageData = LanguageData();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), UMPIRE_TEXT_COLOR);

	printf("Please select a language.\n");
	printf("1) English\n");
	printf("2) French\n");
	printf("3) Yoruba\n");
	printf("4) Hindi\n");
	printf("5) Spanish\n");

	printf("--> ");
	std::cin >> option;
	switch (option)
	{
	case 1:
		languageData = language.Read("en");
		break;
	case 2:
		languageData = language.Read("fr");
		break;
	case 3:
		languageData = language.Read("yo");
		break;
	case 4:
		languageData = language.Read("hi");
		break;
	case 5:
		languageData = language.Read("sp");
		break;
	default:
		languageData = language.Read("en");
		break;
	}
}
