#include "objet.h"
#include<iostream>
#include <time.h>

#include <map>
#define map std::map  

Game::Game() { Reset(); } 

//Permet de Récuperer le Nombre d'essai en cours
int Game::GetCurrentTry() const
{
	return EssaiActuel; 
}
//Recupère la longueur du mot caché
int Game::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}
//Retourne un booleen pour savoir si la partie est gagnée
bool Game::IsGameWon() const 
{ 
	return GameIsWon; 
}

int Game::GetMaxTries() const
{
	map<int, int> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,16 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void Game::Reset()
{
	const string HIDDEN_WORD[10] = { "avion", "avoir", "voiture", "plan", "moteur" };
	//TODO Random Nombre pour pouvoir chosir un mot aléatoire
	srand(time(NULL));
	int ChoixMot = rand() % 4 + 1;

	MyHiddenWord = HIDDEN_WORD[1];
	EssaiActuel = 1;
	GameIsWon = false;
	return;
}

//Verifie si le mot saisi correspond bien au critère attendu
checkstatus Game::CheckEssaiValide(string essai) const
{
	if (!IsIsogram(essai))
	{
		return checkstatus::Not_Isogram;
	}
	else if (!IsLowercase(essai))
	{
		return checkstatus::Not_Lowercase;
	}
	else if (essai.length() != GetHiddenWordLength())
	{
		return checkstatus::Wrong_Length;
	}
	else
	{
		return checkstatus::OK;
	}
}


//Verifie le mot saisi par rapport au mot attendu
compteur Game::TestValidWordCheck(string essai)
{
	compteur compteurJeu;
	EssaiActuel++;
	for (int i = 0; i < MyHiddenWord.length(); i++) {
		
		for (int m = 0; m < MyHiddenWord.length(); m++) {
			
			if (essai[m] == MyHiddenWord[i]) {
				if (i == m) {
					compteurJeu.Bulls++;
				}
				else {
					compteurJeu.Cows++;
				}
			}
		}
	}
	if (compteurJeu.Bulls == MyHiddenWord.length()) {
		GameIsWon = true;
	}
	else
	{
		GameIsWon = false;
	}
	return compteurJeu;
}

//Retourne un bool pour savoir si le mot est un isogram
bool Game::IsIsogram(string mot) const
{
	if (mot.length() <= 1) { return true; }

	map<char, bool> lettres; 
	for (auto lettre : mot) 	
	{
		lettre = tolower(lettre); 
		if (lettres[lettre]) {
			return false; 
		}
		else {
			lettres[lettre] = true;
		}
	}

	return true; 
}
//Retourne un bool pour savoir si le mot est en minuscule
bool Game::IsLowercase(string mot) const
{
	for (auto lettre : mot)
	{
		if (!islower(lettre))
		{
			return false;
		}
	}
	return true;
}

//Verifie chaque statue et l'affiche au joueur
string Game::GetValidGuess()
{
	Game game;
	string essai = " ";
	checkstatus Statue = checkstatus::Invalid_Status;
	do {

		cout << "essai " << EssaiActuel << " sur " << game.GetMaxTries();
		cout << ". Entrer votre mot: ";
		getline(std::cin, essai);

		Statue = game.CheckEssaiValide(essai);
		switch (Statue) {
		case checkstatus::Wrong_Length:
			cout << "Veuillez entrer un mot de " << game.GetHiddenWordLength() << " lettre de long.\n\n";
			break;
		case checkstatus::Not_Isogram:
			cout << "Veuillez entrer un mot qui n'a pas deux fois la même lettre.\n\n";
			break;
		case checkstatus::Not_Lowercase:
			cout << "Veuillez entrer que des lettres en minuscules.\n\n";
			break;
		default:
			break;
		}
	} while (Statue != checkstatus::OK);
	return essai;
}
// Demande à l'utilisateur si le joueur veut rejouer
bool Game::Playagain()
{
	cout << "Voulez vous rejouez (o/n)? ";
	string reponse;
	getline(cin, reponse);
	if (reponse == "o" || reponse == "O")
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Affiche a l'utilisateur si il a gagné ou perdu
void Game::ShowResultGame()
{
	if (IsGameWon())
	{
		cout << "Gagne ! \n";
	}
	else
	{
		cout << "Perdu !\n";
	}
}


void Game::PlayGame()
{
	Reset();
	//Boucle 
	while (!IsGameWon() && GetCurrentTry() <= GetMaxTries()) {
		compteur compteurJeu = TestValidWordCheck(GetValidGuess());

		cout << "Bulls (Bonne lettre et au bonne endroit) = " << compteurJeu.Bulls << "\n";
		cout << "Cows (Bonne lettre et au mauvaise endroit) = " << compteurJeu.Cows << "\n\n";

	}
	ShowResultGame();
}