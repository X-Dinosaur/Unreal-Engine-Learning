/* This the console executable, that makes use of the BullCow class
* This acts as the view in a MVC pattern, and is responsible for all
* user interation. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
Ftext GetValidNumber();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game


// the entry point for our application
int main() {

	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain); // type AskToPlayAgain() into the while() works too, I just prefer this style
	

	return 0; // exit the application
}


void PlayGame() {
	
	// loop for the number of turns asking for guesses
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		Ftext ValidGuess = GetValidGuess();

		FBullCowCount GetBullCowCount = BCGame.SumbitValidGuess(ValidGuess);  // check the user input with MHW(MyHiddentWod)
		std::cout << "Bulls: " << GetBullCowCount.Bulls;
		std::cout << ". Cows: " << GetBullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();


	return;
}


void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN.\n";
	}
	else {
		std::cout << "You lose, Better luck next time!\n";
	}
	return;
}


void PrintIntro() {

	std::cout << "A fun word game.\n";
	
	// The ASCII ART
	std::cout << "__________ ____ ___.____    .____      _________  ________  __      __    ________    _____      _____  ___________._. ._. ._." << std::endl;
	std::cout << "\\______   \\    |   \\    |   |    |     \\_   ___ \\ \\_____  \\/  \\    /  \\  /  _____/   /  _  \\    /     \\ \\_   _____/| | | | | |" << std::endl;
	std::cout << " |    |  _/    |   /    |   |    |     /    \\  \\/  /   |   \\   \\/\\/   / /   \\  ___  /  /_\\  \\  /  \\ /  \\ |    __)_ | | | | | |" << std::endl;
	std::cout << " |    |   \\    |  /|    |___|    |___  \\     \\____/    |    \\        /  \\    \\_\\  \\/    |    \\/    Y    \\|        \\ \\|  \\|  \\|" << std::endl;
	std::cout << " |______  /______/ |_______ \\_______ \\  \\______  /\\_______  /\\__/\\  /    \\______  /\\____|__  /\\____|__  /_______  / __  __  __" << std::endl;
	std::cout << "        \\/                 \\/       \\/         \\/         \\/      \\/            \\/         \\/         \\/        \\/ \\/  \\/  \\/" << std::endl;

	std::cout << std::endl;

	// reset the game parameter
	Ftext WordLength = GetValidNumber();
	BCGame.Reset(WordLength);

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


// loop continually until the user gives a valid guess
Ftext GetValidGuess() {
	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status; // initialize the Status
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try (" << CurrentTry << "/" << BCGame.GetMaxTries() << ") Enter your guess : ";
		std::getline(std::cin, Guess); // player input

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			Status = EGuessStatus::OK; // assume the guess is valid
		}
	} while (Status != EGuessStatus::OK); // keep looping until get no errors
	return Guess;
}


// loop continually until the user gives a valid number (Same with the GetValidGuess function)
Ftext GetValidNumber() {
	Ftext WordLength = "";
	EWordStatus Status = EWordStatus::Invalid_Status; // initialize the Status
	do {
		std::cout << "Please enter the word lengths you want to challenge (3 to 5): "; // TODO make automatically change the minimun and maximum
		std::getline(std::cin, WordLength); // player input
		Status = BCGame.CheckWLValidity(WordLength);
		switch (Status)
		{
		case EWordStatus::Wrong_Number:
			std::cout << "Please enter the right number\n\n";
			break;
		case EWordStatus::Not_Number:
			std::cout << "Please enter a number\n\n";
			break;
		default:
			Status = EWordStatus::OK; // assume the word length is valid 
			break;
		}
	} while (Status != EWordStatus::OK); // keep looping until get no errors
	return WordLength;
}


bool AskToPlayAgain() {
	std::cout << "Do your want to play again with the same hidden word (y/n)?";
	Ftext Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
