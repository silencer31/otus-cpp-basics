#pragma once

#include <iostream>

//  ласс создан дл€ проверки вызова деструктора при удалении элемента из контейнера.
class TestClass{
public:
	TestClass() : test_val(45) {
		std::cout << "Test Class default constructor" << std::endl;
	};
	
	explicit TestClass(int val) : test_val(val) {
		std::cout << "Test Class explicit constructor" << std::endl;
		ptr = &test_val;
	}

	~TestClass() {
		std::cout << "Test Class destructor" << std::endl;
		
		ptr = nullptr;

		// ѕередаем значение обнуленного указател€ через внешний указатель на указатель.
		if (out_ptr != nullptr) {
			*out_ptr = ptr;
		}
	}

	// ”знать значение указател€ через внешний указатель на указатель.
	// “ак сделано специально.
	void get_ptr_value() { 
		if (out_ptr != nullptr) {
			*out_ptr = ptr;
		}
	}

	// «апомнить внешний указатель на указатель. 
	void set_ptr_value(int** p_ptr) { out_ptr = p_ptr; }

private:
	int test_val = 0;

	int *ptr = nullptr;

	int **out_ptr = nullptr;

	
};