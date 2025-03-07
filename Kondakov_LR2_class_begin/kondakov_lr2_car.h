#ifndef KONDAKOV_LR2_CAR
#define KONDAKOV_LR2_CAR

#include "kondakov_lr2_input_control.h"

class Car {
	std::string brand_, model_, color_, number_;
	int year_, mileage_;

public:
	// Конструктор машины без спецификаций
	Car() : brand_(""), model_(""), year_(0), color_(""), number_(""), mileage_(0) {}

	// Конструктор машины с параметрами:
	// 1. Марка (brand_(brand))
	// 2. Модель (model_(model))
	// 3. Год выпуска (year_(year))
	// 4. Цвет (color_(color))
	// 5. Номерной знак (number_(number))
	// 6. Пробег (mileage_(mileage))
	Car(const std::string& brand, const std::string& model, int year, const std::string& color, const std::string& number, int mileage)
		: brand_(brand), model_(model), year_(year), color_(color), number_(number), mileage_(mileage) {}

	// Конструктор машины с перемещением параметров:
	// 1. Марка (brand_(move(brand))
	// 2. Модель (model_(move(model))
	// 3. Год выпуска (year_(move(year))
	// 4. Цвет (color_(move(color))
	// 5. Номерной знак (number_(move(number))
	// 6. Пробег (mileage_(move(mileage))
	Car(std::string&& brand, std::string&& model, int year, std::string&& color, std::string&& number, int mileage)
		: brand_(move(brand)), model_(move(model)), year_(move(year)),
		  color_(move(color)), number_(move(number)), mileage_(move(mileage)) {}

	// Создаёт копию экземпляра класса Car
	Car(const Car& car) = default;

	// Деструктор объекта
	~Car() = default;

	// Возвращает true при стравнении, если спецификация отсутствует (для отмены операции)
	explicit operator bool() const {
		return !brand_.empty() && !model_.empty() && year_ != 0 && !color_.empty() && !number_.empty() && mileage_ != 0;
	}

	// Присваивает переданным переменным значения спецификации машины:
	// 1. Марка (brand_)
	// 2. Модель (model_)
	// 3. Год выпуска (year_)
	// 4. Цвет (color_)
	// 5. Номерной знак (number_)
	// 6. Пробег (mileage_)
	inline void get_specification(std::string& brand, std::string& model, int& year,
								  std::string& color, std::string& number, int& mileage) const {
		brand = brand_;
		model = model_;
		year = year_;
		color = color_;
		number = number_;
		mileage = mileage_;
	}
	// Получение данных о марке машины
	inline std::string get_brand() const { return brand_; }
	// Получение данных о модели машины
	inline std::string get_model() const { return model_; }
	// Получение данных о годе выпуска машины
	inline int get_year() const { return year_; }
	// Получение данных о цвете машины
	inline std::string get_color() const { return color_; }
	// Получение данных о номерном знаке машины
	inline std::string get_number() const { return number_; }
	// Получение данных о пробеге машины
	inline int get_mileage() const { return mileage_; }

	// Задаёт переданные параметры значениям спецификации машины:
	// 1. Марка (brand)
	// 2. Модель (model)
	// 3. Год выпуска (year)
	// 4. Цвет (color)
	// 5. Номерной знак (number)
	// 6. Пробег (mileage)
	inline void set_specification(const std::string& brand, const std::string& model, const int& year,
								  const std::string& color, const std::string& number, const int& mileage) {
		brand_ = brand;
		model_ = model;
		year_ = year;
		color_ = color;
		number_ = number;
		mileage_ = mileage;
	}
	// Задаёт марку машины
	inline void set_brand(const std::string& brand) { brand_ = brand; }
	// Задаёт модель машины
	inline void set_model(const std::string& model) { model_ = model; }
	// Задаёт год выпуска машины
	inline void set_year(int year) { year_ = year; }
	// Задаёт цвет машины
	inline void set_color(const std::string& color) { color_ = color; }
	// Задаёт номерной знак машины
	inline void set_number(const std::string& number) { number_ = number; }
	// Задаёт пробег машины
	inline void set_mileage(int mileage) { mileage_ = mileage; }


	// Вывод спецификации машины:
	// 1. Марка (brand_)
	// 2. Модель (model_)
	// 3. Год выпуска (year_)
	// 4. Цвет (color_)
	// 5. Номерной знак (number_)
	// 6. Пробег (mileage_)
	void print() const;

	// Вывод вектора машин
	static function<void()> print_car_vector(const vector<Car>& cars);

	// Ввод спецификации машины:
	// 1. Марка (brand)
	// 2. Модель (model)
	// 3. Год выпуска (year)
	// 4. Цвет (color)
	// 5. Номерной знак (number)
	// 6. Пробег (mileage)
	static Car* input();

	static function<void()> add_car(vector<Car>& cars);

	// Принадлежит ли машина заданной марке
	bool is_brand(const string& brand) const;

	// Вывод списка машин заданной марки
	static function<void()> print_cars_by_brand(const vector<Car>& cars);

	// Выпущена ли машина после заданного года
	bool after_year(const int& year) const;

	// Вывод списка автомобилей, выпущенных после заданного года
	static function<void()> print_cars_after_year(const vector<Car>& cars);

	// Меньше ли пробего, чем заданный
	bool less_mileage(const int& mileage) const;

	// Вывод списка автомобилей с пробегом меньше заданного
	static function<void()> print_cars_less_mileage(const vector<Car>& cars);

	// Загрузка данных о машинах из БД
	static function<void()> load_cars_to_vector(const string& filename, vector<Car>& cars);

	// Загрузка данных о машинах в БД
	static function<void()> load_cars_to_bd(const string& filename, vector<Car>& cars);
};

#endif //!KONDAKOV_LR2_CAR