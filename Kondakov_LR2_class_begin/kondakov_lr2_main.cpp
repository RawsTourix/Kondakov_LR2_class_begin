#include "kondakov_lr2_car.h"

int main() {
	setlocale(LC_ALL, "Russian");

	vector<Car> car_vector;

	map<int, MenuItem> menu {
		{ 1, { "Получить данные о машинах из БД;",
			   Car::load_cars_to_vector(BD_FILE_NAME, car_vector) } },
		{ 2, { "Вывести данные о машинах;",
	           Car::print_car_vector(car_vector) } },
		{ 3, { "Добавить машину в список;",
			   Car::add_car(car_vector) } },
		{ 4, { "Загрузить данные в БД;",
			   Car::load_cars_to_bd(BD_FILE_NAME, car_vector) } },
		{ 5, { "Вывести список автомобилей заданной марки;",
			   Car::print_cars_by_brand(car_vector) } },
		{ 6, { "Вывести список автомобилей, выпущенных после заданного года;",
			   Car::print_cars_after_year(car_vector) } },
		{ 7, { "Вывести список автомобилей с пробегом меньше заданного.",
			   Car::print_cars_less_mileage(car_vector) } }
	};

	int choice = 0;
	bool escape = false;

	cout << "[Примечание: для отмены выбранного вами действия оставьте ввод пустым и нажмите Enter]" << endl << endl;
	while (true) {
		InputControl::show_menu(menu);
		InputControl::enter_number(choice, escape, "Введите номер пункта: ");
		cout << endl << endl;

		if (!escape) {
			// Завершение программы при choice == 0
			if (choice == 0) {
				cout << "© 2025 Fedor Kondakov" << endl;
				break;
			}

			// Проверка на существование выбранного пункта меню
			if (menu.find(choice) != menu.end()) {
				menu[choice].action();
			}
			else {
				cout << "Некорректный ввод!";
			}
		}
		escape = false;
		cout << endl << endl << endl;
	}

	return 0;
}