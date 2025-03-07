#ifndef KONDAKOV_LR2_CAR
#define KONDAKOV_LR2_CAR

#include "kondakov_lr2_input_control.h"

class Car {
	std::string brand_, model_, color_, number_;
	int year_, mileage_;

public:
	// ����������� ������ ��� ������������
	Car() : brand_(""), model_(""), year_(0), color_(""), number_(""), mileage_(0) {}

	// ����������� ������ � �����������:
	// 1. ����� (brand_(brand))
	// 2. ������ (model_(model))
	// 3. ��� ������� (year_(year))
	// 4. ���� (color_(color))
	// 5. �������� ���� (number_(number))
	// 6. ������ (mileage_(mileage))
	Car(const std::string& brand, const std::string& model, int year, const std::string& color, const std::string& number, int mileage)
		: brand_(brand), model_(model), year_(year), color_(color), number_(number), mileage_(mileage) {}

	// ����������� ������ � ������������ ����������:
	// 1. ����� (brand_(move(brand))
	// 2. ������ (model_(move(model))
	// 3. ��� ������� (year_(move(year))
	// 4. ���� (color_(move(color))
	// 5. �������� ���� (number_(move(number))
	// 6. ������ (mileage_(move(mileage))
	Car(std::string&& brand, std::string&& model, int year, std::string&& color, std::string&& number, int mileage)
		: brand_(move(brand)), model_(move(model)), year_(move(year)),
		  color_(move(color)), number_(move(number)), mileage_(move(mileage)) {}

	// ������ ����� ���������� ������ Car
	Car(const Car& car) = default;

	// ���������� �������
	~Car() = default;

	// ���������� true ��� ����������, ���� ������������ ����������� (��� ������ ��������)
	explicit operator bool() const {
		return !brand_.empty() && !model_.empty() && year_ != 0 && !color_.empty() && !number_.empty() && mileage_ != 0;
	}

	// ����������� ���������� ���������� �������� ������������ ������:
	// 1. ����� (brand_)
	// 2. ������ (model_)
	// 3. ��� ������� (year_)
	// 4. ���� (color_)
	// 5. �������� ���� (number_)
	// 6. ������ (mileage_)
	inline void get_specification(std::string& brand, std::string& model, int& year,
								  std::string& color, std::string& number, int& mileage) const {
		brand = brand_;
		model = model_;
		year = year_;
		color = color_;
		number = number_;
		mileage = mileage_;
	}
	// ��������� ������ � ����� ������
	inline std::string get_brand() const { return brand_; }
	// ��������� ������ � ������ ������
	inline std::string get_model() const { return model_; }
	// ��������� ������ � ���� ������� ������
	inline int get_year() const { return year_; }
	// ��������� ������ � ����� ������
	inline std::string get_color() const { return color_; }
	// ��������� ������ � �������� ����� ������
	inline std::string get_number() const { return number_; }
	// ��������� ������ � ������� ������
	inline int get_mileage() const { return mileage_; }

	// ����� ���������� ��������� ��������� ������������ ������:
	// 1. ����� (brand)
	// 2. ������ (model)
	// 3. ��� ������� (year)
	// 4. ���� (color)
	// 5. �������� ���� (number)
	// 6. ������ (mileage)
	inline void set_specification(const std::string& brand, const std::string& model, const int& year,
								  const std::string& color, const std::string& number, const int& mileage) {
		brand_ = brand;
		model_ = model;
		year_ = year;
		color_ = color;
		number_ = number;
		mileage_ = mileage;
	}
	// ����� ����� ������
	inline void set_brand(const std::string& brand) { brand_ = brand; }
	// ����� ������ ������
	inline void set_model(const std::string& model) { model_ = model; }
	// ����� ��� ������� ������
	inline void set_year(int year) { year_ = year; }
	// ����� ���� ������
	inline void set_color(const std::string& color) { color_ = color; }
	// ����� �������� ���� ������
	inline void set_number(const std::string& number) { number_ = number; }
	// ����� ������ ������
	inline void set_mileage(int mileage) { mileage_ = mileage; }


	// ����� ������������ ������:
	// 1. ����� (brand_)
	// 2. ������ (model_)
	// 3. ��� ������� (year_)
	// 4. ���� (color_)
	// 5. �������� ���� (number_)
	// 6. ������ (mileage_)
	void print() const;

	// ����� ������� �����
	static function<void()> print_car_vector(const vector<Car>& cars);

	// ���� ������������ ������:
	// 1. ����� (brand)
	// 2. ������ (model)
	// 3. ��� ������� (year)
	// 4. ���� (color)
	// 5. �������� ���� (number)
	// 6. ������ (mileage)
	static Car* input();

	static function<void()> add_car(vector<Car>& cars);

	// ����������� �� ������ �������� �����
	bool is_brand(const string& brand) const;

	// ����� ������ ����� �������� �����
	static function<void()> print_cars_by_brand(const vector<Car>& cars);

	// �������� �� ������ ����� ��������� ����
	bool after_year(const int& year) const;

	// ����� ������ �����������, ���������� ����� ��������� ����
	static function<void()> print_cars_after_year(const vector<Car>& cars);

	// ������ �� �������, ��� ��������
	bool less_mileage(const int& mileage) const;

	// ����� ������ ����������� � �������� ������ ���������
	static function<void()> print_cars_less_mileage(const vector<Car>& cars);

	// �������� ������ � ������� �� ��
	static function<void()> load_cars_to_vector(const string& filename, vector<Car>& cars);

	// �������� ������ � ������� � ��
	static function<void()> load_cars_to_bd(const string& filename, vector<Car>& cars);
};

#endif //!KONDAKOV_LR2_CAR