#pragma once
#include <string>

using Fstring = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


enum class EWordStatus {
	Invalid_Status,
	OK,
	Wrong_Number,
	Not_Number
};


class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(Fstring) const;
	EWordStatus CheckWLValidity(Fstring) const;
	
	void Reset(Fstring);
	FBullCowCount SumbitValidGuess(Fstring); // use the struct to cout bull and cow


private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	Fstring MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogran(Fstring) const;
	bool IsLowercase(Fstring) const;
	bool IsNumber(Fstring) const;
	bool IsRightNumber(Fstring) const;

	Fstring GetHiddenWord(Fstring) const;
};