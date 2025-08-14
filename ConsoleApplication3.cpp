#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <windows.h>

using namespace std;

class DiceGame {
protected:
	vector<int> dice{ 1, 2,3,4,5,6 };
	int playerOneNum{};
	int playerTwoNum{};

public:
	std::string playerName;
	DiceGame()
	{
	}

	~DiceGame()
	{
		cout << "+++++ DiceGame memory deleted/freed" << endl;
	}

	void setPlayerOne() {
		playerOneNum = throwDice();
	}

	void setPlayerTwo() {
		playerTwoNum = throwDice();
	}

	int throwDice() {
		resetDice();
		return dice.front();
	}

	void resetDice() {
		random_device rd;
		mt19937 g(rd());
		shuffle(dice.begin(), dice.end(), g);
	}

	string getResult() {
		string message{  };

		if (playerOneNum > playerTwoNum) {
			message = "Player One was the victor: ";
		}
		else if (playerOneNum < playerTwoNum) {
			message = "Player Two was the victor: ";
		}
		else {
			message = "Throws were equal, game was a draw : ";
		}

		return message
			.append(to_string(playerOneNum))
			.append(" : ")
			.append(to_string(playerTwoNum));
	}
};


class PlayerOne {
public:
	shared_ptr<DiceGame> dg;

	// inject the shared instance
	PlayerOne(shared_ptr<DiceGame> sharedDiceInstance) :dg(sharedDiceInstance) {

	}

	void throwDice() {

		dg->setPlayerOne();
	}
};

class PlayerTwo {
public:
	shared_ptr<DiceGame> dg;

	// inject the shared instance
	PlayerTwo(shared_ptr<DiceGame> sharedDiceInstance) :dg(sharedDiceInstance) {

	}

	void throwDice() {
		dg->setPlayerTwo();
	}
};



void runGame() {
	// create a shared instance pointer
	auto dice = make_shared<DiceGame>();



	// Dependency injection. One instance shared amongst many objects
	PlayerOne p1(dice);
	PlayerTwo p2(dice);

	p1.throwDice();
	p2.throwDice();

	cout << dice->getResult() << endl;
}

void clearScreen() {
	// windows only clear screen
	system("cls");
}


int main() {
	char loop = 'y';
	cout << "Get ready...\n";
	Sleep(2000);
	clearScreen();

	do
	{

		runGame();

		cout << "Enter 'y' to Play Again or enter any key to quit ?\n";
		cin >> loop;

		if (loop != 'y') {
			cout << "Bye.\n";
			exit(0);
		}
		else {
			clearScreen();
		}

	} while (true);



}
