#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

void Tiuring();
void readFile(string* ThisState, string* NewState, char* Symbol, char* NewSymbol, char* Direction, string &tape, int &headPosition, int &amountOfInstructions);
bool moveHead(string* ThisState, string* NewState, char* Symbol, char* NewSymbol, char* Direction, string &currentState, string &tape, int &headPosition, int &amountOfInstructions);

int main()
{
	char command;
	while (true) {
		Tiuring();
		cout << "Continue? - (Y//N) "; cin >> command;
		if (command == 'N') break;
	}
	return 0;
}

//Actual Turing is happening here
void Tiuring() {
	int headPosition = 0, amountOfInstructions = 0;
	string tape, currentState = "0";
	string ThisState[100], NewState[100];
	char Symbol[100], NewSymbol[100], Direction[100];
	readFile(ThisState, NewState, Symbol, NewSymbol, Direction, tape, headPosition, amountOfInstructions);
	while (!_kbhit()) {
		if ((headPosition >= tape.length()) || (headPosition < 0)) break;
		if (!(moveHead(ThisState, NewState, Symbol, NewSymbol, Direction, currentState, tape, headPosition, amountOfInstructions))) {
			cout << "Halt - state: " << currentState << " - symbol: " << tape[headPosition] << endl;
			break;
		}
		cout << tape << endl;
	}
	return;
}

//Reads entered files, and prepares them for work
void readFile(string* ThisState, string* NewState, char* Symbol, char* NewSymbol, char* Direction, string &tape, int &headPosition, int &amountOfInstructions) {
	string filename;
	cout << "Enter file name - ";
	cin >> filename;
	ifstream file(filename);
	file >> headPosition;
	while (tape.empty()) {
		getline(file, tape);
	}
	int i = 0;
	while (!file.eof()) {
		file >> ThisState[i] >> Symbol[i] >> NewSymbol[i] >> Direction[i] >> NewState[i];
		i++;
	}
	amountOfInstructions = i-1;
	file.close();
}

//Moves Head of the machine to new location
bool moveHead(string* ThisState, string* NewState, char* Symbol, char* NewSymbol, char* Direction, string &currentState, string &tape, int &headPosition, int &amountOfInstructions) {
	for (int i = 0; i < amountOfInstructions; i++) {
		if (currentState == ThisState[i]) {
			if (tape[headPosition] == Symbol[i]) {
				tape[headPosition] = NewSymbol[i];
				if (Direction[i] == 'R') headPosition++;
				else headPosition--;

				currentState = NewState[i];
				return true;
			}
		}
	}
	return false;
}