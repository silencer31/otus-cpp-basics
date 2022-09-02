#pragma once

#include <algorithm>
#include <iostream>

// ��������� � ���������������� �������� ������.

template <typename T>
class SerialContainer {
public:
	struct Iterator {
		Iterator() : iter_data_ptr{ nullptr } {}

		explicit Iterator(T* new_iter_ptr) : iter_data_ptr{ new_iter_ptr } {}

		T* operator++() {
			iter_data_ptr = iter_data_ptr + 1;
			return iter_data_ptr;
		}

		T get() {
			return *iter_data_ptr;
		}

		T& operator*() {
			return *iter_data_ptr;
		}

		bool operator==(const Iterator& another_iter) {
			return (iter_data_ptr == another_iter.iter_data_ptr);
		}

		bool operator!=(const Iterator& another_iter) {
			return !(iter_data_ptr == another_iter.iter_data_ptr);
		}

	private:
		T* iter_data_ptr;
	};

	// ����������� �� ���������.
	SerialContainer() : data_ptr{ nullptr }, total_number{ 0 }, capacity{ 0 } {
		std::cout << "Serial Container default constructor" << std::endl;
	}

	// ����������� � ���������� - �������� ������ ����������.
	explicit SerialContainer(const size_t& new_capacity) : SerialContainer()
	{
		std::cout << "Serial Container explicit constructor" << std::endl;

		if (new_capacity != 0) {
			data_ptr = new T[new_capacity];
			capacity = new_capacity;
		}
	}

	// ���������� �����������.
	SerialContainer(const SerialContainer& scont) : SerialContainer()
	{
		std::cout << "Serial Container copy constructor" << std::endl;

		if (scont.data_ptr != nullptr) {
			data_ptr = new T[scont.capacity];
			capacity = scont.capacity;

			for (size_t i = 0; i < scont.total_number; ++i) {
				data_ptr[i] = scont.data_ptr[i];
			}

			total_number = scont.total_number;
		}
	}

	// ������������ �����������.
	SerialContainer(SerialContainer&& scont) : SerialContainer()
	{
		std::cout << "Serial Container move constructor" << std::endl;

		std::swap(data_ptr, scont.data_ptr);
		std::swap(total_number, scont.total_number);
		std::swap(capacity, scont.capacity);
	}

	// �������� ����������� ������������.
	SerialContainer& operator=(const SerialContainer& scont)
	{
		std::cout << "Serial Container copy operator" << std::endl;

		if ((this != &scont) && (scont.data_ptr != nullptr)) {
			clear(); // ������ ������� ������ ����������.
			
			data_ptr = new T[scont.capacity];
			capacity = scont.capacity;

			for (size_t i = 0; i < scont.total_number; ++i) {
				data_ptr[i] = scont.data_ptr[i];
			}

			total_number = scont.total_number;
		}

		return *this;
	}

	// ������������ ������������.
	SerialContainer& operator=(SerialContainer&& scont) noexcept
	{
		std::cout << "Serial Container move operator" << std::endl;

		if ((this != &scont) && (scont.data_ptr != nullptr)) {
			clear(); // ������ ������� ������ ����������.

			SerialContainer temp{ std::move(scont) };
			std::swap(data_ptr, temp.data_ptr);
			std::swap(total_number, temp.total_number);
			std::swap(capacity, temp.capacity);
		}
		
		return *this;
	}

	// ��������� ������� �� �������. ����� �� ������� �� �����������.
	T& operator[](const size_t& place) {
		return data_ptr[place];
	}
	
	// ����������� �����. ��������� ������� �� �������. ����� �� ������� �� �����������.
	const T& operator[](const size_t& place) const {
		return data_ptr[place];
	}

	// ��������� ������� �� ������� � ��������� ������ �� �������.
	T& at(const size_t& place) {
		if (place >= total_number) throw std::out_of_range("Bad range");
		return data_ptr[place];
	}

	// ����������� �����. ��������� ������� �� ������� � ��������� ������ �� �������.
	const T& at(const size_t& place) const{
		if (place >= total_number) throw std::out_of_range("Bad range");
		return data_ptr[place];
	}

	// ����������.
	~SerialContainer()
	{
		std::cout << "Serial Container destructor" << std::endl;

		if (data_ptr != nullptr) {
			delete[] data_ptr;
		}
	}

	// ������� ����� ����������.
	void clear() {
		if (data_ptr != nullptr) {
			delete[] data_ptr;
			data_ptr = nullptr;
		}

		capacity = 0;
		total_number = 0;
	}

	// ������ ���������� ���������, ����������� � ���������.
	size_t get_number() const { return total_number; }

	// ������ ���������� ���������, ������� ����� ��������� � ���������� ��� ��������� ��� �������. ���������� ������� �� ������ ������.
	size_t get_capacity() const { return capacity; }

	// ������, ������ �� ���������.
	bool empty() const { return (total_number == 0); }

	// �������� ������ ������ �� ������.
	T* get_data() const { return data_ptr; }

	// ��������������� ����� � ������ ��� ����� ���������� ���������.
	void reserve(const size_t& new_cap) {
		if (new_cap <= capacity) return;

		T* new_data_ptr = new T[new_cap];

		if (data_ptr == nullptr) {
			data_ptr = new_data_ptr;
			capacity = new_cap;
			return;
		}

		for (size_t i = 0; i < total_number; ++i) {
			new_data_ptr[i] = data_ptr[i];
		}

		delete[] data_ptr;

		data_ptr = new_data_ptr;
		capacity = new_cap;
	}

	// �������� ����� ������� � ���������.
	void push_back(const T& value) {
		if (total_number == capacity) { // ��� ��������� ������ ��� ������.
			size_t new_capacity = (capacity == 0) ? 4 : static_cast<size_t>(capacity * 1.6);
			reserve(new_capacity);
		}

		data_ptr[total_number] = value;
		++total_number;
	}

	// ������� ��������� ������� �� ����������.
	void pop_back() {
		if (total_number == 0) return;
	
		--total_number;

		return;
	}

	// �������� ����� ������� � ��������� � ��������� �������.
	bool insert(const size_t& place, const T& value) {
		// ��������� ����� ������ �� ��� ����� ����� ���������� ��������. ������ ��������� ����� ������ �����.
		if (place > total_number) return false;

		if (total_number == capacity) { // ��� ��������� ������ ��� ������.
			size_t new_capacity = (capacity == 0) ? 4 : static_cast<size_t>(capacity * 1.6);
			reserve(new_capacity);
		}

		if (place == total_number) { // ������ ��������� ����� �� ��������� ���������
			data_ptr[place] = value;
			++total_number;
			return true;
		}

		// ��� ��������, ��������� �� ��������� �������, �������� �� 1 ����� � �����.
		size_t i = total_number;
		while( i != 0) {
			data_ptr[i] = data_ptr[i-1];
			--i;
			if (i == place) {
				break;
			}
		}

		data_ptr[place] = value;
		++total_number;

		return true;
	}

	// ������� ������� ���������� �� ��������� �������.
	bool erase(const size_t& place) {
		if (place >= total_number) return false; // ����� �� �������.

		if (total_number == 1) {
			total_number = 0;
			return true;
		}

		// ��� ��������, ��������� ����� �� ��������� ��������, �������� �� 1 ����� � ������.
		for (size_t i = place; i < (total_number - 1); ++i) {
			data_ptr[i] = data_ptr[i + 1];
		}

		--total_number;

		return true;
	}

	Iterator begin() const {
		return Iterator(&data_ptr[0]);
	}

	Iterator last_valid() const {
		if (data_ptr == nullptr) return Iterator(nullptr);
		return Iterator(&data_ptr[total_number-1]);
	}

	Iterator end() const {
		if (data_ptr == nullptr) return Iterator(nullptr);
		return Iterator(&data_ptr[total_number]);
	}

private:
	T *data_ptr; // ��������� �� ������ ������� ������������� �������.
	
	size_t total_number; // ���-�� ��������� � ����������.
	size_t capacity;	 // ����������� 
};

// ����� ���� ��������� ���������� � �������.
template <typename T>
std::ostream& operator<<(std::ostream& os, const SerialContainer<T>& scont) {
	for (auto iter = scont.begin(); iter != scont.end(); ++iter) {
		os << *iter;
		if (iter != scont.last_valid()) { os << ", "; }
	}

	return os;
}

template <typename T>
SerialContainer<T> get_serial_cont(const size_t& new_size) {
	SerialContainer<int> serial_cont(new_size);
	return serial_cont;
}