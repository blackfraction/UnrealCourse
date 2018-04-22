/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

// instantiate a new game
FBullCowGame BCGame;

// application entry point
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain() == true); // if false, exit application
}


void PrintIntro()
{
	// print out introduction
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "An isogram is a word which contains each letter exactly once." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	for (int32 count = 1; count <= MaxTries; count++) // TODO change from FOR to WHILE loop once we are validating tries
	{
		FText Guess = GetValidGuess();
		
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	// TODO summarize game
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " - Please take a guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess i not an isogram!\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase!\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Your guess is not a " << BCGame.GetHiddenWordLength() << " letter word!\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	}
	while (Status != EGuessStatus::OK); // keep looping until we get no errors
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}