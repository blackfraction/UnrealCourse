/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include <limits>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintOutro();
void PlayGame();
void AskForDifficulty();
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
	std::cout << "MM                   MM                                     \n";
	std::cout << "MMM+                8MM                                     \n";
	std::cout << "MMMMMM            :MMM                        MM,     ZMM   \n";
	std::cout << "ZMMM+MMMM+       MMMM                         MMMO  MMMMM   \n";
	std::cout << "   MMM  MMMMMMMMMMMN                            MMMMMMMZ    \n";
	std::cout << "    MMMMM   MMMMMMMMM                        ZMMMZMZ, MMMMMM\n";
	std::cout << "      $MMD  MMM    MMMMMMM         MMMMMMMMMMMMM         MMM\n";
	std::cout << "777MMMMDI               I7MMM~  7MMMIIIIIII+                \n";
	std::cout << "MMM?                       MMM +MM                          \n";
	std::cout << "                           ZMM +M+                          \n";
	std::cout << "        B U L L S          MMM  MM            C O W S       \n";
	std::cout << "                     MMMMMMMO    MMMMMMM                    \n";
	std::cout << "               ZMMMMMMMM               MMMMM                \n";
	std::cout << "             MMMM                         MMMMM             \n";
	std::cout << "            MMM                               MMMMM         \n";
	std::cout << "           MMO                                   MM,        \n";
	std::cout << std::endl;
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "An isogram is a word which contains each letter exactly once." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	AskForDifficulty();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintOutro();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " - Please take a guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Alphabetic:
			std::cout << "Please use only alphabetic characters!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase!\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess i not an isogram!\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Your guess is not a " << BCGame.GetHiddenWordLength() << " letter word!\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	}
	while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void AskForDifficulty()
{
	std::cout << "What is your preferred difficulty setting? (1-3)\n\n";
	int32 Difficulty = 0;
	std::cin >> Difficulty;
	std::cin.ignore(INT_MAX, '\n');
	std::cout << std::endl;
	BCGame.SetDifficulty(Difficulty);
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)\n\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintOutro()
{
	int32 MaxTries = BCGame.GetMaxTries();
	if (BCGame.IsGameWon() == true && BCGame.GetCurrentTry() <= MaxTries)
	{
		std::cout << "Congratulations! You have guessed the correct isogram!\n";
	}
	else
	{
		std::cout << "Sorry you're out of turns. Better Luck next time!\n";
	}
}