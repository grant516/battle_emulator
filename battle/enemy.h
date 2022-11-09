#pragma once

#include <iostream>
#include <string>
#include "json.h"

using json = nlohmann::json;
using namespace std;

class Enemy
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
public:
	Enemy(json data);

	string getName();
	double getHP();
	double getSpeed();
	double getAttack();
	void setDebuffSpeed();
	void setDebuffAttack();
	void changeHP(double attack, int power);

};
