#ifndef KONDAKOV_LR2_DEF
#define KONDAKOV_LR2_DEF

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// ���� � ��
const string BD_FILE_NAME = "car_bd.txt";

// ��������� ����
struct MenuItem {
	string title;
	function<void()> action;
};

#endif // !KONDAKOV_LR2_DEF