#ifndef KONDAKOV_LR2_INPUT_CONTROL
#define KONDAKOV_LR2_INPUT_CONTROL

#include "kondakov_lr2_def.h"

class InputControl {
public:
	// �������� �������� ������� � � ����� (trim)
	static void trim(string& str);

	// ���������� ��������� ����� "������" � ����������� �� ��� ����������
	static string get_car_ending(size_t n);

	// ���������� ��������� ����� "�������" � ����������� �� ��� ����������
	static string get_find_ending(size_t n);

	// �������� �� ������ ���� ��� ������ ��������
	static bool is_input_empty(string input);

	// �������� ����������� � ����� �����
	static bool is_int(string input, int min, int max);

	// ��������������� ������� ��� ����� ����� �����
	static void enter_number(int& varLink, bool& escapeLink, string label = "", int min = 0, int max = 2147483647);

	// ��������������� ������� ��� ����� �����
	static void enter_string(string& varLink, bool& escapeLink, string label = "");

	// ������� ��� ������ ����
	static void show_menu(const map<int, MenuItem>& menu);
};

#endif // !KONDAKOV_LR2_INPUT_CONTROL