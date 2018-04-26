/*
This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include <limits>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PrintOutro();
void PlayGame();
void AskForDifficulty();
void AskForHiddenWordLength();
FText GetValidGuess();
bool AskToPlayAgain();
void ResetIOBuffer();

// instantiate a new game, which we re-use across plays
FBullCowGame BCGame;

// application entry point
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain() == true); // exit application
}


void PrintIntro()
{
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


// Plays a single round to completion
void PlayGame()
{
	BCGame.Reset();
	AskForHiddenWordLength();
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

		// get a guess from the player
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
	while (Status != EGuessStatus::OK); // keep looping until no errors received
	return Guess;
}

void AskForDifficulty()
{
	int32 Difficulty = 0;
	std::cout << "What is your preferred difficulty setting? (0-3, higher numbers equals less maximum tries.)\n\n";
	while (!(std::cin >> Difficulty))
	{
			std::cin.clear();
			ResetIOBuffer();
	}
	BCGame.SetDifficulty(Difficulty);
	ResetIOBuffer();
}

void AskForHiddenWordLength()
{
	int32 HiddenWordLength = 0;
	std::cout << "What is your preferred word length? (3 to 7 letters)\n\n";
	while (!(std::cin >> HiddenWordLength))
	{
		std::cin.clear();
		ResetIOBuffer();
	}
	BCGame.SetHiddenWordLength(HiddenWordLength);
	ResetIOBuffer();
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)\n\n";
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

void ResetIOBuffer()
{
	std::cin.ignore(INT_MAX, '\n');
	std::cout << std::endl;
}
