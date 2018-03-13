#pragma once
#include <vector>
#include <list>
#include <stack>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <string>
#include "Sommet.h"
#include "Arc.h"
#include "Drone.h"
#include "Chemin.h"
#include "SommetIngredient.h"

ifstream input;

class Graphe
{
public:
	//Fonctions de base pour creer le graphe
	void addArc(Arc);
	void addArcI(Arc arc);
	void addSommet(Sommet);
	void addSommetI(SommetIngredient sommet);
	void remSommet(string);
	int hasSommet(string);
	int hasSommetI(int id);
	int hasArc(string, string);
	int hasArcI(string, string);

	//Fonction servant a retourner une liste de voisins d'un sommet
	vector<pair<Sommet, int>> getVoisins(Sommet);
	//Fonction servant a retourner une liste de voisins d'un sommet parmi un vecteur donne
	vector<pair<Sommet, int>>getVoisins(vector<pair<Sommet, int>>*, Sommet);

	//Fonction qui utilise l'algorithme de Dijkstra pour determiner le chemin le plus court entre deux points
	//Utilise le premier parametre string pour determiner la faisabilite de l'utilisation d'un drone moins
	//autonome et dispendieux.
	void plusCourtChemin(string, string, string);
	
	//FOnction pour générer le diagramme de Hasse
	void genererHasse();

	//Fonction pour trouver un Sommet specifique dans un vecteur a l'aide de son id
	pair<Sommet, int> searchForSommet(vector<pair<Sommet, int>>*, string);

	//Fonction qui teste si le Sommet specifie par le string existe dans le vecteur donne
	bool hasSommetIn(vector<pair<Sommet, int>>*, string);

	//Fonction qui enleve un sommet specifie par le string d'un vecteur donne
	//La valeur de retour est le sommet enleve
	pair<Sommet, int> removeSommetVec(vector<pair<Sommet, int>>*, string);

	//Fonction qui permet de modifier la valeur de distance associee au sommet donne par le string
	void setSommetDistance(vector<pair<Sommet, int>>*, string, int);

	//Fonction qui retourne l'index d'un sommet dans le vecteur donne, s'il y a lieu
	int trouverSommetDsPrec(vector<pair<Sommet, Sommet>>*, string);

	//Fonction pour lire le contenu du graphe
	void lireGraphe();

	//Fonctions pour afficher le resultat de la methode plusCourtChemin
	void Graphe::afficheReussite(Drone*, Drone*, vector<pair<Sommet, int>>*, int);
	void Graphe::afficheEchec(Drone*, vector<pair<Sommet, int>>*);
	void Graphe::afficheEchecCritique(string, string);

	//Affiche le nombre de sommets dans le graphe
	int getNbSommets();
	int getNbSommetsI();

	bool idDone_ = false;

private:
	//Liste "maitre" des arcs et sommets
	vector<Arc> listeArcs_;
	vector<Sommet> listeSommets_;
	vector<pair<int, string>> listeSommetsI_;
};

/*******************************************
	Methodes de classe Graphe
*******************************************/
void Graphe::addSommet(Sommet sommet)
{
	if(this->hasSommet(sommet.getId()) < 0)
		listeSommets_.push_back(sommet);
}

void Graphe::addSommetI(SommetIngredient sommet)
{
	if (this->hasSommetI(sommet.getId()) < 0)
	{
		pair<int, string> p (sommet.getId(), sommet.getIngredient());
		listeSommetsI_.push_back(p);
	}
}

int Graphe::getNbSommets()
{
	return listeSommets_.size();
}

int Graphe::getNbSommetsI()
{
	return listeSommetsI_.size();
}

void Graphe::remSommet(string id)
{
	int index = this->hasSommet(id);
	if (index != -1)
		listeSommets_.erase(listeSommets_.begin() + index);

	for (int i = 0; i < listeArcs_.size(); i++)
	{
		if (listeArcs_[i].getConnexions().first == id || listeArcs_[i].getConnexions().second == id)
			listeArcs_.erase(listeArcs_.begin() + i);
	}
}

void Graphe::addArc(Arc arc)
{
	if (this->hasArc(arc.getConnexions().first, arc.getConnexions().second) < 0)
		listeArcs_.push_back(arc);
}

void Graphe::addArcI(Arc arc)
{
	if (this->hasArcI(arc.getConnexions().first, arc.getConnexions().second) < 0)
		listeArcs_.push_back(arc);
}

int Graphe::hasSommet(string id)
{
	for (int i = 0; i < listeSommets_.size(); i++)
	{
		if (listeSommets_[i].getId() == id)
			return i;
	}

	return -1;
}

int Graphe::hasSommetI(int id)
{
	for (std::vector<pair<int, string>>::iterator it = listeSommetsI_.begin(); it != listeSommetsI_.end(); ++it)
		if (it->first == id)
			return 1;
	return -1;
}

int Graphe::hasArc(string sommet1, string sommet2)
{
	if (stoi(sommet1) > stoi(sommet2))
	{
		string tmp = sommet1;
		sommet1 = sommet2;
		sommet2 = tmp;
	}

	for (int i = 0; i < listeArcs_.size(); i++)
	{
		if (listeArcs_[i].getConnexions().first == sommet1 && listeArcs_[i].getConnexions().second == sommet2)
			return i;
	}
	return -1;
}

int Graphe::hasArcI(string sommet1, string sommet2)
{
	for (int i = 0; i < listeArcs_.size(); i++)
	{
		if (listeArcs_[i].getConnexions().first == sommet1 && listeArcs_[i].getConnexions().second == sommet2)
			return i;
	}
	return -1;
}


vector<pair<Sommet, int>> Graphe::getVoisins(Sommet sommet)
{
	vector<pair<Sommet, int>> voisins;
	for (int i = 0; i < listeArcs_.size(); i++)
	{
		if (listeArcs_[i].getConnexions().first == sommet.getId())
			voisins.push_back(pair<Sommet, int>(listeSommets_[this->hasSommet(listeArcs_[i].getConnexions().second)], listeArcs_[i].getDistance()));
		else if (listeArcs_[i].getConnexions().second == sommet.getId())
			voisins.push_back(pair<Sommet, int>(listeSommets_[this->hasSommet(listeArcs_[i].getConnexions().first)], listeArcs_[i].getDistance()));
	}
	return voisins;
}

vector<pair<Sommet, int>> Graphe::getVoisins(vector<pair<Sommet, int>>* vec, Sommet sommet)
{
	vector<pair<Sommet, int>> voisins;
	for (int i = 0; i < listeArcs_.size(); i++)
	{
		if (listeArcs_[i].getConnexions().first == sommet.getId() && hasSommetIn(vec, listeArcs_[i].getConnexions().second))
			voisins.push_back(pair<Sommet, int>(listeSommets_[this->hasSommet(listeArcs_[i].getConnexions().second)], listeArcs_[i].getDistance()));
		else if (listeArcs_[i].getConnexions().second == sommet.getId() && hasSommetIn(vec, listeArcs_[i].getConnexions().first))
			voisins.push_back(pair<Sommet, int>(listeSommets_[this->hasSommet(listeArcs_[i].getConnexions().first)], listeArcs_[i].getDistance()));
	}
	return voisins;
}

void Graphe::lireGraphe()
{
	vector<pair<Sommet, int>> connexions_sommet;
	for (int i = 0; i < listeSommets_.size(); i++)
	{
		cout << "(" << listeSommets_[i].getId() << ", ";
		this_thread::sleep_for(chrono::milliseconds(50));
		connexions_sommet = getVoisins(listeSommets_[i]);

		for (int j = 0; j < connexions_sommet.size(); j++)
		{
			cout << "(" << connexions_sommet[j].first.getId() << ", " << connexions_sommet[j].second << ")";
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		cout << ")" << endl;
	}
		
}

bool Graphe::hasSommetIn(vector<pair<Sommet, int>>* vec, string id)
{
	for (pair<Sommet, int> somm : *vec)
	{
		if (somm.first.getId() == id)
			return true;
	}
	return false;
}

pair<Sommet, int> Graphe::removeSommetVec(vector<pair<Sommet, int>>* vec, string id)
{
	pair<Sommet, int> sommetRetour;
	int emplacement = numeric_limits<int>::max();

	for (int i = 0; i < vec->size(); i++)
	{
		if (vec->at(i).first.getId() == id)
		{
			sommetRetour = vec->at(i);
			emplacement = i;
		}
	}

	if (emplacement < numeric_limits<int>::max())
	{
		vec->erase(vec->begin() + emplacement);
	}

	return sommetRetour;
}

pair<Sommet, int> Graphe::searchForSommet(vector<pair<Sommet, int>>* vec, string id)
{
	for (pair<Sommet, int> somm : *vec)
	{
		if (somm.first.getId() == id)
			return somm;
	}
	pair<Sommet, int> out;
	return out;
}

void Graphe::setSommetDistance(vector<pair<Sommet, int>>* vec, string sommetId, int distance)
{
	for (int i = 0; i < vec->size(); i++)
	{
		if (vec->at(i).first.getId() == sommetId)
		{
			vec->at(i).second = distance;
		}
	}
}

int Graphe::trouverSommetDsPrec(vector<pair<Sommet, Sommet>>* vec, string id)
{
	for (int i = 0; i < vec->size(); i++)
	{
		if (vec->at(i).first.getId() == id)
			return i;
	}
	return -1;
}


void Graphe::plusCourtChemin(string poids, string depart, string arrive)
{
	//Creation/initialization de variables
	vector<pair<Sommet, int>> distancesTentSommetsNonVisites;
	vector<pair<Sommet, Sommet>> sommetsPrec;
	vector<pair<Sommet, int>> distancesSommetsVoisins;
	pair<Sommet, int> currentSomm;
	int plusPetiteDistanceTent = numeric_limits<int>::max();

	//Structures a utiliser pour determiner le passage du drone
	vector<pair<Sommet, int>> distancesFinales;
	vector<pair<Sommet, int>> trajet;
	
	//Initialization des listes de sommets initiales
	for (Sommet somm : listeSommets_)
	{
		pair<Sommet, int> tmpPair;
		tmpPair.first = somm;
		if (tmpPair.first.getId() != depart)
		{
			tmpPair.second = numeric_limits<int>::max();
			distancesTentSommetsNonVisites.push_back(tmpPair);
		}
		else
		{
			tmpPair.second = 0;
			currentSomm = tmpPair;
		}
		
	}
	
	if (this->hasSommet(depart) >= 0 && this->hasSommet(arrive) >= 0)
	{
		//Tant qu'il reste encore des sommets non visites
		while (!distancesTentSommetsNonVisites.empty())
		{
			//
			distancesSommetsVoisins = getVoisins(&distancesTentSommetsNonVisites, currentSomm.first);

			int distanceAlt = 0;
			pair<Sommet, int> plusPetitVoisin;
			plusPetiteDistanceTent = numeric_limits<int>::max();

			for (pair<Sommet, int> somm : distancesSommetsVoisins)
			{
				distanceAlt = currentSomm.second + somm.second;

				if (distanceAlt < searchForSommet(&distancesTentSommetsNonVisites, somm.first.getId()).second)
				{
					setSommetDistance(&distancesTentSommetsNonVisites, somm.first.getId(), distanceAlt);

					if (trouverSommetDsPrec(&sommetsPrec, somm.first.getId()) < 0)
						sommetsPrec.push_back(pair<Sommet, Sommet>(somm.first, currentSomm.first));
					else
						sommetsPrec[trouverSommetDsPrec(&sommetsPrec, somm.first.getId())].second = currentSomm.first;
				}
			}

			distancesFinales.push_back(removeSommetVec(&distancesTentSommetsNonVisites, currentSomm.first.getId()));

			for (pair<Sommet, int> somm : distancesTentSommetsNonVisites)
			{
				if (searchForSommet(&distancesTentSommetsNonVisites, somm.first.getId()).second < plusPetiteDistanceTent)
				{
					plusPetitVoisin = searchForSommet(&distancesTentSommetsNonVisites, somm.first.getId());
					plusPetiteDistanceTent = plusPetitVoisin.second;
				}
			}

			int finTrouveDsPrec = trouverSommetDsPrec(&sommetsPrec, arrive);
			pair<Sommet, int> finTrouveDsTent = searchForSommet(&distancesTentSommetsNonVisites, arrive);


			if (finTrouveDsPrec >= 0 && !(finTrouveDsTent.first.getId() == arrive))
			{
				Sommet prochain = sommetsPrec[trouverSommetDsPrec(&sommetsPrec, arrive)].first;
				int aEliminer = 0;
				bool fini = false;

				while (!sommetsPrec.empty() && !fini)
				{
					if (prochain.getId() != depart)
					{
						aEliminer = trouverSommetDsPrec(&sommetsPrec, prochain.getId());
						trajet.push_back(pair<Sommet, int>(sommetsPrec[aEliminer].first, searchForSommet(&distancesFinales, prochain.getId()).second));
						prochain = sommetsPrec[trouverSommetDsPrec(&sommetsPrec, prochain.getId())].second;

						sommetsPrec.erase(sommetsPrec.begin() + aEliminer);
					}
					else
					{
						trajet.push_back(pair<Sommet, int>(listeSommets_[this->hasSommet(depart)], searchForSommet(&distancesFinales, depart).second));
						fini = true;
					}
				}
			}

			currentSomm = plusPetitVoisin;
		}

		int tempsTotal = 0;
		bool trajetComplete = true;

		Drone drone3("3.3a");
		Drone drone5("5a");

		double perteDrone3 = drone3.getRate(poids);

		if (perteDrone3 != 0)
		{
			double perteDrone5 = drone5.getRate(poids);

			for (int i = trajet.size() - 1; i >= 0; i--)
			{
				if (drone3.getState() || drone5.getState())
				{
					drone3.setBatt(perteDrone3 * (trajet[i].second - tempsTotal));
					drone5.setBatt(perteDrone5 * (trajet[i].second - tempsTotal));
					tempsTotal = trajet[i].second;

					if (trajet[i].first.getChargeur() && drone3.getBatt() < 100 && trajet[i].first.getId() != arrive)
						drone3.resetBatt();

					if (trajet[i].first.getChargeur() && drone5.getBatt() < 100 && trajet[i].first.getId() != arrive)
						drone5.resetBatt();

					if (drone3.getBatt() <= 20)
						drone3.setState(false);

					if (drone5.getBatt() <= 20)
						drone5.setState(false);
				}
			}
		}
		else
		{
			return;
		}

		if (drone3.getState())
			tempsTotal += drone3.getNbResets() * 20;
		else if (drone5.getState())
			tempsTotal += drone3.getNbResets() * 20;
		else
			trajetComplete = false;

		if (trajetComplete)
			afficheReussite(&drone3, &drone5, &trajet, tempsTotal);
		else
			afficheEchec(&drone5, &trajet);
	}
	else
		afficheEchecCritique(depart, arrive);
}

void Graphe::genererHasse()
{
	/*Chemin** matriceChemins = new Chemin*[this->getNbSommetsI()];
	for (int i = 0; i < this->getNbSommetsI(); i++)
		matriceChemins[i] = new Chemin[this->getNbSommetsI()];

	for (vector<Arc>::iterator it = listeArcs_.begin(); it != listeArcs_.end(); ++it)
	{
		int x = stoi(it->getConnexions().first) - 1;
		int y = stoi(it->getConnexions().second) - 1;
		matriceChemins[x][y].insertChemin(stoi(it->getConnexions().first), stoi(it->getConnexions().second));
	}*/


}


/**********************************************************************
	Methodes reliees au graphe mais ne faisant pas parti de la classe
**********************************************************************/
void creerGraphe(string nomFichier, Graphe* graph)
{
	if (!input.is_open())
	{
		//Ouvrir le fichier s'il n'est pas ouvert
		input.open(nomFichier, ifstream::in);
		if (!input.is_open())
		{
			cout << "Fichier introuvable: " << nomFichier << endl << endl;
			this_thread::sleep_for(chrono::seconds(2));
			
		}
		else
		{
			cout << "Fichier ouvert avec succes" << endl << endl;
		}
	}

	string line;
	getline(input, line);

	//Les sommets dans le fichier a lire sont characterises par des lignes de 3 ou 4 char
	//Si on creait plus de 100 sommets, il faudrait modifier l'algo
	if (line.length() <= 4 && line.length() != 0)
	{
		Sommet sommet;
		//Trouver l'indice de ligne ou les valeurs sont separes
		int index = line.find(',', 0);

		//Isoler les composantes du sommet
		sommet.setId(line.substr(0, index));
		sommet.setChargeur(stoi(line.substr(index + 1, line.length() - index)));

		//Ajouter le sommet au graphe
		graph->addSommet(sommet);
		//Appel recursif
		creerGraphe(nomFichier, graph);
	}
	//Les arcs dans le fichier ont toujours plus de 4 char
	else if (line.length() > 4)
	{
		Arc arc;
		//Trouver les indices de ligne ou les valeurs sont separes
		int index1 = line.find(',', 0);
		int index2 = line.find(',', index1+1);

		//Isoler les composantes de l'arc
		arc.setConnexions(line.substr(0, index1), line.substr(index1 + 1, index2-index1-1));
		arc.setDistance(stoi(line.substr(index2 + 1, line.length() - index2)));

		//Ajouter l'arc au graphe
		graph->addArc(arc);
		//Appel recursif
		creerGraphe(nomFichier, graph);
	}
	else if (input.eof())
	{
		//Close le fichier
		input.close();
	}
	else if (line.length() < 1 && !input.is_open())
	{
		return;
	}
	else if (line.length() < 1)
	{
		creerGraphe(nomFichier, graph);
	}
	
}

void creerGrapheOriente(string nomFichier, Graphe* graph)
{
	if (!input.is_open())
	{
		//Ouvrir le fichier s'il n'est pas ouvert
		input.open(nomFichier, ifstream::in);
		if (!input.is_open())
		{
			cout << "Fichier introuvable: " << nomFichier << endl << endl;
			this_thread::sleep_for(chrono::seconds(2));
			
		}
		else
		{
			cout << "Fichier ouvert avec succes" << endl << endl;
		}
	}

	string line;
	getline(input, line);

	if (line.length() == 0)
	{
		if (input.eof())
		{
			//Close le fichier
			input.close();
			return;
		}
		graph->idDone_ = true;
		creerGrapheOriente(nomFichier, graph);
	}
	else if (graph->idDone_ == false)
	{
		SommetIngredient sommetI;
		//Trouver l'indice de ligne ou les valeurs sont separes
		int index = line.find(',', 0);

		//Isoler les composantes du sommet
		sommetI.setId(stoi(line.substr(0, index)));
		sommetI.setIngredient(line.substr(index + 1, line.length() - index));

		//Ajouter le sommet au graphe
		graph->addSommetI(sommetI);
		//Appel recursif
		creerGrapheOriente(nomFichier, graph);
	}
	else if(graph->idDone_ == true)
	{
		Arc arc;
		//Trouver les indices de ligne ou les valeurs sont separes
		int index1 = line.find(',', 0);
		int index2 = line.find(',', index1 + 1);

		//Isoler les composantes de l'arc
		arc.setConnexionsI(line.substr(0, index1), line.substr(index1 + 1, index2-index1-1));
		arc.setDistance(0);

		//Ajouter l'arc au graphe
		graph->addArcI(arc);
		//Appel recursif
		creerGrapheOriente(nomFichier, graph);
	}
	else if (line.length() < 1 && !input.is_open())
	{
		return;
	}
	
}


void Graphe::afficheReussite(Drone* drone3, Drone* drone5, vector<pair<Sommet, int>>* trajet, int tempsTotal)
{
	cout << endl << "Plus court chemin trouve! : ";

	for (int i = trajet->size() - 1; i >= 0; i--)
	{
		cout << trajet->at(i).first.getId();

		if (i == 0)
			cout << endl;
		else
			cout << " -> ";
	}

	cout << "Temps total du parcours : " << tempsTotal << endl;
	cout << "Type de drone utilise : ";

	if (drone3->getState())
		cout << drone3->getType() << endl << "Batterie restante : " << drone3->getBatt() << endl;
	else if (drone5->getState())
		cout << drone5->getType() << endl << "Batterie restante : " << drone5->getBatt() << endl;
}

void Graphe::afficheEchec(Drone* drone5, vector<pair<Sommet, int>>* trajet)
{
	cout << endl << "Aucun chemin trouve!" << endl;

	cout << "En raison de : ";

	if (trajet->empty())
	{
		cout << "Trajet infaisable!" << endl;
	}
	else if (!drone5->getState())
	{
		cout << "Aucun drone n'est en mesure d'effectuer ce passage." << endl;
		cout << "Verifiez le poids du paquet." << endl;
	}
}

void Graphe::afficheEchecCritique(string depart, string arrive)
{
	cout << endl << "Erreur critique! : " << endl;

	if (this->hasSommet(depart) < 0)
	{
		cout << "Le point de depart n'existe pas dans ce graphe!" << endl;
	}

	if(this->hasSommet(arrive) < 0)
	{
		cout << "Le point d'arrive n'existe pas dans ce graphe!" << endl;
	}
}