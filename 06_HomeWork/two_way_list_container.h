#pragma once

#include <iostream>

// ���������, ����������� ��������������� ������.

template <typename T>
struct TwoWayNode {
	TwoWayNode() : next_node{ nullptr }, prev_node{ nullptr} {}
	explicit TwoWayNode(const T& value) : next_node{ nullptr }, prev_node{ nullptr }, data{ value } {}

	TwoWayNode* next_node;
	TwoWayNode* prev_node;
	T data;
};

template <typename T>
class TwoWayList {
public:
	struct Iterator {
		Iterator() : two_way_node_ptr{ nullptr } {}

		explicit Iterator(TwoWayNode<T>* own_ptr) : two_way_node_ptr{ own_ptr } {}

		TwoWayNode<T>* operator++() {
			two_way_node_ptr = two_way_node_ptr->next_node;
			return two_way_node_ptr;
		}

		TwoWayNode<T>* operator--() {
			two_way_node_ptr = two_way_node_ptr->prev_node;
			return two_way_node_ptr;
		}

		T get() {
			return two_way_node_ptr->data;
		}

		bool operator==(const Iterator& another_iter) {
			return (two_way_node_ptr == another_iter.two_way_node_ptr);
		}

		bool operator!=(const Iterator& another_iter) {
			return !(two_way_node_ptr == another_iter.two_way_node_ptr);
		}

	private:
		TwoWayNode<T>* two_way_node_ptr;
	};

	TwoWayList() : first_node_ptr{ nullptr }, last_node_ptr{ nullptr }, total_number{ 0 } {
		std::cout << "Two Way List default constructor" << std::endl;
	}

	// ����������� � ���������� - �������� ������� ��������.
	explicit TwoWayList(const T& first_value) : TwoWayList()
	{
		std::cout << "Two Way List explicit constructor" << std::endl;

		TwoWayNode<T> *twn_ptr = new TwoWayNode(first_value);
		
		first_node_ptr = twn_ptr;
		last_node_ptr = twn_ptr;

		total_number = 1;
	}

	// ���������� �����������.
	TwoWayList(const TwoWayList& twl_cont) : TwoWayList() {
		std::cout << "Two Way List copy constructor" << std::endl;

		if (twl_cont.first_node_ptr != nullptr) {
			
			// � ����� ������� ����� ������� ���� ������� �������.
			TwoWayNode<T>* twn_ptr_to_copy = twl_cont.first_node_ptr;
			TwoWayNode<T>* twn_ptr_new = nullptr;

			while (twn_ptr_to_copy != nullptr) {
				twn_ptr_new = new TwoWayNode(twn_ptr_to_copy->data);

				if (first_node_ptr == nullptr) { // ������ ������.
					first_node_ptr = twn_ptr_new;
					last_node_ptr = twn_ptr_new;
				}
				else { // ���������� � ��� ���������� ����.
					twn_ptr_new->prev_node = last_node_ptr;
					last_node_ptr->next_node = twn_ptr_new;
					last_node_ptr = twn_ptr_new;
				}

				twn_ptr_to_copy = twn_ptr_to_copy->next_node;
			}

			total_number = twl_cont.total_number;
		}
	}

	// ������������ �����������.
	TwoWayList(TwoWayList&& twl_cont) : TwoWayList()
	{
		std::cout << "Two Way List move constructor" << std::endl;

		std::swap(first_node_ptr, twl_cont.first_node_ptr);
		std::swap(last_node_ptr, twl_cont.last_node_ptr);
		std::swap(total_number, twl_cont.total_number);
	}

	// �������� ����������� ������������.
	TwoWayList& operator=(const TwoWayList& twl_cont)
	{
		std::cout << "Two Way List copy operator" << std::endl;

		if ((this != &twl_cont) && (twl_cont.first_node_ptr != nullptr)) {
			clear(); // ������ ������� ������ ����������.

			// � ����� ������� ����� ������� ���� ������� �������.
			TwoWayNode<T>* twn_ptr_to_copy = twl_cont.first_node_ptr;
			TwoWayNode<T>* twn_ptr_new = nullptr;

			while (twn_ptr_to_copy != nullptr) {
				twn_ptr_new = new TwoWayNode(twn_ptr_to_copy->data);

				if (first_node_ptr == nullptr) {
					first_node_ptr = twn_ptr_new;
					last_node_ptr = twn_ptr_new;
				}
				else {
					twn_ptr_new->prev_node = last_node_ptr;
					last_node_ptr->next_node = twn_ptr_new;
					last_node_ptr = twn_ptr;
				}

				twn_ptr_to_copy = twn_ptr_to_copy->next_node;
			}

			total_number = twl_cont.total_number;
		}

		return *this;
	}

	// ������������ ������������.
	TwoWayList& operator=(TwoWayList&& twl_cont) noexcept
	{
		std::cout << "Two Way List move operator" << std::endl;

		if ((this != &twl_cont) && (twl_cont.first_node_ptr != nullptr)) {
			clear(); // ������ ������� ������ ����������.

			TwoWayList temp{ std::move(twl_cont) };
			std::swap(first_node_ptr, temp.first_node_ptr);
			std::swap(last_node_ptr, temp.last_node_ptr);
			std::swap(total_number, temp.total_number);
		}

		return *this;
	}

	// ��������� ������� �� �������. ����� �� ������� �� �����������.
	T& operator[](const size_t& place) {
		TwoWayNode<T>* current_node_ptr = get_node_by_place(place);

		return current_node_ptr->data;
	}

	// ��������� ������� �� �������. ����� �� ������� �� �����������.
	const T& operator[](const size_t& place) const {
		TwoWayNode<T>* current_node_ptr = get_node_by_place(place);

		return current_node_ptr->data;
	}

	// ����������
	~TwoWayList() {
		std::cout << "Two Way List destructor" << std::endl;

		// ����� ���� ����� �� ���������� �� �������.
		clear();

	}

	// ������� ����� ����������.
	void clear() {
		if (first_node_ptr == nullptr) {
			return;
		}

		TwoWayNode<T> *current_node_ptr = last_node_ptr;
		TwoWayNode<T> *next_to_delete_node_ptr = nullptr;

		// ������� ��� ���� � ������� �� ���������� � �������.
		while (current_node_ptr != nullptr) {
			next_to_delete_node_ptr = current_node_ptr->prev_node;
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
		TwoWayNode<T>* twn_ptr = new TwoWayNode(value);
		
		if (first_node_ptr == nullptr) {
			first_node_ptr = twn_ptr;
			last_node_ptr = twn_ptr;
		}
		else {
			twn_ptr->prev_node = last_node_ptr;
			last_node_ptr->next_node = twn_ptr;
			last_node_ptr = twn_ptr;
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

		TwoWayNode<T>* twn_ptr = new TwoWayNode(value);

		TwoWayNode<T>* current_node_ptr = first_node_ptr;
		TwoWayNode<T>* prev_node_ptr = nullptr;

		size_t i = 0;
		while (i != place) {
			prev_node_ptr = current_node_ptr;
			current_node_ptr = current_node_ptr->next_node;
			++i;
		}

		if (current_node_ptr != nullptr) {
			current_node_ptr->prev_node = twn_ptr;
			twn_ptr->next_node = current_node_ptr;
		}
		else {
			return false;
		}

		if (prev_node_ptr == nullptr) {
			first_node_ptr = twn_ptr;
		}
		else {
			prev_node_ptr->next_node = twn_ptr;
		}

		++total_number;

		return true;
	}

	// ������� ������� ���������� �� ��������� �������.
	bool erase(const size_t& place) {
		if (place >= total_number) return false; // ����� �� �������.
		if (first_node_ptr == nullptr) return false;

		TwoWayNode<T>* current_node_ptr = first_node_ptr;
		TwoWayNode<T>* prev_node_ptr = nullptr;
		TwoWayNode<T>* next_node_ptr = current_node_ptr->next_node;

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

		if (next_node_ptr != nullptr) {
			next_node_ptr->prev_node = prev_node_ptr;
		}

		if (current_node_ptr == first_node_ptr) {
			if (first_node_ptr == last_node_ptr) { // ��������� ������������ �������.
				first_node_ptr = nullptr;
				last_node_ptr = nullptr;
			}
			else {
				first_node_ptr = next_node_ptr;
				first_node_ptr->prev_node = nullptr;
			}
		}
		else {
			if (current_node_ptr == last_node_ptr) {
				prev_node_ptr->next_node = nullptr;
				last_node_ptr = prev_node_ptr;
			}
			else {
				next_node_ptr->prev_node = prev_node_ptr;
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
	TwoWayNode<T>* get_node_by_place(const size_t& place) const {
		if (first_node_ptr == nullptr) {
			return nullptr;
		}

		TwoWayNode<T>* current_node_ptr = first_node_ptr;

		// �.�. ������ ���������������, ����� ����� ��������� ����� � ����� ��� ������ ������������� ������� ������� ������. 
		size_t half_way_len = static_cast<size_t>(total_number / 2);
		size_t i = 0;

		if (place < half_way_len) {
			current_node_ptr = first_node_ptr;

			while (i != place) {
				current_node_ptr = current_node_ptr->next_node;

				if (current_node_ptr == nullptr) {
					return nullptr;
				}

				++i;
			}
		}
		else {
			current_node_ptr = last_node_ptr;
			i = total_number - 1;

			while (i != place) {
				current_node_ptr = current_node_ptr->prev_node;

				if (current_node_ptr == nullptr) {
					return nullptr;
				}

				--i;
			}
		}

		return current_node_ptr;
	}

private:
	TwoWayNode<T> *first_node_ptr; // ��������� �� ������ ����.
	TwoWayNode<T> *last_node_ptr;  // ��������� �� ��������� ����.

	size_t total_number;
};

// ����� ���� ��������� ���������� � �������.
template <typename T>
std::ostream& operator<<(std::ostream& os, const TwoWayList<T>& lcont) {
	for (auto iter = lcont.begin(); iter != lcont.end(); ++iter) {
		os << iter.get();
		if (iter != lcont.last_valid()) { os << ", "; }
	}

	return os;
}