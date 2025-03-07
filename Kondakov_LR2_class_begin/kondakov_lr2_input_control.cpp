#include "kondakov_lr2_input_control.h"

const char* SEP = "= ";

// Удаление пробелов вначале и в конце (trim)
void InputControl::trim(string& str) {
	// Удаляем пробелы с начала
	while (!str.empty() && str.front() == ' ')
		str.erase(str.begin());

	// Удаляем пробелы с конца
	while (!str.empty() && str.back() == ' ')
		str.pop_back();
}

// Возвращает окончание слова "машина" в зависимости от его количества
string InputControl::get_car_ending(size_t n) {
	n %= 100;
	if (n >= 11 && n <= 19) return "";
	n %= 10;
	if (n == 1) return "а";
	if (n >= 2 && n <= 4) return "ы";
	return "";
}

// Возвращает окончание слова "найдено" в зависимости от его количества
string InputControl::get_find_ending(size_t n) {
	n %= 100;
	if (n == 11) return "о";
	n %= 10;
	if (n == 1) return "а";
	return "о";
}

// Проверка на пустой ввод для отмены операции
bool InputControl::is_input_empty(string input) {
	if (input.empty()) {
		cout << endl << "[Отмена операции]";
		return true;
	}
	return false;
}

// Проверка конвертации в целое число
bool InputControl::is_int(string input, int min, int max) {
	try {
		int number = stoi(input);
		if (number < min) { cout << endl << "Вы ввели \"" << number << "\" — значение должно быть больше \"" << min << "\"" << endl << endl; return false; }
		if (number > max) { cout << endl << "Вы ввели \"" << number << "\" — значение должно быть меньше \"" << max << "\"" << endl << endl; return false; }
	}
	catch (...) { cerr << endl << "Введённое вами значение \"" << input << "\" не является числом!" << endl << endl; return false; }
	return true;
}

// Вспомогательная функция для ввода целых чисел
void InputControl::enter_number(int& varLink, bool& escapeLink, string label, int min, int max) {
	string raw_input;

	do {
		cout << label << SEP;
		getline(cin, raw_input);
		trim(raw_input);
		escapeLink = is_input_empty(raw_input);
		if (escapeLink) return;
	} while (!is_int(raw_input, min, max));

	varLink = stoi(raw_input);
}

// Вспомогательная функция для ввода строк
void InputControl::enter_string(string& varLink, bool& escapeLink, string label) {
	string raw_input;

	cout << label << SEP;
	getline(cin, raw_input);
	trim(raw_input);
	escapeLink = is_input_empty(raw_input);
	if (!escapeLink)
		varLink = raw_input;
}

// Функция для вывода меню
void InputControl::show_menu(const map<int, MenuItem>& menu) {
	cout << "Меню:" << endl;

	for (const auto& item : menu) {
		cout << item.first << ". " << item.second.title << endl;
	}

	cout << "0. Выход" << endl << endl;
}