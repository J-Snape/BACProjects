#pragma once

class Drone
{
public:
	Drone(string);
	string getType();
	double getBatt();
	void setBatt(double);
	double getRate(string);
	void resetBatt();
	int getNbResets();
	bool getState();
	void setState(bool);
private:
	string type_;
	double batterie_ = 100;
	vector<pair<string, double>> perteBatterie_;
	int nbResets_ = 0;
	bool active_ = true;
};

Drone::Drone(string type)
{
	type_ = type;

	if (type == "3.3a")
	{
		perteBatterie_.push_back(pair<string, int>("plume", 1));
		perteBatterie_.push_back(pair<string, int>("moyen", 2));
		perteBatterie_.push_back(pair<string, int>("lourd", 4));

	}
	else if (type == "5a")
	{
		perteBatterie_.push_back(pair<string, double>("plume", 1));
		perteBatterie_.push_back(pair<string, double>("moyen", 1.5));
		perteBatterie_.push_back(pair<string, double>("lourd", 2.5));
	}
}

string Drone::getType()
{
	return type_;
}

double Drone::getBatt()
{
	return batterie_;
}

void Drone::setBatt(double pertes)
{
	batterie_ -= pertes;
}

double Drone::getRate(string poids)
{
	for (int i = 0; i < perteBatterie_.size(); i++)
	{
		if (perteBatterie_[i].first == poids)
			return perteBatterie_[i].second;
	}
	cout << "Erreur : " << poids << " n'est pas un poids valide." << endl;
	return 0;
}

void Drone::resetBatt()
{
	batterie_ = 100;
	nbResets_++;
}

int Drone::getNbResets()
{
	return nbResets_;
}

bool Drone::getState()
{
	return active_;
}

void Drone::setState(bool state)
{
	active_ = state;
}