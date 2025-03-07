#include "kondakov_lr2_input_control.h"

const char* SEP = "= ";

// �������� �������� ������� � � ����� (trim)
void InputControl::trim(string& str) {
	// ������� ������� � ������
	while (!str.empty() && str.front() == ' ')
		str.erase(str.begin());

	// ������� ������� � �����
	while (!str.empty() && str.back() == ' ')
		str.pop_back();
}

// ���������� ��������� ����� "������" � ����������� �� ��� ����������
string InputControl::get_car_ending(size_t n) {
	n %= 100;
	if (n >= 11 && n <= 19) return "";
	n %= 10;
	if (n == 1) return "�";
	if (n >= 2 && n <= 4) return "�";
	return "";
}

// ���������� ��������� ����� "�������" � ����������� �� ��� ����������
string InputControl::get_find_ending(size_t n) {
	n %= 100;
	if (n == 11) return "�";
	n %= 10;
	if (n == 1) return "�";
	return "�";
}

// �������� �� ������ ���� ��� ������ ��������
bool InputControl::is_input_empty(string input) {
	if (input.empty()) {
		cout << endl << "[������ ��������]";
		return true;
	}
	return false;
}

// �������� ����������� � ����� �����
bool InputControl::is_int(string input, int min, int max) {
	try {
		int number = stoi(input);
		if (number < min) { cout << endl << "�� ����� \"" << number << "\" � �������� ������ ���� ������ \"" << min << "\"" << endl << endl; return false; }
		if (number > max) { cout << endl << "�� ����� \"" << number << "\" � �������� ������ ���� ������ \"" << max << "\"" << endl << endl; return false; }
	}
	catch (...) { cerr << endl << "�������� ���� �������� \"" << input << "\" �� �������� ������!" << endl << endl; return false; }
	return true;
}

// ��������������� ������� ��� ����� ����� �����
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

// ��������������� ������� ��� ����� �����
void InputControl::enter_string(string& varLink, bool& escapeLink, string label) {
	string raw_input;

	cout << label << SEP;
	getline(cin, raw_input);
	trim(raw_input);
	escapeLink = is_input_empty(raw_input);
	if (!escapeLink)
		varLink = raw_input;
}

// ������� ��� ������ ����
void InputControl::show_menu(const map<int, MenuItem>& menu) {
	cout << "����:" << endl;

	for (const auto& item : menu) {
		cout << item.first << ". " << item.second.title << endl;
	}

	cout << "0. �����" << endl << endl;
}