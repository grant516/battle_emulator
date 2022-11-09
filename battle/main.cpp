#include <iostream>
#include <string>
#include <fstream>
#include "enemy.h"
#include "player.h"
#include "json.h"

using json = nlohmann::json;
using namespace std;

void menu(Player player, Enemy enemy)
// This Menu will display Enemy and Player HP.
// It will then ask if the user would like to attack.
{
	cout << "\n" << "Opposing " << enemy.getName() << "'s HP : " << enemy.getHP() << endl;
	cout << player.getName() << "'s HP: " << player.getHP() << endl;

	cout << "\n1. Attack the Enemy\n" 
		<< "2. Debuff the Enemy's Attack\n" 
		<< "3. Debuff the Enemy's Speed\n" 
		<< "4. Heal yourself\n" 
		<< "5. Quit the game" << endl;
}

bool gameOverCheck(Player &player, Enemy &enemy)
{
	if (player.getHP() <= 0) {
		cout << "The Enemy was the victor" << endl;
		return true;
	}
	else if (enemy.getHP() <= 0) {
		cout << player.getName() << " was the victor!" << endl;
		return true;
	}
	return false;
}

void enemyTurn(Player &player, Enemy &enemy)
{
	int input = rand() % 4;
	//int input = 4;
	if (input == 1) {
		// Attack
		player.changeHP(enemy.getAttack(), 1);
	}
	else if (input == 2) {
		// debuff player attack
		player.setDebuffAttack();
	}
	else if (input == 3) {
		// debuff player speed
		player.setDebuffSpeed();
	}
	else if (input == 4) {
		// Heal
		enemy.changeHP(-75, 0);
	}
}

void playerTurn(Player &player, Enemy &enemy, string input)
{
	if (input == "1") {
		// Attack
		string moveInput;
		player.displayMoves();
		cin >> moveInput;
		int power = player.getMove(moveInput);
		// TODO add feature to choose the move.
		enemy.changeHP(player.getAttack(), power);
	}
	else if (input == "2") {
		// debuff enemy attack
		enemy.setDebuffAttack();
	}
	else if (input == "3") {
		// debuff enemy speed
		enemy.setDebuffSpeed();
	}
	else if (input == "4") {
		// Heal
		player.changeHP(-75, 0);
	}
}

int main()
{
	srand(time(NULL));

	std::ifstream f("characters.json");
	json data = json::parse(f);


	int playerChar = rand() % 7 + 1;
	int enemyChar = rand() % 7 + 1;

	Player player(data[to_string(playerChar)]);
	Enemy enemy(data[to_string(enemyChar)]);

	string input = "";

	while (input != "5" and !gameOverCheck(player, enemy)) {
		menu(player, enemy);
		cout << "What would you like to do? ";
		cin >> input;

		if (input != "5") {
			// Need a better way to deal with speed ties.
			if (player.getSpeed() >= enemy.getSpeed()) {
				playerTurn(player, enemy, input);
				enemyTurn(player, enemy);
			}
			else if (player.getSpeed() < enemy.getSpeed()) {
				enemyTurn(player, enemy);
				playerTurn(player, enemy, input);
			}
		}

	}

	return 0;
}