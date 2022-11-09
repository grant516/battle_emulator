#include "player.h"
#include <iostream>
#include <string>
#include "json.h"

using json = nlohmann::json;
using namespace std;

double debuffRatePlayer = 0.67;

Player::Player(json data) : name(""), hp(10), speed(10), attack(10), debuffAttack(1), debuffSpeed(1){


	name = data["name"];
	attack = data["attack"];
	attackSpecial = data["spattack"];
	defense = data["defense"];
	defenseSpecial = data["spdefense"];
	speed = data["speed"];
	hp = data["hp"];
	maxHp = data["hp"];

	debuffAttack = 1;
	debuffSpeed = 1;

	move1 = data["move1"];
	move2 = data["move2"];
	move3 = data["move3"];
	move4 = data["move4"];
}

string Player::getName() {
	return name;
}
double Player::getHP() {
	return hp;
}
double Player::getSpeed() {
	return speed * debuffSpeed;
	}
double Player::getAttack() {
	double value = rand() % 100 + 1;
	if (value < 6.25) {
		return attack * 2;
		cout << name << " attacked, it was a Critical Hit!" << endl;
	}
	else {
		return attack * debuffAttack;
	}
	}
void Player::setDebuffSpeed() {
	debuffSpeed *= debuffRatePlayer;
	cout << name << "'s speed was lowered." << endl;
	}
void Player::setDebuffAttack() {
	debuffSpeed *= debuffRatePlayer;
	cout << name << "'s attack was lowered." << endl;
	}
void Player::changeHP(double attack, int power) {
	if (attack < 0) {
		if ((hp - attack) > maxHp) {
			hp = maxHp;
		}
		else {
			hp -= attack;
			cout << name << " healed " << -attack << "HP!" << endl;
		}
	}
	else {
		double damage = 0;
		damage = ((((2 * 100) / 5) + 2) * power * attack / defense) / 50 + 2;
		
		hp -= damage;
		cout << name << " took damage!" << endl;
	}
	}

void Player::displayMoves() {
	cout << "1 - " << move1["name"] << endl;
	cout << "2 - " << move2["name"] << endl;
	cout << "3 - " << move3["name"] << endl;
	cout << "4 - " << move4["name"] << endl;
}

int Player::getMove(string move) {
	int power = 0;
	if (move == "1") {
		power = move1["power"];
	}
	else if (move == "2") {
		power = move2["power"];
	}
	else if (move == "3") {
		power = move3["power"];
	}
	else {
		power = move4["power"];
	}

	return power;
}