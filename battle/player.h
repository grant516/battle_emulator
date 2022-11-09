#pragma once

#include <iostream>
#include <string>
#include "json.h"

using json = nlohmann::json;
using namespace std;

class Player
{
private:
	string name;
	double maxHp;
	double hp;
	double speed;
	double attack;
	double attackSpecial;
	double defense;
	double defenseSpecial;
	double debuffAttack;
	double debuffSpeed;

	json move1;
	json move2;
	json move3;
	json move4;
public:
	Player(json data);

	string getName();
	double getHP();
	double getSpeed();
	double getAttack();
	void setDebuffSpeed();
	void setDebuffAttack();
	void changeHP(double attack, int power);
	void displayMoves();
	int getMove(string move);
};