#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>
#include <deque>
#include <algorithm>
using namespace std;

static int generateRandomNumber(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);

	int random_number = distrib(gen);
	return random_number;
}
static string toUpperCase(string str) {
	string output = "";
	for (char& c : str) {
		output += toupper(c);
	}
	return output;
}

void playNumberGuessingGame() {
	string user_input;
	int user_answer;
	int correct_answer = generateRandomNumber(1, 50);
	int number_of_guesses = 0;
	bool game_finished = false;

	system("cls");
	cout << "--- Number Guessing Game ---\n";

	while (!game_finished) {
		number_of_guesses++;
		cout << "Guess a number between 1 and 50: \n";

		cin >> user_input;
		if (toUpperCase(user_input) == "QUIT") {
			game_finished = true;
			system("cls");
			break;
		}
		else {
			try {
				user_answer = stoi(user_input);
				if (user_answer > 50) {
					cerr << "Invalid Input \n";
					number_of_guesses--;
				}
				else if (user_answer == correct_answer) {
					cout << "Correct! The answer was " << correct_answer << "! \n";
					cout << "It took you " << number_of_guesses << " tries to guess it! \n";
					cout << "Type \"y\" to play again: \n";

					cin >> user_input;
					if (user_input == "y") {
						playNumberGuessingGame();
						break;
					}
					else {
						game_finished = true;
						system("cls");
						break;
					}
				}
				else if (user_answer > correct_answer) {
					cout << "Wrong, the correct answer is smaller. \n";
				}
				else if (user_answer < correct_answer) {
					cout << "Wrong, the correct answer is bigger. \n";
				}
				else {
					cerr << "Invalid Input \n";
					number_of_guesses--;
				}
			}
			catch (invalid_argument& e) {
				cerr << "Invalid Input \n";
				number_of_guesses--;
			}
		}
		
		
	}
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
			int GAME_WIDTH = 41;
			int GAME_HEIGHT = 29;
			deque<int> gameScreen;
			enum RoadDirection {
				LEFT,
				STRAIGHT,
				RIGHT
			};
			enum RoadDirection mode = STRAIGHT;
			public:
				Display() {
					for (int i = 0; i < GAME_HEIGHT; i++) {
						gameScreen.push_back(10);
					}
				}
				void setUpScreen(DrivingGame::Car c) {
					string display_string;
					int row;
					int xPos = c.getXPos();

					for (int i = 0; i < GAME_HEIGHT; i++) {
						row = gameScreen[i];
						display_string = string(row, '.') + string(21, ' ') + string(20 - row, '.');
						if (i == GAME_HEIGHT - 4) {
							display_string.replace(xPos, 1, 1, '^');
						}
						cout << display_string << "\n";
					}
				}
				bool checkIfHit(DrivingGame::Car c) {
					int next_row = gameScreen.at(GAME_HEIGHT - 5);
					int xPos = c.getXPos();

					return xPos < next_row || xPos > next_row + 20;
				}
				void displayGame(DrivingGame::Car c) {
					string display_string;
					int row;
					int last_row_edge = gameScreen.at(0);
					int xPos = c.getXPos();

					gameScreen.pop_back();

					if (generateRandomNumber(1, 15) == 15) {
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
					
					system("cls");
					for (int i = 0; i < GAME_HEIGHT; i++) {
						row = gameScreen.at(i);
						display_string = string(row, '.') + string(21, ' ') + string(20 - row, '.');
						if (i == GAME_HEIGHT - 4) {
							display_string.replace(xPos, 1, 1, '^');
						}
						cout << display_string << "\n";
					}
				}
		};
};

void playDrivingGame() {
	string user_input;
	DrivingGame::Car car;
	DrivingGame::Display display;
	bool game_finished = false;

	system("cls");
	cout << "--- Forza Horizon -1 ---\n";
	cout << "Get Ready \n";
	Sleep(1000);
	cout << "3\n";
	Sleep(1000);
	cout << "2\n";
	Sleep(1000);
	cout << "1\n";
	Sleep(1000);

	
	display.setUpScreen(car);
	while (!game_finished) {
		if (GetKeyState(VK_LEFT) & 0x8000) {
			car.moveLeft();
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {
			car.moveRight();
		}

		display.displayGame(car);

		if (display.checkIfHit(car)) {
			cout << "Game Over! Type \"y\" to Play Again: \n";

			cin >> user_input;
			if (user_input == "y") {
				playDrivingGame();
				break;
			}
			else {
				game_finished = true;
				system("cls");
				break;
			}
		}
		Sleep(20);
	}
}

void sortWords() {
	string user_input;
	vector<string> sorted_words;
	bool program_finished = false;
	bool word_inserted = false;

	system("cls");
	cout << "--- Sort Words Alphabetically ---\n";
	
	while (!program_finished) {
		word_inserted = false;
		cout << "Type in a Word: \n";

		cin >> user_input;
		user_input = toUpperCase(user_input);
		if (user_input == "QUIT") {
			program_finished = true;
			system("cls");
			break;
		}
		else {
			if (sorted_words.size() < 1) {
				sorted_words.push_back(user_input);
				word_inserted = true;
			}
			else {
				for (string word : sorted_words) {
					bool word_is_after = false;
					word = toUpperCase(word);

					if (user_input == word) {
						sorted_words.insert(find(sorted_words.begin(), sorted_words.end(), word), user_input);
						word_inserted = true;
						break;
					}

					for (int i = 0; i < user_input.size(); i++) {
						
						if ((int)user_input[i] < (int)word[i]) {
							sorted_words.insert(find(sorted_words.begin(), sorted_words.end(), word), user_input);
							word_inserted = true;
							break;
						}
						else if ((int)user_input[i] == (int)word[i]) {
							continue;
						}
						else if ((int)user_input[i] > (int)word[i]) {
							word_is_after = true;
							break;
						}
						
					}

					if (word_inserted) { break; }

					if (word_is_after) { continue; }

					if (user_input.size() < word.size()) {
						sorted_words.insert(find(sorted_words.begin(), sorted_words.end(), word), user_input);
						word_inserted = true;
						break;
					}
				}
				if (!word_inserted) {
					sorted_words.push_back(user_input);
				}
			}
			
			cout << "\n";
			for (string word : sorted_words) {
				cout << word << "\n";
			}
		}
	}
}

int main() {
	string user_input;
	bool program_done = false;

	while (!program_done) {
		cout << "Welcome to the CPP Console App! \n\n";
		cout << "Type in a Number to Select a Program or \"quit\" to Exit the Console \n";
		cout << "(1) Guess the Number \n";
		cout << "(2) Forza Horizon -1 \n";
		cout << "(3) Alphbetically Sort Words \n";

		cin >> user_input;
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
		else if (user_input == "3") {
			sortWords();
		}
		else {
			cerr << "Invalid Input \n";
		}
	}
	cout << "\nThank you for Using the Console App!";
	return 0;
}

