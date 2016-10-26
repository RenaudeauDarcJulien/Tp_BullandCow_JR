#pragma once
#include <string>
using namespace std;

struct compteur
{
	int Bulls = 0;
	int Cows = 0;
};

enum class checkstatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class Game
{
public:
	Game(); // constructeur

	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	checkstatus CheckEssaiValide(string) const;
	void Reset();
	compteur TestValidWordCheck(string);
	string GetValidGuess();
	bool Playagain();
	void ShowResultGame();

	void PlayGame();

private:

	int EssaiActuel;
	string MyHiddenWord;
	bool GameIsWon;
	bool IsIsogram(string) const;
	bool IsLowercase(string) const;
};