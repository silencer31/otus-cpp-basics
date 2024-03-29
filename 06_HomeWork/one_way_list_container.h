#pragma once

#include <iostream>

// ���������, ����������� ���������������� ������.

template <typename T>
struct OneWayNode {
	OneWayNode() : next_node{ nullptr} {}
	explicit OneWayNode(const T& value) : next_node{ nullptr }, data{ value } {}

	OneWayNode* next_node;
	T data;
};

template <typename T>
class OneWayList {
public:
	struct Iterator {
		Iterator() : one_way_node_ptr{nullptr} {}

		explicit Iterator(OneWayNode<T>* own_ptr) : one_way_node_ptr{ own_ptr } {}

		OneWayNode<T>* operator++() {
			one_way_node_ptr = one_way_node_ptr->next_node;
			return one_way_node_ptr;
		}

		T get() {
			return one_way_node_ptr->data;
		}

		bool operator==(const Iterator& another_iter) {
			return (one_way_node_ptr == another_iter.one_way_node_ptr);
		}

		bool operator!=(const Iterator& another_iter) {
			return !(one_way_node_ptr == another_iter.one_way_node_ptr);
		}

	private:
		OneWayNode<T>* one_way_node_ptr;
	};


	OneWayList() : first_node_ptr{nullptr}, last_node_ptr{nullptr}, total_number{0} {
		std::cout << "One Way List default constructor" << std::endl;
	}

	// ����������� � ���������� - �������� ������� ��������.
	explicit OneWayList(const T& first_value) : OneWayList()
	{
		std::cout << "One Way List explicit constructor" << std::endl;

		OneWayNode<T> *ow_node_ptr = new OneWayNode(first_value);

		first_node_ptr = ow_node_ptr;
		last_node_ptr = ow_node_ptr;

		total_number = 1;
	}

	// ���������� �����������.
	OneWayList(const OneWayList& owl_cont) : OneWayList() {
		std::cout << "One Way List copy constructor" << std::endl;

		if (owl_cont.first_node_ptr != nullptr) {
			
			// � ����� ������� ����� ������� ���� ������� ������� � ������ �������.
			OneWayNode<T>* own_ptr_to_copy = owl_cont.first_node_ptr;
			OneWayNode<T>* own_ptr_new = nullptr;

			while (own_ptr_to_copy != nullptr) {
				own_ptr_new = new OneWayNode(own_ptr_to_copy->data);

				if (first_node_ptr == nullptr) { // ������ ������.
					first_node_ptr = own_ptr_new;
					last_node_ptr = own_ptr_new;
				}
				else { // ���������� � ��� ���������.
					last_node_ptr->next_node = own_ptr_new;
					last_node_ptr = own_ptr_new;
				}

				own_ptr_to_copy = own_ptr_to_copy->next_node;
			}

			total_number = owl_cont.total_number;
		}
	}

	// ������������ �����������.
	OneWayList(OneWayList&& owl_cont) : OneWayList()
	{
		std::cout << "One Way List move constructor" << std::endl;

		std::swap(first_node_ptr, owl_cont.first_node_ptr);
		std::swap(last_node_ptr, owl_cont.last_node_ptr);
		std::swap(total_number, owl_cont.total_number);
	}

	// �������� ����������� ������������.
	OneWayList& operator=(const OneWayList& owl_cont)
	{
		std::cout << "One Way List copy operator" << std::endl;

		if ((this != &owl_cont) && (owl_cont.first_node_ptr != nullptr)) {
			clear(); // ������ ������� ������ ����������.

			// � ����� ������� ����� ������� ���� ������� �������.
			OneWayNode<T>* own_ptr_to_copy = owl_cont.first_node_ptr;
			OneWayNode<T>* own_ptr_new = nullptr;

			while (own_ptr_to_copy != nullptr) {
				own_ptr_new = new OneWayNode(own_ptr_to_copy->data);

				if (first_node_ptr == nullptr) {
					first_node_ptr = own_ptr_new;
					last_node_ptr = own_ptr_new;
				}
				else {
					last_node_ptr->next_node = own_ptr_new;
					last_node_ptr = own_ptr_new;
				}

				own_ptr_to_copy = own_ptr_to_copy->next_node;
			}

			total_number = owl_cont.total_number;
		}

		return *this;
	}

	// ������������ ������������.
	OneWayList& operator=(OneWayList&& owl_cont) noexcept
	{
		std::cout << "One Way List move operator" << std::endl;

		if ((this != &owl_cont) && (owl_cont.first_node_ptr != nullptr)) {
			clear(); // ������ ������� ������ ����������.

			OneWayList temp{ std::move(owl_cont) };
			std::swap(first_node_ptr, temp.first_node_ptr);
			std::swap(last_node_ptr, temp.last_node_ptr);
			std::swap(total_number, temp.total_number);
		}

		return *this;
	}

	// ��������� ������� �� �������. ����� �� ������� �� �����������.
	T& operator[](const size_t& place) {
		OneWayNode<T>* current_node_ptr = get_node_by_place(place);

		return current_node_ptr->data;
	}

	// ����������� �����. ��������� ������� �� �������. ����� �� ������� �� �����������.
	const T& operator[](const size_t& place) const {
		OneWayNode<T>* current_node_ptr = get_node_by_place(place);

		return current_node_ptr->data;
	}

	// ����������
	~OneWayList() {
		std::cout << "One Way List destructor" << std::endl;

		// ����� ���� ����� �� ������� �� ����������.
		clear();

	}

	// ������� ����� ����������.
	void clear() {
		if (first_node_ptr == nullptr) {
			return;
		}

		OneWayNode<T>* current_node_ptr = first_node_ptr;
		OneWayNode<T>* next_to_delete_node_ptr = nullptr;

		// ������� ��� ���� � ������� �� ���������� � �������.
		while (current_node_ptr != nullptr) {
			next_to_delete_node_ptr = current_node_ptr->next_node;
			delete current_node_ptr;
			current_node_ptr = next_to_delete_node_ptr;
		}

		first_node_ptr = nullptr;
		last_node_ptr = nullptr;
		total_number = 0;
	}

	// ������ ���������� ��������� � ����������.
	size_t get_number() const { return total_number; }

	// �������� ����� ������� � ����� ����������.
	void push_back(const T& value) {
		OneWayNode<T>* own_ptr = new OneWayNode(value);

		if (first_node_ptr == nullptr) {
			first_node_ptr = own_ptr;
			last_node_ptr = own_ptr;
		}
		else {
			last_node_ptr->next_node = own_ptr;
			last_node_ptr = own_ptr;
		}
		
		++total_number;
	}

	// �������� ����� ������� � ��������� � ��������� �������.
	bool insert(const size_t& place, const T& value) {
		if (place > total_number) return false;

		if (place == total_number) { // ���������� � �����.
			push_back(value);
			return true;
		}

		OneWayNode<T>* own_ptr = new OneWayNode(value);

		OneWayNode<T>* current_node_ptr = first_node_ptr;
		OneWayNode<T>* prev_node_ptr = nullptr;

		size_t i = 0;
		while (i != place) {
			prev_node_ptr = current_node_ptr;
			current_node_ptr = current_node_ptr->next_node;
			++i;
		}

		if (current_node_ptr != nullptr) {
			own_ptr->next_node = current_node_ptr;
		}
		else {
			return false;
		}

		if (prev_node_ptr == nullptr) {
			first_node_ptr = own_ptr;
		}
		else {
			prev_node_ptr->next_node = own_ptr;
		}

		++total_number;

		return true;
	}

	// ������� ������� ���������� �� ��������� �������.
	bool erase(const size_t& place) {
		if (place >= total_number) return false; // ����� �� �������.
		if (first_node_ptr == nullptr) return false;

		OneWayNode<T>* current_node_ptr = first_node_ptr;
		OneWayNode<T>* prev_node_ptr = nullptr;
		OneWayNode<T>* next_node_ptr = current_node_ptr->next_node;

		size_t i = 0;
		while (i != place) {
			prev_node_ptr = current_node_ptr;
			current_node_ptr = current_node_ptr->next_node;
			
			if (current_node_ptr == nullptr) {
				return false; // ����� �������� �� ������ ����.
			}
			
			next_node_ptr = current_node_ptr->next_node;
			++i;
		}

		if (current_node_ptr == first_node_ptr) {
			if (first_node_ptr == last_node_ptr) { // ��������� ������������ �������.
				first_node_ptr = nullptr;
				last_node_ptr = nullptr;
			}
			else {
				first_node_ptr = next_node_ptr;
			}
		}
		else {
			if (current_node_ptr == last_node_ptr) {
				prev_node_ptr->next_node = nullptr;
				last_node_ptr = prev_node_ptr;
			}
			else {
				prev_node_ptr->next_node = next_node_ptr;
			}
		}

		delete current_node_ptr;

		--total_number;

		return true;
	}

	Iterator begin() const {
		return Iterator(first_node_ptr);
	}

	Iterator last_valid() const {
		if (last_node_ptr == nullptr) return Iterator(nullptr);
		return Iterator(last_node_ptr);
	}

	Iterator end() const {
		if (last_node_ptr == nullptr) return Iterator(nullptr);
		return Iterator(last_node_ptr->next_node);
	}

private: // ������� ��� ����������� �������������.

	// �������� ��������� �� ���� �� ������ ����� � ����������.
	OneWayNode<T>* get_node_by_place(const size_t& place) const {
		if (first_node_ptr == nullptr) {
			return nullptr;
		}

		OneWayNode<T>* current_node_ptr = first_node_ptr;

		size_t i = 0;
		while (i != place) {
			current_node_ptr = current_node_ptr->next_node;

			if (current_node_ptr == nullptr) {
				return nullptr;
			}

			++i;
		}

		return current_node_ptr;
	}
	

private:
	OneWayNode<T> *first_node_ptr; // ��������� �� ������ ����.
	OneWayNode<T> *last_node_ptr;  // ��������� �� ��������� ����.

	size_t total_number;

	Iterator owl_iterator;
};

// ����� ���� ��������� ���������� � �������.
template <typename T>
std::ostream& operator<<(std::ostream& os, const OneWayList<T>& lcont) {
	for (auto iter = lcont.begin(); iter != lcont.end(); ++iter) {
		os << iter.get();
		if (iter != lcont.last_valid()) { os << ", "; }
	}

	return os;
}

