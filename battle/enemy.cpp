#include "enemy.h"
#include <iostream>
#include <string>
#include "json.h"

using json = nlohmann::json;
using namespace std;

double debuffRateEnemy = 0.67;

Enemy::Enemy(json data) : name(""), hp(10), speed(10), attack(10), debuffAttack(1), debuffSpeed(1) {
	name = data["name"];
	attack = data["attack"];
	attackSpecial = data["spattack"];
	defense = data["defense"];
	defenseSpecial = data["spdefense"];
	speed = data["speed"];
	hp = data["hp"];
	maxHp = data["hp"];
}

string Enemy::getName() {
	return name;
}

double Enemy::getHP() {
	return hp;
}

double Enemy::getSpeed() {
	return speed * debuffSpeed;
}

double Enemy::getAttack() {
	double value = rand() % 100 + 1;
	if (value < 6.25) {
		cout << name << " attacked, it was a Critical Hit!" << endl;
		return attack * 2;
	}
	else {
		return attack * debuffAttack;
	}
}

void Enemy::setDebuffSpeed() {
	debuffSpeed *= debuffRateEnemy;
	cout << name << "'s speed was lowered." << endl;
}

void Enemy::setDebuffAttack() {
	debuffAttack *= debuffRateEnemy;
	cout << name << "'s attack was lowered." << endl;
}

void Enemy::changeHP(double attack, int power) {
	if (attack < 0) {
		if ((hp - attack) > maxHp) {
			hp = maxHp;
		}
		else {
			hp -= attack;
			cout << "The opposing " << name << " healed " << -attack << "HP!" << endl;
		}
	}
	else {
		double damage = 0;
		damage = ((((2 * 100) / 5) + 2) * power * attack / defense) / 50 + 2;

		hp -= damage;
		cout << name << " took damage!" << endl;
	}
}