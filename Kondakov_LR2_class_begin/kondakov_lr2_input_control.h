#ifndef KONDAKOV_LR2_INPUT_CONTROL
#define KONDAKOV_LR2_INPUT_CONTROL

#include "kondakov_lr2_def.h"

class InputControl {
public:
	// Удаление пробелов вначале и в конце (trim)
	static void trim(string& str);

	// Возвращает окончание слова "машина" в зависимости от его количества
	static string get_car_ending(size_t n);

	// Возвращает окончание слова "найдено" в зависимости от его количества
	static string get_find_ending(size_t n);

	// Проверка на пустой ввод для отмены операции
	static bool is_input_empty(string input);

	// Проверка конвертации в целое число
	static bool is_int(string input, int min, int max);

	// Вспомогательная функция для ввода целых чисел
	static void enter_number(int& varLink, bool& escapeLink, string label = "", int min = 0, int max = 2147483647);

	// Вспомогательная функция для ввода строк
	static void enter_string(string& varLink, bool& escapeLink, string label = "");

	// Функция для вывода меню
	static void show_menu(const map<int, MenuItem>& menu);
};

#endif // !KONDAKOV_LR2_INPUT_CONTROL