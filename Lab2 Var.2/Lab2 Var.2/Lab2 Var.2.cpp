#include <iostream>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>;
#include "windows.h";

using namespace std;

class FiniteAutomat {
public:
	FiniteAutomat() {}

	void InputFile(const string& filename) { // ввід з файлу
		ifstream file(filename);
		string str;

		if (!file.is_open()) {
			cerr << "Файл не знайдено" << endl;
			return;
		}

		InputAlphabet(file);
		InputStates(file);
		InputInitialState(file);
		InputFinalStates(file);

		while (getline(file, str)) {
			InputTransition(str);
		}

		file.close();
	}

	set<int> GetUnreachable() { // функція що шукає недосяжні стани, тобто стани до яких не може дійти автомат
		set<int> unreachableStates;
		for (int state : states) {
			bool isReachable = false;
			for (map<pair<int, char>, int>::iterator it = trans.begin(); it != trans.end(); it++) {
				if (it->second == state) {
					isReachable = true;
				}
			}
			if (!isReachable) {
				unreachableStates.insert(state);
			}
		}
		return unreachableStates;
	}

	set<int> GetDeadEnds() { // функція що шукає тупикові стани, тобто стани з яких не може вийти автомат
		set<int> deadEndStates;
		for (int state : states) {
			bool isDeadEnd = true;
			for (char symbol : alphabet) {
				if (trans.count(make_pair(state, symbol)) > 0) {
					isDeadEnd = false;
				}
			}
			if (isDeadEnd) {
				deadEndStates.insert(state);
			}
		}
		return deadEndStates;
	}

private:
	set<char> alphabet;
	set<int> states;
	int initialState;
	set<int> finalStates;
	int currentState;
	map<pair<int, char>, int> trans;

	void InputAlphabet(ifstream& file) { // вводимо з файлу алфавіт
		string str;
		getline(file, str);
		stringstream ss(str);
		char symbol;
		while (ss >> symbol) {
			if (symbol != ' ') {
				alphabet.insert(symbol);
			}
		}
	}

	void InputStates(ifstream& file) { // вводимо з файлу стани
		string str;
		getline(file, str);
		stringstream ss(str);
		int state;
		while (ss >> state) {
			states.insert(state);
		}
	}

	void InputInitialState(ifstream& file) { // вводимо з файлу початковий стан
		file >> initialState;
	}

	void InputFinalStates(ifstream& file) { // вводимо з файлу фінальні стани
		int numFinalStates;
		file >> numFinalStates;
		for (int i = 0; i < numFinalStates; ++i) {
			int finalState;
			file >> finalState;
			finalStates.insert(finalState);
		}
		string str;
		getline(file, str);
	}

	void InputTransition(const string& str) { // вводимо з файлу переходи
		int fromState, toState;
		char inputSymbol;
		stringstream ss(str);
		ss >> fromState >> inputSymbol >> toState;
		trans[make_pair(fromState, inputSymbol)] = toState;
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "ukr");

	FiniteAutomat automat;

	automat.InputFile("file.txt"); // вводимо з файлу input.txt

	try {
		set<int> unreachableStates = automat.GetUnreachable(); // отримуємо недосяжні стани
		set<int> deadEndStates = automat.GetDeadEnds(); // отримуємо тупикові стани
		cout << "Недосяжні стани:" << endl;
		for (int state : unreachableStates) {
			cout << state << endl;
		}

		cout << "Тупикові стани:" << endl;
		for (int state : deadEndStates) {
			cout << state << endl;
		}
	}
	catch (const char* exception)
	{
		std::cerr << "Error: " << exception << '\n';
	}
	cout << endl;
	system("pause");
	return 0;
}
