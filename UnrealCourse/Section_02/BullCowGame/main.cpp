#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuess();
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
	cout << "Welcome to Bulls and Cows, a fun word game." << endl;
	cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << endl;
	cout << endl;
	return;
}


void PlayGame()
{
	// loop for the number of turns asking for guesses
	constexpr int TURN_COUNT = 5;
	for (int count = 0; count < TURN_COUNT; count++)
	{
		string Guess = GetGuess();
		// print guess back
		cout << "Your guess was: " << Guess << endl;
		cout << endl;
	}
}


string GetGuess()
{
	// ask for players guess
	cout << "Please take a guess: ";
	string Guess = "";
	getline(cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again? (y/n) ";
	string Response = "";
	getline(cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
