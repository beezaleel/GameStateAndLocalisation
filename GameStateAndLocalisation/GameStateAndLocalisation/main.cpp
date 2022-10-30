#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string>
#include "GameState.h"
#include <pugixml.hpp>


#define ROBOT_TEXT_COLOR 13
#define USER_TEXT_COLOR 2
#define UMPIRE_TEXT_COLOR 15
#define WRONG 4
#define RIGHT 9
#define TOTAL_ATTEMPS 10

const std::string UMPIRE_NAME = "Umpire";

std::string player1 = "Jane";
std::string player2;

int secretNumber = 0;

bool player2sTurn = false;
bool gameOver = false;

unsigned int microsecond = 5000;

struct PlayersInput {
	int secretNo;
	int guessedNo;
};

struct Result {
	int totalAttempt;
	int score;
};

Result player1Result;
Result player2Result;

void ChangeConsoleColor(int color, std::string message) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("%s\n", message.c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), USER_TEXT_COLOR);
}

PlayersInput GetInputFromComputer();
PlayersInput GetInputFromPlayer();
void Update();
void ProcessUserInput(PlayersInput, bool);

int main(int argc, char* argv) {

	srand(time(NULL));

	std::cout << R"(
                                                                                          
  ____  _   _  _____  ____  ____        _       _   _  _   _  __  __  ____   _____  ____  
 / ___|| | | || ____|/ ___|/ ___|      / \     | \ | || | | ||  \/  || __ ) | ____||  _ \ 
| |  _ | | | ||  _|  \___ \\___ \     / _ \    |  \| || | | || |\/| ||  _ \ |  _|  | |_) |
| |_| || |_| || |___  ___) |___) |   / ___ \   | |\  || |_| || |  | || |_) || |___ |  _ < 
 \____| \___/ |_____||____/|____/   /_/   \_\  |_| \_| \___/ |_|  |_||____/ |_____||_| \_\
                                                                                          
		)" << '\n';
		
	GameState gameState = GameState();
	Data state = Data();
	state = gameState.Read();
	state.gameOver = false;
	state.playerTwosTurn = false;

	state.playerOne.name = "Jane";
	state.playerOne.score = 4;
	state.playerOne.totalAttempt = 4;

	state.playerTwo.name = "Ademola";
	state.playerTwo.score = 0;
	state.playerTwo.totalAttempt = 4;

	//gameState.Write(state);


	if (gameState.hasData) {
		printf("Loading saved game . . .\n");
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
		printf("\n");
		Update();
	}

	printf("\n");
	ChangeConsoleColor(ROBOT_TEXT_COLOR, "Hello! My name is Jane. Would you like to play a number guessing game with me?");
	printf("--> ");
	std::cin >> player2;
	// TODO generate a game play struct
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + ": Hi " + player2 + " , we will both take turns in guessing a number from 1 - 3, with 5 attempts each.");
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + ": If you fail to guess the number i'm thinking, you get 0, but if you guess right, you get 1");
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + ": If we can guess correctly, then it's 1 point");
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 +": There is an Umpire that keeps record of scores. Let us begin ");

	Update();
	// display welcome message
	// check if there is a saved state
	// Ask if user wants to continue from where the game stopped
	// If yes, retreive saved data and continue game
	// If no, clear data and start from stage 1.
	return 0;
}

void Update() {
	PlayersInput playersInput;

	// Determine who plays first
	// Create method to help Jane randomly generate a number between 1 and 10
	while (!gameOver) {
		if (!player2sTurn) {
			// Computer should randomly generate a number and save in global variable
			// Allow user to input a input a value
			// Umpire proesses the data and return and save the result
			playersInput = GetInputFromComputer();
		}
		else {
			// I enter a number, same it in global variable and
			// Allow computer to guess my thought
			// Umpire proesses the data and return and save the result
			playersInput = GetInputFromPlayer();
		}
		// Umpire checks if count is up to 10
		// Umpire announces the score result
		ProcessUserInput(playersInput, player2sTurn);
		player2sTurn = !player2sTurn;
		printf("\n");

		// Check if both players have attempted 5 times each
		if ((player1Result.totalAttempt + player2Result.totalAttempt) == TOTAL_ATTEMPS) {
			if (player1Result.score > player2Result.score) {
				ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + ": THE WINNER IS " + 
					player1 + "!!! WITH A SCORE OF " + std::to_string(player1Result.score) + 
					" " + player2 + " scored " + std::to_string(player2Result.score));
			}
			else if (player2Result.score > player1Result.score) {
				ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + ": THE WINNER IS " +
					player2 + "!!! WITH A SCORE OF " + std::to_string(player2Result.score) +
					" " + player1 + " scored " + std::to_string(player1Result.score));
			}
			else {
				ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + ": NO WINNER, " +
					player2 + " AND " + player2 + " SCORED THE SAME " + std::to_string(player1Result.score));
			}

			gameOver = true;
		}
	}
}

PlayersInput GetInputFromComputer() {
	int secret, guess;
	PlayersInput input;
	// Create a random generator. Generate an int from 1 to 10
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + ": I'm thinking of a number...");
	secret = rand() % 3 + 1;
	Sleep(microsecond);
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + ": Okay " + player2 + ", can you guess now");
	printf("--> ");
	std::cin >> guess;

	input.secretNo = secret;
	input.guessedNo = guess;

	return input;
}

PlayersInput GetInputFromPlayer() {
	int secret, guess;
	PlayersInput input;
	ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + ": Hi " + player2 + " enter a secret number between 1 and 3. Don't worry, you can trust me.");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), USER_TEXT_COLOR);
	printf("--> ");
	std::cin >> secret;
	ChangeConsoleColor(USER_TEXT_COLOR, player2 + ": Okay " + player1 + ", can you guess now");
	guess = rand() % 3 + 1;
	Sleep(microsecond);
	ChangeConsoleColor(ROBOT_TEXT_COLOR, player1 + ": The number is " + std::to_string(guess));

	input.secretNo = secret;
	input.guessedNo = guess;

	return input;
}

void ProcessUserInput(PlayersInput input, bool player2sTurn) {
	if (!player2sTurn) {
		if (input.guessedNo == input.secretNo) {
			player2Result.score += 1;
			player2Result.totalAttempt += 1;
			ChangeConsoleColor(RIGHT, UMPIRE_NAME + ": You are right " + player2 + " the number is " + std::to_string(input.secretNo));
		}
		else {
			player2Result.totalAttempt += 1;
			ChangeConsoleColor(WRONG, UMPIRE_NAME + ": Wrong " + player2 + " the number is " + std::to_string(input.secretNo));
		}
	}
	else {
		if (input.guessedNo == input.secretNo) {
			player1Result.score += 1;
			player1Result.totalAttempt += 1;
			ChangeConsoleColor(RIGHT, UMPIRE_NAME + ": You are right " + player1 + " the number is " + std::to_string(input.secretNo));
		}
		else {
			player1Result.totalAttempt += 1;
			ChangeConsoleColor(WRONG, UMPIRE_NAME + ": Wrong " + player1 + " the number is " + std::to_string(input.secretNo));
		}
	}
	ChangeConsoleColor(UMPIRE_TEXT_COLOR, UMPIRE_NAME + ": Scores - " + player1 + ": " + std::to_string(player1Result.score) + ", " + player2 + ": " + std::to_string(player2Result.score));
}
