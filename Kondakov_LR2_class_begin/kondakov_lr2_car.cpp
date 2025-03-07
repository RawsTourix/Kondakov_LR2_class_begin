#include "kondakov_lr2_car.h"

using namespace std;

// �����
void Car::print() const {
	cout << "�����: " << brand_ << endl;
	cout << "������: " << model_ << endl;
	cout << "��� �������: " << year_ << endl;
	cout << "����: " << color_ << endl;
	cout << "�������� ����: " << number_ << endl;
	cout << "������: " << mileage_ << " ��" << endl << endl;
}

// ����� ������� �����
function<void()> Car::print_car_vector(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "������ ����������� ����!";
		else {
			for (const auto& car : cars)
				car.print();
			cout << endl << "� ������ [" << cars.size() << "] �����" << InputControl::get_car_ending(cars.size()) << ".";
		}
	};
}

// ����
Car* Car::input() {
	bool escape = false;
	string brand, model, color, number;
	int year, mileage;

	InputControl::enter_string(brand, escape, "�����: ");						if (escape) return new Car();
	InputControl::enter_string(model, escape, "������: ");						if (escape) return new Car();
	InputControl::enter_number(year, escape, "��� ������� : ", 1885, 2025);		if (escape) return new Car();
	InputControl::enter_string(color, escape, "����: ");						if (escape) return new Car();
	InputControl::enter_string(number, escape, "�������� ����: ");				if (escape) return new Car();
	InputControl::enter_number(mileage, escape, "������: ", 0, 10000000);		if (escape) return new Car();
	cout << endl;

	return new Car(move(brand), move(model), move(year), move(color), move(number), move(mileage));
}

// ���������� ������ � ������
function<void()> Car::add_car(vector<Car>& cars) {
	return [&cars]() {
		Car car = *input();
		if (car) {
			cars.push_back(car);
			cout << "������ ������� ���������.";
		}
		else
			cout << endl << endl << "������ �� ���������, ��� ��� �������� ���� ��������.";
	};
}

// �������� ������ ����� �������� �����
bool Car::is_brand(const string& brand) const {
	return brand_ == brand;
}

// ����� ������ ����� �������� �����
function<void()> Car::print_cars_by_brand(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "������ ����������� ����!";
		else {
			vector<Car> filtered_cars;
			string brand;
			bool escape = false;
			InputControl::enter_string(brand, escape, "����� ������: ");
			cout << endl;

			if (escape)
				cout << endl;
			else {
				for (const auto& car : cars)
					if (car.is_brand(brand))
						filtered_cars.push_back(car);

				if (filtered_cars.empty())
					cout << "������ ����� \"" << brand << "\" ��� � ������!";
				else {
					for (const auto& car : filtered_cars)
						car.print();

					cout << "������" << InputControl::get_find_ending(filtered_cars.size())
						 << " [" << filtered_cars.size() << "] �����" << InputControl::get_car_ending(filtered_cars.size())
						 << " ����� \"" << brand << "\".";
				}
			}
		}
	};
}

// �������� ������ ����� ���������� ����� ��������� ����
bool Car::after_year(const int& year) const {
	return year_ > year;
}

// ����� ������ �����������, ���������� ����� ��������� ����
function<void()> Car::print_cars_after_year(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "������ ����������� ����!";
		else {
			vector<Car> filtered_cars;
			int year;
			bool escape = false;
			InputControl::enter_number(year, escape, "���, ����� �������� �������� ������: ", 1885, 2025);
			cout << endl;

			if (escape)
				cout << endl;
			else {
				for (const auto& car : cars)
					if (car.after_year(year))
						filtered_cars.push_back(car);

				if (filtered_cars.empty())
					cout << "�����, ���������� ����� \"" << year << "\" ����, ��� � ������!";
				else {
					for (const auto& car : filtered_cars)
						car.print();

					cout << "������" << InputControl::get_find_ending(filtered_cars.size())
						 << " [" << filtered_cars.size() << "] �����" << InputControl::get_car_ending(filtered_cars.size())
						 << ", ���������� ����� \"" << year << "\" ����.";
				}
			}
		}
	};
}

// �������� ������ ����� � �������� ������ ���������
bool Car::less_mileage(const int& mileage) const {
	return mileage_ < mileage;
}

// ����� ������ ����������� � �������� ������ ���������
function<void()> Car::print_cars_less_mileage(const vector<Car>& cars) {
	return [&cars]() {
		if (cars.empty())
			cout << "������ ����������� ����!" << endl << endl;
		else {
			vector<Car> filtered_cars;
			int mileage;
			bool escape = false;
			InputControl::enter_number(mileage, escape, "������, ������ �������� ������ ������: ", 0, 10000000);
			cout << endl;

			if (escape)
				cout << endl;
			else {
				for (const auto& car : cars)
					if (car.less_mileage(mileage))
						filtered_cars.push_back(car);

				if (filtered_cars.empty())
					cout << "����� � �������� ������ \"" << mileage << "\" �� ��� � ������!";
				else {
					for (const auto& car : filtered_cars)
						car.print();

					cout << "������" << InputControl::get_find_ending(filtered_cars.size())
						 << " [" << filtered_cars.size() << "] �����" << InputControl::get_car_ending(filtered_cars.size())
						 << "� �������� ������ \"" << mileage << "\" ��.";
				}
			}
		}
	};
}

// ��������� ������ � ������� � ���� ������
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

					err = "����� (brand)";
					getline(ss, brand, ',');
					InputControl::trim(brand);

					err = "������ (model)";
					getline(ss, model, ',');
					InputControl::trim(model);

					err = "��� ������� (year)";
					getline(ss, year_str, ',');
					InputControl::trim(year_str);
					year = stoi(year_str);

					err = "���� (color)";
					getline(ss, color, ',');
					InputControl::trim(color);

					err = "�������� ���� (number)";
					getline(ss, number, ',');
					InputControl::trim(number);

					err = "������ (mileage)";
					getline(ss, mileage_str, ',');
					InputControl::trim(mileage_str);
					mileage = stoi(mileage_str);

					cars.emplace_back(Car(move(brand), move(model), move(year), move(color), move(number), move(mileage)));
				}
				cout << "������ ������� ���������.";
				file.close();
			}
			catch (...) {
				cerr << "������ ��� �������� ������!" << endl << endl;
				if (err == "") {
					cerr << "�������������� ���������� �� ������ �����������.";
				}
				else {
					cerr << "��������� ����: " << err << ".";
				}
				cars.clear();
			}
		}
		else
			cerr << "�������� ������ ��� �������� �����: " << filename;
	};
}

// ��������� ������ � ������� � ���� ������
function<void()> Car::load_cars_to_bd(const string& filename, vector<Car>& cars) {
	return [&filename, &cars]() {
		if (cars.empty())
			cout << "������ ����������� ����!";
		else {
			ofstream file(filename, ios::trunc);
			if (file.is_open()) {
				try {
					for (const auto& car : cars)
						file << car.brand_ << ", " << car.model_ << ", " << car.year_ << ", "
						<< car.color_ << ", " << car.number_ << ", " << car.mileage_ << "\n";
					file.close();
					cout << "������ ������� ��������.";
				}
				catch (...) { cerr << "������ ��� �������� ������ � ��!"; }
			}
		}
	};
}