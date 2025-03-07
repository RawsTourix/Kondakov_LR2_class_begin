#include "kondakov_lr2_car.h"

using namespace std;

// Вывод
void Car::print() const {
	cout << "Марка: " << brand_ << endl;
	cout << "Модель: " << model_ << endl;
	cout << "Год выпуска: " << year_ << endl;
	cout << "Цвет: " << color_ << endl;
	cout << "Номерной знак: " << number_ << endl;
	cout << "Пробег: " << mileage_ << " км" << endl << endl;
}

// Вывод вектора машин
function<void()> Car::print_car_vector(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "Список автомобилей пуст!";
		else {
			for (const auto& car : cars)
				car.print();
			cout << endl << "В списке [" << cars.size() << "] машин" << InputControl::get_car_ending(cars.size()) << ".";
		}
	};
}

// Ввод
Car* Car::input() {
	bool escape = false;
	string brand, model, color, number;
	int year, mileage;

	InputControl::enter_string(brand, escape, "Марка: ");						if (escape) return new Car();
	InputControl::enter_string(model, escape, "Модель: ");						if (escape) return new Car();
	InputControl::enter_number(year, escape, "Год выпуска : ", 1885, 2025);		if (escape) return new Car();
	InputControl::enter_string(color, escape, "Цвет: ");						if (escape) return new Car();
	InputControl::enter_string(number, escape, "Номерной знак: ");				if (escape) return new Car();
	InputControl::enter_number(mileage, escape, "Пробег: ", 0, 10000000);		if (escape) return new Car();
	cout << endl;

	return new Car(move(brand), move(model), move(year), move(color), move(number), move(mileage));
}

// Добавление машины в список
function<void()> Car::add_car(vector<Car>& cars) {
	return [&cars]() {
		Car car = *input();
		if (car) {
			cars.push_back(car);
			cout << "Машина успешно добавлена.";
		}
		else
			cout << endl << endl << "Машина не добавлена, так как операция была отменена.";
	};
}

// Получить список машин заданной марки
bool Car::is_brand(const string& brand) const {
	return brand_ == brand;
}

// Вывод списка машин заданной марки
function<void()> Car::print_cars_by_brand(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "Список автомобилей пуст!";
		else {
			vector<Car> filtered_cars;
			string brand;
			bool escape = false;
			InputControl::enter_string(brand, escape, "Марка машины: ");
			cout << endl;

			if (escape)
				cout << endl;
			else {
				for (const auto& car : cars)
					if (car.is_brand(brand))
						filtered_cars.push_back(car);

				if (filtered_cars.empty())
					cout << "Машины марки \"" << brand << "\" нет в списке!";
				else {
					for (const auto& car : filtered_cars)
						car.print();

					cout << "Найден" << InputControl::get_find_ending(filtered_cars.size())
						 << " [" << filtered_cars.size() << "] машин" << InputControl::get_car_ending(filtered_cars.size())
						 << " марки \"" << brand << "\".";
				}
			}
		}
	};
}

// Получить список машин выпущенных после заданного года
bool Car::after_year(const int& year) const {
	return year_ > year;
}

// Вывод списка автомобилей, выпущенных после заданного года
function<void()> Car::print_cars_after_year(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "Список автомобилей пуст!";
		else {
			vector<Car> filtered_cars;
			int year;
			bool escape = false;
			InputControl::enter_number(year, escape, "Год, после которого выпущена машина: ", 1885, 2025);
			cout << endl;

			if (escape)
				cout << endl;
			else {
				for (const auto& car : cars)
					if (car.after_year(year))
						filtered_cars.push_back(car);

				if (filtered_cars.empty())
					cout << "Машин, выпущенных после \"" << year << "\" года, нет в списке!";
				else {
					for (const auto& car : filtered_cars)
						car.print();

					cout << "Найден" << InputControl::get_find_ending(filtered_cars.size())
						 << " [" << filtered_cars.size() << "] машин" << InputControl::get_car_ending(filtered_cars.size())
						 << ", выпущенных после \"" << year << "\" года.";
				}
			}
		}
	};
}

// Получить список машин с пробегом меньше заданного
bool Car::less_mileage(const int& mileage) const {
	return mileage_ < mileage;
}

// Вывод списка автомобилей с пробегом меньше заданного
function<void()> Car::print_cars_less_mileage(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "Список автомобилей пуст!" << endl << endl;
		else {
			vector<Car> filtered_cars;
			int mileage;
			bool escape = false;
			InputControl::enter_number(mileage, escape, "Пробег, меньше которого искать машины: ", 0, 10000000);
			cout << endl;

			if (escape)
				cout << endl;
			else {
				for (const auto& car : cars)
					if (car.less_mileage(mileage))
						filtered_cars.push_back(car);

				if (filtered_cars.empty())
					cout << "Машин с пробегом меньше \"" << mileage << "\" км нет в списке!";
				else {
					for (const auto& car : filtered_cars)
						car.print();

					cout << "Найден" << InputControl::get_find_ending(filtered_cars.size())
						 << " [" << filtered_cars.size() << "] машин" << InputControl::get_car_ending(filtered_cars.size())
						 << "с пробегом меньше \"" << mileage << "\" км.";
				}
			}
		}
	};
}

// Загрузить данные о машинах с базы данных
function<void()> Car::load_cars_to_vector(const string& filename, vector<Car>& cars) {
	return [&filename, &cars]() {
		ifstream file(filename);

		if (file.is_open()) {
			cars.clear();
			string line = "";
			string err = "";
			try {
				while (getline(file, line)) {
					stringstream ss(line);
					string brand, model, year_str, color, number, mileage_str;
					int year, mileage;

					err = "Марка (brand)";
					getline(ss, brand, ',');
					InputControl::trim(brand);

					err = "Модель (model)";
					getline(ss, model, ',');
					InputControl::trim(model);

					err = "Год выпуска (year)";
					getline(ss, year_str, ',');
					InputControl::trim(year_str);
					year = stoi(year_str);

					err = "Цвет (color)";
					getline(ss, color, ',');
					InputControl::trim(color);

					err = "Номерной знак (number)";
					getline(ss, number, ',');
					InputControl::trim(number);

					err = "Пробег (mileage)";
					getline(ss, mileage_str, ',');
					InputControl::trim(mileage_str);
					mileage = stoi(mileage_str);

					cars.emplace_back(Car(move(brand), move(model), move(year), move(color), move(number), move(mileage)));
				}
				cout << "Данные успешно загружены.";
				file.close();
			}
			catch (...) {
				cerr << "Ошибка при загрузке данных!" << endl << endl;
				if (err == "") {
					cerr << "Дополнительная информация об ошибке отсутствует.";
				}
				else {
					cerr << "Проверьте поле: " << err << ".";
				}
				cars.clear();
			}
		}
		else
			cerr << "Возникла ошибка при открытии файла: " << filename;
	};
}

// Загрузить данные о машинах с базы данных
function<void()> Car::load_cars_to_bd(const string& filename, vector<Car>& cars) {
	return [&filename, &cars]() {
		if (cars.empty())
			cout << "Список автомобилей пуст!";
		else {
			ofstream file(filename, ios::trunc);
			if (file.is_open()) {
				try {
					for (const auto& car : cars)
						file << car.brand_ << ", " << car.model_ << ", " << car.year_ << ", "
						<< car.color_ << ", " << car.number_ << ", " << car.mileage_ << "\n";
					file.close();
					cout << "Данные успешно записаны.";
				}
				catch (...) { cerr << "Ошибка при загрузке данных в БД!"; }
			}
		}
	};
}