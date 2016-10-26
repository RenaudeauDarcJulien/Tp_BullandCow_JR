#include<iostream>
#include <string>
#include "objet.h"

using namespace std;

Game game; 
int main()
{
	bool ChoixRejouer = false;
	do {
		cout << "Jeu de Bull and Cow \n";
		cout << "Devinne le mot de " << game.GetHiddenWordLength();
		cout << " lettres qui est un isogramme";
		cout << std::endl;
		

		game.PlayGame();
		ChoixRejouer = game.Playagain();
		
	} while (ChoixRejouer);

	return 0; 
	//Commentaire test GIT
}


