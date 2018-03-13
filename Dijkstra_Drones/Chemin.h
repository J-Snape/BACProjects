#pragma once

class Chemin
{
public:
	void insertChemin(int, int);
private:
	vector<pair<int, int>> listeArcsChoisis_;
};

void Chemin::insertChemin(int a, int b)
{
	pair<int, int> p = make_pair(a, b);
	listeArcsChoisis_.push_back(p);
}