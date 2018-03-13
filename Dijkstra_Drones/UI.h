#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class UI
{
public:
	void displayMainMenu();
private:
	void droneMain();
	void recetteMain();
};

void UI::displayMainMenu()
{
	bool quit_token = false;
	char select = ' ';
	while (!quit_token)
	{
		system("cls");
		cout << endl;
		cout << "  **************************************" << endl;
		cout << "  **************************************" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  ***    LOG2810 TP1 - Main Menu     ***" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  ***            Code par:           ***" << endl;
		cout << "  ***       Christopher Nicolae      ***" << endl;
		cout << "  ***           Jared Snape          ***" << endl;
		cout << "  ***          Chi-Huy Trinh         ***" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  **************************************" << endl;
		cout << "  **************************************" << endl;
		cout << endl << endl;
		cout << "               (a) Drones" << endl;
		cout << "               (b) Recettes" << endl;
		cout << "               (c) Quitter" << endl;

		cout << endl << endl << "Entrez votre choix: ";
		cin >> select;


		//Checking input
		switch (select)
		{
		case 'a':
			droneMain();
			break;

		case 'b':
			recetteMain();
			break;

		case 'c':
			quit_token = true;
			cout << "Au revoir!" << endl;
			this_thread::sleep_for(chrono::seconds(1));
			break;

		default:
			cout << "Entree invalide!";
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			break;
		};
	
	}
	
	
}


void UI::droneMain()
{
	bool quit_token = false;
	bool graph_active = false;
	char select = ' ';
	Graphe graph;

	while (!quit_token)
	{
		system("cls");
		cout << endl;
		cout << "  **************************************" << endl;
		cout << "  **************************************" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  ***    LOG2810 TP1 - Drone Menu    ***" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  **************************************" << endl;
		cout << "  **************************************" << endl;
		cout << endl << endl;
		cout << "(a) Mettre a jour la carte" << endl;
		cout << "(b) Determiner le plus court chemin securitaire" << endl;
		cout << "(c) Quitter" << endl;

		cout << endl << endl << "Entrez votre choix: ";
		cin >> select;
		

		
		//Checking input
		switch (select)
		{
		case 'a':
		{
			string filename = "";
			cout << endl << "Entrez le nom de fichier contenant l'information de carte: ";
			cin >> filename;
			cout << "Mise a Jour de la carte..." << endl << endl;

			creerGraphe(filename + ".txt", &graph);
			cout << endl << "Affichage du graphe en cours:" << endl;
			graph.lireGraphe();
			cout << endl;
			graph_active = true;
		}
			break;

		case 'b':
		{
			if (graph_active)
			{
				//variables requises pour le calcul
				string depart;
				string arrivee;
				string poids;
				
				//Pour faciliter l'usage et obtenir les intervalles valides du graphe, on trouve le nombre de sommets dans le graphe importé
				int nbmax = graph.getNbSommets();


				cout << "Entrer le point de depart (1-" << nbmax <<"): ";
				cin >> depart;
				cout << "Entrer le point d'arrivee (1-" << nbmax << "): ";
				cin >> arrivee;
				cout << "Entrer le poids du paquet (plume, moyen, lourd): ";
				cin >> poids;

				graph.plusCourtChemin(poids, depart, arrivee);
			}
			else
			{
				cout << "Erreur: Aucun Graphe actif." << endl;
				cout << "Exectuer \"Mettre a jour la carte\" d'abord" << endl << endl;
				this_thread::sleep_for(chrono::seconds(1));
			}
		}
			break;
		case 'c':
			cout << "Retour au menu principal" << endl << endl;
			quit_token = true;
			break;

		default:
			cout << "Entree invalide!" << endl;
			this_thread::sleep_for(chrono::seconds(1));
			break;
		}
		
		system("pause");
	}
}


void UI::recetteMain()
{
	bool quit_token = false;
	bool graph_active = false;
	char select = ' ';
	Graphe graph;

	while (!quit_token)
	{
		system("cls");
		cout << endl;
		cout << "  **************************************" << endl;
		cout << "  **************************************" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  ***   LOG2810 TP1 - Recette Menu   ***" << endl;
		cout << "  ***                                ***" << endl;
		cout << "  **************************************" << endl;
		cout << "  **************************************" << endl;
		cout << endl << endl;
		cout << "(a) Creer et afficher le graphe des recettes" << endl;
		cout << "(b) Generer et afficher le diagramme de Hasse" << endl;
		cout << "(c) Quitter" << endl;

		cout << endl << endl << "Entrez votre choix: ";
		cin >> select;



		//Checking input
		switch (select)
		{
		case 'a':
		{
			//Creer et afficher graphe des recettes
			string filename = "";
			cout << endl << "Entrez le nom de fichier contenant l'information de carte: ";
			cin >> filename;
			cout << "Mise a Jour de la carte..." << endl << endl;

			creerGrapheOriente(filename + ".txt", &graph);
			cout << endl << "Affichage du graphe en cours:" << endl;
			graph.lireGraphe();
			cout << endl;
			graph_active = true;
		}
		break;

		case 'b':
		{
			if (graph_active)
			{
				//generer Hasse
			}
			else
			{
				cout << "Erreur: Aucun Graphe actif." << endl;
				cout << "Exectuer \"Creer et afficher le graphe des recettes\" d'abord" << endl << endl;
				this_thread::sleep_for(chrono::seconds(1));
			}
		}
		break;
		case 'c':
			cout << "Retour au menu principal" << endl << endl;
			quit_token = true;
			break;

		default:
			cout << "Entree invalide!" << endl;
			this_thread::sleep_for(chrono::seconds(1));
			break;
		}

		system("pause");
	}
}