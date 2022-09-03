#pragma once

#include <iostream>

// ����� ������ ��� �������� ������ ����������� ��� �������� �������� �� ����������.
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

		// �������� �������� ����������� ��������� ����� ������� ��������� �� ���������.
		if (out_ptr != nullptr) {
			*out_ptr = ptr;
		}
	}

	// ������ �������� ��������� ����� ������� ��������� �� ���������.
	// ��� ������� ����������.
	void get_ptr_value() { 
		if (out_ptr != nullptr) {
			*out_ptr = ptr;
		}
	}

	// ��������� ������� ��������� �� ���������. 
	void set_ptr_value(int** p_ptr) { out_ptr = p_ptr; }

private:
	int test_val = 0;

	int *ptr = nullptr;

	int **out_ptr = nullptr;

	
};