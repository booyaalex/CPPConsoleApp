#include <iostream>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>
#include <deque>
#include <algorithm>
#include <map>
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

static void playNumberGuessingGame() {
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
			deque<int> game_screen;
			enum RoadDirection {
				LEFT,
				STRAIGHT,
				RIGHT
			};
			enum RoadDirection mode = STRAIGHT;
			public:
				Display() {
					for (int i = 0; i < GAME_HEIGHT; i++) {
						game_screen.push_back(10);
					}
				}
				void setUpScreen(DrivingGame::Car c) {
					string display_string;
					int row;
					int xPos = c.getXPos();

					for (int i = 0; i < GAME_HEIGHT; i++) {
						row = game_screen[i];
						display_string = string(row, '.') + string(21, ' ') + string(20 - row, '.');
						if (i == GAME_HEIGHT - 4) {
							display_string.replace(xPos, 1, 1, '^');
						}
						cout << display_string << "\n";
					}
				}
				bool checkIfHit(DrivingGame::Car c) {
					int next_row = game_screen.at(GAME_HEIGHT - 5);
					int xPos = c.getXPos();

					return xPos < next_row || xPos > next_row + 20;
				}
				void displayGame(DrivingGame::Car c) {
					string display_string;
					int row;
					int last_row_edge = game_screen.at(0);
					int xPos = c.getXPos();

					game_screen.pop_back();

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
							game_screen.push_front(max(last_row_edge - 1, 0));
							last_row_edge = max(last_row_edge - 1, 0);
							break;
						case RIGHT:
							game_screen.push_front(min(last_row_edge + 1, 17));
							last_row_edge = min(last_row_edge + 1, 17);
							break;
						case STRAIGHT:
							game_screen.push_front(last_row_edge);
							break;
					}
					
					system("cls");
					for (int i = 0; i < GAME_HEIGHT; i++) {
						row = game_screen.at(i);
						display_string = string(row, '.') + string(21, ' ') + string(20 - row, '.');
						if (i == GAME_HEIGHT - 4) {
							display_string.replace(xPos, 1, 1, '^');
						}
						cout << display_string << "\n";
					}
				}
		};
};

static void playDrivingGame() {
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

static void sortWords() {
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

class TicTacToeGame {
	string user_input;
	int total_moves = 0;
	int game_board[3][3] = {
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 }
	};
	bool game_finished = false;
	map<int, string> game_markers = { {0, " "}, {1, "X"}, {2, "O"} };

	void displayTicTacToeBoard() {
		system("cls");

		cout << "+---+---+---+\n";
		cout << "| " + game_markers[game_board[0][0]] + " | " + game_markers[game_board[0][1]] + " | " + game_markers[game_board[0][2]] + " |\n";
		cout << "+---+---+---+\n";
		cout << "| " + game_markers[game_board[1][0]] + " | " + game_markers[game_board[1][1]] + " | " + game_markers[game_board[1][2]] + " |\n";
		cout << "+---+---+---+\n";
		cout << "| " + game_markers[game_board[2][0]] + " | " + game_markers[game_board[2][1]] + " | " + game_markers[game_board[2][2]] + " |\n";
		cout << "+---+---+---+\n\n";

		cout << "Type a Number to Play:\n";
	}
	int checkIfWin() {
		int who_won = 0;

		if (total_moves > 8) {
			return 3;
		}

		// Vertical
		for (int r = 0; r < 3; r++) {
			if (game_board[0][r] == game_board[1][r] && game_board[0][r] == game_board[2][r] && game_board[0][r] != 0) {
				who_won = game_board[0][r];
			}
		}

		// Horizontal
		for (int c = 0; c < 3; c++) {
			if (game_board[c][0] == game_board[c][1] && game_board[c][0] == game_board[c][2] && game_board[c][0] != 0) {
				who_won = game_board[c][0];
			}
		}

		// Diagonal
		if (game_board[0][0] == game_board[1][1] && game_board[0][0] == game_board[2][2] && game_board[0][0] != 0) {
			who_won = game_board[0][0];
		}
		if (game_board[2][0] == game_board[1][1] && game_board[2][0] == game_board[0][2] && game_board[2][0] != 0) {
			who_won = game_board[2][0];
		}

		return who_won;
	}
	void computersTurn() {
		vector<int> open_squares = {};

		if (game_board[1][1] == 0) {
			game_board[1][1] = 2;
			total_moves++;
			return;
		}

		for (int i = 0; i < 9; i++) {
			if (game_board[(int)floor(i / 3)][i - 3 * (int)floor(i / 3)] == 0) {
				open_squares.push_back(i);
			}
		}

		int pos = open_squares.at(generateRandomNumber(0, open_squares.size() - 1));
		cout << pos;
		game_board[(int)floor(pos / 3)][pos - 3 * (int)floor(pos / 3)] = 2;
		total_moves++;
	}
	void endGame() {
		displayTicTacToeBoard();

		if (checkIfWin() == 1) {
			cout << "Player Wins!\n";
		}
		else if (checkIfWin() == 2) {
			cout << "Computer Wins!\n";
		}
		else {
			cout << "The Game is Tied!\n";
		}

		cout << "Type \"y\" to play again: \n";

		cin >> user_input;
		if (toUpperCase(user_input) == "Y") {
			total_moves = 0;
			for (int i = 0; i < 9; i++) {
				game_board[(int)floor(i / 3)][i - 3 * (int)floor(i / 3)] = 0;
			}
			playTicTacToe();
		}
		else {
			game_finished = true;
			system("cls");
		}
	}

	public:
		void playTicTacToe() {
			system("cls");
			cout << "--- Tic Tac Toe ---\n\n";

			cout << "+---+---+---+\n";
			cout << "| 1 | 2 | 3 |\n";
			cout << "+---+---+---+\n";
			cout << "| 4 | 5 | 6 |\n";
			cout << "+---+---+---+\n";
			cout << "| 7 | 8 | 9 |\n";
			cout << "+---+---+---+\n\n";

			cout << "Type a Number to Play:\n";

			while (!game_finished) {
				cin >> user_input;
				user_input = toUpperCase(user_input);
				if (user_input == "QUIT") {
					game_finished = true;
					system("cls");
					break;
				}

				try {
					int pos = stoi(user_input);
					if (pos < 1 || pos > 9) {
						cerr << "Invalid Input\n";
						continue;
					}

					pos--;
					if (game_board[(int)floor(pos / 3)][pos - 3 * (int)floor(pos / 3)] != 0) {
						cout << "Square is Already Taken, Pick Another:\n";
						continue;
					}
					game_board[(int)floor(pos / 3)][pos - 3 * (int)floor(pos / 3)] = 1;
					total_moves++;
				}
				catch (invalid_argument& e) {
					cerr << "Invalid Input\n";
					continue;
				}
				
				if (checkIfWin() != 0) {
					endGame();
				}

				computersTurn();

				if (checkIfWin() != 0) {
					endGame();
				}

				displayTicTacToeBoard();
			}
		}
};

class HangmanGame {
	string user_input;
	string correct_word;
	string available_words[20] = { "BACON", "SUNSHINE", "DIRT", "CONFESS", "IDLE", "OWL", "JUMPS", "DUCK", "GOOSE", "KITTY", "APPLE", "POPCORN", "PRIME", "SPIRIT", "CONSOLE", "FOURTY", "GUESS", "SOURCE", "KITCHEN", "SPOON" };
	string body_parts[6] = { " ", " ", " ", " ", " ", " " };
	int wrong_guesses;
	bool game_won = false;
	bool game_finished = false;
	bool letters_found[26] = {};

	void setupGame() {
		wrong_guesses = 0;
		game_won = false;

		for (int i = 0; i < 6; i++) {
			body_parts[i] = " ";
		}

		for (int i = 0; i < 26; i++) {
			letters_found[i] = false;
		}

		correct_word = available_words[generateRandomNumber(0, 19)];
	}

	void addToHangman() {
		switch (++wrong_guesses) {
			case 1:
				body_parts[0] = "O";
				break;
			case 2:
				body_parts[1] = "|";
				break;
			case 3:
				body_parts[2] = "/";
				break;
			case 4:
				body_parts[3] = "\\";
				break;
			case 5:
				body_parts[4] = "/";
				break;
			case 6:
				body_parts[5] = "\\";
				break;
		}
	}

	void guessWord() {
		if (user_input != correct_word) {
			cout << "That's the Wrong Word!\n";
			addToHangman();
			return;
		}

		for (char c : correct_word) {
			letters_found[(int)c - 65] = true;
		}
		game_won = true;
	}

	void guessLetter() {
		if (letters_found[(int)user_input[0] - 65]) {
			cerr << "You Already Guessed This Letter!\n";
			return;
		}
		letters_found[(int)user_input[0] - 65] = true;
		if (correct_word.find(user_input[0]) == -1) {
			cout << "There is no \"" << user_input[0] << "\"!\n\n";
			addToHangman();
		}
	}

	void displayGame() {
		string hidden_word = "";
		bool found_word = true;
		for (char c : correct_word) {
			if (letters_found[(int)c - 65]) {
				hidden_word += c;
			}
			else {
				hidden_word += '_';
				found_word = false;
			}
			hidden_word += ' ';
		}

		cout << "  +---+\n";
		cout << "  |   |\n";
		cout << "  " << body_parts[0] << "   |\n";
		cout << " " << body_parts[2] << body_parts[1] << body_parts[3] << "  |\n";
		cout << " " << body_parts[4] << " " << body_parts[5] << "  |\n";
		cout << "      |\n";
		cout << "=========\n\n";
		cout << hidden_word << "\n\n";

		if (found_word) {
			game_won = true;
		}
	}

	public:
		void playHangman() {

			setupGame();
			
			system("cls");
			cout << "--- Tic Tac Toe ---\n\n";
			displayGame();

			while (!game_finished) {
				bool character_check = true;

				cout << "Type in a Letter or Word to Guess: \n";

				cin >> user_input;
				user_input = toUpperCase(user_input);
				if (user_input == "QUIT") {
					game_finished = true;
					system("cls");
					break;
				}
				for (auto c : user_input) {
					if (!isalpha(c)) {
						character_check = false;
						break;
					}
				}
				if (!character_check) {
					cerr << "Invalid Input\n";
					continue;
				}

				system("cls");
				if (user_input.size() > 1) {
					guessWord();
				}
				else {
					guessLetter();
				}

				displayGame();

				if (game_won) {
					cout << "Correct! The answer was " << correct_word << "! \n";
					cout << "Type \"y\" to play again: \n";

					cin >> user_input;
					if (user_input == "y") {
						playHangman();
						break;
					}
					else {
						game_finished = true;
						system("cls");
						break;
					}
				}
				else if (wrong_guesses > 5) {
					cout << "You Lose! The Correct Answer was " << correct_word << "! \n";
					cout << "Type \"y\" to play again: \n";

					cin >> user_input;
					if (user_input == "y") {
						playHangman();
						break;
					}
					else {
						game_finished = true;
						system("cls");
						break;
					}
				}
			}
		}
};

int main() {
	string user_input;
	bool program_done = false;

	while (!program_done) {
		cout << "Welcome to the CPP Console App! \n\n";
		cout << "Type in a Number to Select a Program or \"quit\" to Exit the Console \n";
		cout << "(1) Guess the Number \n";
		cout << "(2) Forza Horizon -1 \n";
		cout << "(3) Alphbetically Sort Words \n";
		cout << "(4) TicTacToe \n";
		cout << "(5) Hangman \n";

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
		else if (user_input == "4") {
			TicTacToeGame tg;
			tg.playTicTacToe();
		}
		else if (user_input == "5") {
			HangmanGame hg;
			hg.playHangman();
		}
		else {
			cerr << "Invalid Input \n";
		}
	}
	cout << "\nThank you for Using the Console App!";
	return 0;
}