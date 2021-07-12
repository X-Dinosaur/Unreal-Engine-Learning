#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset("3"); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


// "xxx = 2" == "xxx {2}"
int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 5}, {5, 10}, {6, 15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset(Fstring WordLength) {
	// magic number, the point is change a value to apply all the code which is related. 
	Fstring HIDDENT_WORD = GetHiddenWord(WordLength);
	
	MyCurrentTry = 1;
	MyHiddenWord = HIDDENT_WORD;
	bGameIsWon = false;
	return;
}


// avoid implicit dependencies, all syntax are work dependently
EGuessStatus FBullCowGame::CheckGuessValidity(Fstring Guess) const {
	if (!IsIsogran(Guess)) {  // if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {  // if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else {  // otherwise
		return EGuessStatus::OK;
	}
}


EWordStatus FBullCowGame::CheckWLValidity(Fstring WordLength) const {
	if (!IsNumber(WordLength)) { // if the word isn't number 
		return EWordStatus::Not_Number;
	}
	else if (!IsRightNumber(WordLength)) { // if the word length is 0
		return EWordStatus::Wrong_Number;
	}
	else { // otherwise
		return EWordStatus::OK;
	}
}


// receives a VALID guess, incriments turn and returns count
FBullCowCount FBullCowGame::SumbitValidGuess(Fstring Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount; // A struct
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// if they match then
				if (GChar == MHWChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogran(Fstring Word) const {
	// treat 0 and 1 letter as isograms
	if (Word.length() <= 1) { return true; };

	TMap<char, bool> LetterSeen; // setup a map

	// loop through all the letters of the word
	for (auto Letter : Word) { // for all letters of the word, auto --> the compiler decide the type
		Letter = tolower(Letter); // handle mixed case

		if (LetterSeen[Letter]) { // if the letter is in the map
			return false;
		}
		else{// otherwise
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for example in cases where \0 is entered (\0 not actually send null. To do that we need to send CTRL + @ in windows)
}

bool FBullCowGame::IsLowercase(Fstring Word) const {
	for (auto Letter : Word) {  // for all letters of the word, auto --> the compiler decide the type
		if (!islower(Letter)) { // if not a lowercase letter
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsNumber(Fstring Number) const {
	/*for (int i = 0; i < Number.length(); i++) {
		int temp = (int)Number[i];
		if (temp >= 48 && temp <= 57) {
			continue;
		}
		else {
			return false;
		}
	}
	*/
	for (int single : Number) {
		if (single >= 48 && single <= 57) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsRightNumber(Fstring Number) const {
	if (GetHiddenWord(Number).length() == 0) { // if not in the map it return (word length) 0
		return false;
	}
	return true;
}

Fstring FBullCowGame::GetHiddenWord(Fstring WordLength) const {
	TMap<Fstring, Fstring> HIDDENT_WORDS{ {"3", "ant"}, {"4", "read"}, {"5", "plane"} }; // TODO A word length contain at less 3 words and computer automatically select one to player
	const Fstring HIDDENT_WORD = HIDDENT_WORDS[WordLength];
	return HIDDENT_WORD;
}
