#pragma once

class Arc
{
public:
	void setDistance(int);
	int getDistance();
	void setConnexions(string, string);
	void setConnexionsI(string, string);
	pair<string, string> getConnexions();
private:
	int distance_;
	pair<string, string> connexions_;
};

void Arc::setDistance(int distance)
{
	distance_ = distance;
}

int Arc::getDistance()
{
	return distance_;
}

void Arc::setConnexions(string sommet1, string sommet2)
{
	if (stoi(sommet1) <= stoi(sommet2))
	{
		connexions_.first = sommet1;
		connexions_.second = sommet2;
	}
	else
	{
		connexions_.first = sommet2;
		connexions_.second = sommet1;
	}
}

void Arc::setConnexionsI(string sommet1, string sommet2)
{
	connexions_.first = sommet1;
	connexions_.second = sommet2;

}

pair<string, string> Arc::getConnexions()
{
	return connexions_;
}