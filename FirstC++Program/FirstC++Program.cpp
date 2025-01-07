#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>
#include <deque>
using namespace std;

static int generateRandomNumber(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);

	int random_number = distrib(gen);
	return random_number;
}

void playNumberGuessingGame() {
	string user_play_again_input;
	int user_input;
	int answer = generateRandomNumber(1, 50);
	int number_of_guesses = 0;
	bool game_finished = false;

	cout << "\n --Number Guessing Game-- \n";

	while (!game_finished) {
		number_of_guesses++;
		cout << "Guess a number between 1 and 50: \n";

		cin >> user_input;
		if (user_input > 50) {
			cerr << "Invalid Input \n";
			number_of_guesses--;
		}
		else if (user_input == answer) {
			cout << "Correct! The answer was " << answer << "! \n";
			cout << "It took you " << number_of_guesses << " tries to guess it! \n";
			cout << "Type \"y\" to play again \n";

			cin >> user_play_again_input;
			if (user_play_again_input == "y") {
				answer = generateRandomNumber(1, 50);
				number_of_guesses = 0;
				continue;
			}
			else {
				game_finished = true;
				break;
			}
		}
		else if (user_input > answer) {
			cout << "Wrong, the correct answer is smaller. \n";
		}
		else if (user_input < answer) {
			cout << "Wrong, the correct answer is bigger. \n";
		}
		else {
			cerr << "Invalid Input \n";
			number_of_guesses--;
		}
	}
	cout << "\n";
}

class DrivingGame {
	
	public:
		class Car {
			int xPos = 15;
			public:
				int getXPos() {
					return xPos;
				}
				void moveLeft() {
					xPos = max(xPos - 1, 0);
				}
				void moveRight() {
					xPos = min(xPos + 1, 40);
				}
		};
		class Display {
			deque<int> gameScreen;
			enum RoadDirection {
				LEFT,
				STRAIGHT,
				RIGHT
			};
			enum RoadDirection mode = STRAIGHT;
			public:
				Display() {
					for (int i = 0; i < 30; i++) {
						gameScreen.push_back(10);
					}
				}
				void setUpScreen(DrivingGame::Car c) {
					string display_string;
					int row;
					int xPos = c.getXPos();

					for (int i = 0; i < gameScreen.size(); i++) {
						row = gameScreen[i];
						display_string = string(row, '.') + string(21, ' ') + string(20 - row, '.');
						if (i == gameScreen.size() - 4) {
							display_string.replace(xPos, 1, 1, '^');
						}
						cout << display_string << "\n";
					}
				}
				void displayGame(DrivingGame::Car c) {
					string display_string;
					int row;
					int last_row_edge = gameScreen.at(0);
					int xPos = c.getXPos();

					gameScreen.pop_back();

					if (generateRandomNumber(1, 20) == 20) {
						int random_change = generateRandomNumber(0, 1);
						switch (mode) {
							case STRAIGHT:
								if (random_change == 0) {
									mode = LEFT;
								}
								else {
									mode = RIGHT;
								}
								break;
							case LEFT:
								if (random_change == 0) {
									mode = STRAIGHT;
								}
								else {
									mode = RIGHT;
								}
								break;
							case RIGHT:
								if (random_change == 0) {
									mode = LEFT;
								}
								else {
									mode = STRAIGHT;
								}
								break;
						}
					}

					switch (mode) {
						case LEFT:
							gameScreen.push_front(max(last_row_edge - 1, 0));
							last_row_edge = max(last_row_edge - 1, 0);
							break;
						case RIGHT:
							gameScreen.push_front(min(last_row_edge + 1, 17));
							last_row_edge = min(last_row_edge + 1, 17);
							break;
						case STRAIGHT:
							gameScreen.push_front(last_row_edge);
							break;
					}
					

					for (int i = 0; i < gameScreen.size(); i++) {
						row = gameScreen.at(i);
						display_string = string(row, '.') + string(21, ' ') + string(20 - row, '.');
						if (i == gameScreen.size() - 4) {
							display_string.replace(xPos, 1, 1, '^');
						}
						cout << display_string << last_row_edge << "\n";
					}
				}
		};
};

void playDrivingGame() {
	DrivingGame::Car car;
	DrivingGame::Display display;
	bool game_finished = false;
	
	display.setUpScreen(car);
	while (!game_finished) {
		if (GetKeyState(VK_LEFT) & 0x8000) {
			car.moveLeft();
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {
			car.moveRight();
		}
		display.displayGame(car);
		Sleep(10);
	}
}

int main() {
	string user_input;
	bool program_done = false;
	cout << "Welcome to the CPP Console App! \n\n";

	while (!program_done) {
		cout << "Type in a Number to Select a Program or \"quit\" to Exit the Console \n";
		cout << "(1) Guess the Number \n";
		cout << "(2) Forza Horizon -1 \n";

		getline(cin, user_input);
		if (user_input == "quit") { 
			program_done = true;
			break; 
		}
		else if (user_input == "1") {
			playNumberGuessingGame();
		}
		else if (user_input == "2") {
			playDrivingGame();
		}
		else {
			cerr << "Invalid Input";
		}
	}
	cout << "Thank you for using the Console App!";
	return 0;
}

