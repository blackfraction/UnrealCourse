#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Alphabetic,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetDifficulty() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	
	void SetDifficulty(int32);
	
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); //TODO make a richer return value.

	// counts bulls and cows and increases try number assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);
	


private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyDifficulty;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsAlpha(FString) const;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;	
};