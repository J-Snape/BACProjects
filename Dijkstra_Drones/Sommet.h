#pragma once
#include <string>
using namespace std;

class Sommet
{
public:
	void setId(string);
	string getId();
	void setChargeur(bool);
	bool getChargeur();
private:
	string id_;
	bool chargeur_;
};

void Sommet::setId(string id)
{
	id_ = id;
}

string Sommet::getId()
{
	return id_;
}

void Sommet::setChargeur(bool chargeur)
{
	chargeur_ = chargeur;
}

bool Sommet::getChargeur()
{
	return chargeur_;
}