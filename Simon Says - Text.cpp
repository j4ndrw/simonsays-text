#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <string>
#include <conio.h>

using namespace std;

int nScore = 0;
int nCountdown = 0;

bool bGameOver = false;
bool bYouWin = false;
bool bStartGame = false;

vector<string> vColors;
vector<string> vSequence;

void Ready(); // Get the components ready
void GetAnswer(); // Get input from user containing a [Y/N] answer
void ShowColor(string sColor, string sCode, char cEncode[], char cReset[]); // E.g: "Blue" will be written in the color blue
void Countdown();
void Game();

void Ready()
{
	cout << "Welcome to Simon Says!" << endl << endl;

	cout << "RULES:" << endl;
	cout << "1. When the sequence of colors ends, press the key labeled with the color's initial on your keyboard." << endl << endl;
	cout << "2. Your score is directly proportional to how many colors there are in the sequence." << endl;
	cout << "Example: One color in a sequence = 10 * 1 (10) points. Two colors = 10 * 2. And the list continues." << endl;
	cout << "3. There is no third rule. Just have fun and train your memory :)" << endl << endl;

	cout << "Are you ready to play the game?" << endl;
	cout << "[Y / N]" << endl << endl;

	GetAnswer();
}

void GetAnswer()
{
	char cAnswer;

	bool bAnswerValid = false;

	while (bAnswerValid == false)
	{
		cin >> cAnswer;
		if (cAnswer == 'Y' || cAnswer == 'y')
		{
			bStartGame = true;
			bAnswerValid = true;
		}
		else
			if (cAnswer == 'N' || cAnswer == 'n')
			{
				bStartGame = false;
				bAnswerValid = true;
			}
			else
			{
				cout << "Please enter a valid option: [Y / N]" << endl << endl;
			}
	}
	system("cls");
}

void ShowColor(string sColor, string sCode, char cEncode[], char cReset[])
{
	if (sColor == sCode)
		cout << cEncode << sColor << cReset << endl;
}

void Countdown()
{
	if (bStartGame == true)
	{
		cout << "Alright! The game will start in a few seconds." << endl;
		for (int i = 1; i <= 13; i++)
		{
			this_thread::sleep_for(300ms);
			if (i == 1 || i == 5 || i == 9)
			{
				nCountdown++;
				cout << nCountdown;
			}
			if ((i >= 2 && i <= 4) || (i >= 6 && i <= 8) || (i >= 10 && i <= 12))
				cout << ".";
		}
	}
}

void Game()
{
	char red[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
	char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
	char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
	char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
	char reset[] = { 0x1b, '[', '0', 'm', 0 };

	char cAnswer;
	string sCorrect;

	// Every iteration, add color to sequence (color is random).
	vSequence.push_back(vColors[rand() % 4]); 

	for (int i = 0; i < vSequence.size(); i++)
	{
		ShowColor(vSequence[i], "red", red, reset);
		ShowColor(vSequence[i], "green", green, reset);
		ShowColor(vSequence[i], "blue", blue, reset);
		ShowColor(vSequence[i], "yellow", yellow, reset);
		this_thread::sleep_for(1s);
		system("cls");
	}

	system("cls");

	cout << "Your score so far is: " << nScore << endl;
	cout << "What was the order of the colors?" << endl;

	// If user inputs correct color, add +10 to the score for every color in the sequence picked correctly.
	// If user misses, subtract acquired score in said wave. Game over.
	for (int i = 0; i < vSequence.size(); i++)
	{
		cAnswer = _getch();
		sCorrect = vSequence[i];

		if(cAnswer == sCorrect[0])
		{
			ShowColor(vSequence[i], "red", red, reset);
			ShowColor(vSequence[i], "green", green, reset);
			ShowColor(vSequence[i], "blue", blue, reset);
			ShowColor(vSequence[i], "yellow", yellow, reset);
			if(i == vSequence.size() - 1)
				system("cls");
			nScore += 10;
		}
		else 
		{
			system("cls");
			nScore -= 10 * (vSequence.size() - 1);
			cout << "That's wrong. The correct answer was: " << vSequence[i] << endl;
			cout << "Your score: " << nScore << endl;
			cout << "Game over" << endl << endl;
			bGameOver = true;
			break;
		}
	}
}

int main()
{
	srand(time(NULL));

	// Initialize basic colors.
	vColors.push_back("red");
	vColors.push_back("green");
	vColors.push_back("blue");
	vColors.push_back("yellow");

	Ready();
	Countdown();
	
	system("cls");

	while (bGameOver == false)
	{
		this_thread::sleep_for(2s);
		Game();
	}
}