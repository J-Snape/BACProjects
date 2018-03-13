#pragma once
#include <string>
using namespace std;

class SommetIngredient
{
public:
	void setId(int);
	int getId();
	void setIngredient(string);
	string getIngredient();
private:
	int id_;
	string ingredient_;
};

void SommetIngredient::setId(int id)
{
	id_ = id;
}

int SommetIngredient::getId()
{
	return id_;
}

void SommetIngredient::setIngredient(string ingredient)
{
	ingredient_ = ingredient;
}

string SommetIngredient::getIngredient()
{
	return ingredient_;
}