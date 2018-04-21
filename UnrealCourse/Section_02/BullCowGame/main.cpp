#include <iostream>
#include <string>


void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

// application entry proint
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
	// define word length and print out introduction
	constexpr int WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	// loop for the number of turns asking for guesses
	constexpr int TURN_COUNT = 5;
	for (int count = 0; count < TURN_COUNT; count++)
	{
		std::string Guess = GetGuess();
		// print guess back
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}
}


std::string GetGuess()
{
	// ask for players guess
	std::cout << "Please take a guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	std::string Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
