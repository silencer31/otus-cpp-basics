#include "serial_container.h"
#include "one_way_list_container.h"
#include "two_way_list_container.h"

// Демонстрация работы контейнера с последовательным расположением данных.
void test_serial_container() {
	std::cout << "Serial container testing\n" << std::endl;

	SerialContainer<int> scont_1;

	for (int i = 0; i < 10; ++i) {
		scont_1.push_back(i);
	}
	
	std::cout << scont_1 << std::endl;
	std::cout << "Container size: " << scont_1.get_number() << std::endl;
	std::cout << "Container capacity: " << scont_1.get_capacity() << std::endl;

	// удаление третьего (по счёту), пятого и седьмого элементов.
	scont_1.erase(2);
	scont_1.erase(4 - 1); // Далее добавляем -1 и -2, т.к. после каждого удаления изначальная очерёдность элементов меняется.
	scont_1.erase(6 - 2);

	std::cout << scont_1 << std::endl;
	std::cout << "Container size: " << scont_1.get_number() << std::endl;
	std::cout << "Container capacity: " << scont_1.get_capacity() << std::endl;

	// добавление элемента 10 в начало контейнера.
	scont_1.insert(0, 10);

	std::cout << scont_1 << std::endl;
	std::cout << "Container size: " << scont_1.get_number() << std::endl;
	std::cout << "Container capacity: " << scont_1.get_capacity() << std::endl;

	// добавление элемента 20 в середину контейнера.
	size_t place_in_the_middle = static_cast<size_t>(scont_1.get_number() / 2);
	scont_1.insert( place_in_the_middle, 20 );

	std::cout << scont_1 << std::endl;
	std::cout << "Container size: " << scont_1.get_number() << std::endl;
	std::cout << "Container capacity: " << scont_1.get_capacity() << std::endl;

	// добавление элемента 30 в конец контейнера
	scont_1.push_back(30);

	std::cout << "scont 1: " << scont_1 << std::endl;
	std::cout << "Container size: " << scont_1.get_number() << std::endl;
	std::cout << "Container capacity: " << scont_1.get_capacity() << std::endl;

	std::cout << std::endl;

	SerialContainer<int> scont_2(5);
	scont_2.push_back(11);
	std::cout << "scont 2: " << scont_2 << std::endl;

	SerialContainer<int> scont_3(std::move(scont_2));
	scont_3.push_back(14);
	std::cout << "scont 3: " << scont_3 << std::endl;

	SerialContainer<int> scont_4(6);
	scont_4 = std::move(scont_3);
	std::cout << "scont 4: " << scont_4 << std::endl;
	std::cout << std::endl;
	//std::cout << scont_3 << std::endl;

}

// Демонстрация работы контейнера, реализующего однонаправленный список.
void test_one_way_container() {
	std::cout << "\nOne Way List container testing\n" << std::endl;
	
	OneWayList<int> owl_cont_1;

	for (int i = 0; i < 10; ++i) {
		owl_cont_1.push_back(i);
	}

	std::cout << owl_cont_1 << std::endl;
	std::cout << "Container size: " << owl_cont_1.get_number() << std::endl;

	// удаление третьего (по счёту), пятого и седьмого элементов.
	owl_cont_1.erase(2);
	owl_cont_1.erase(4 - 1); // Далее добавляем -1 и -2, т.к. после каждого удаления изначальная очерёдность элементов меняется.
	owl_cont_1.erase(6 - 2);

	std::cout << owl_cont_1 << std::endl;
	std::cout << "Container size: " << owl_cont_1.get_number() << std::endl;

	// добавление элемента 10 в начало контейнера.
	owl_cont_1.insert(0, 10);

	std::cout << owl_cont_1 << std::endl;
	std::cout << "Container size: " << owl_cont_1.get_number() << std::endl;

	// добавление элемента 20 в середину контейнера.
	size_t place_in_the_middle = static_cast<size_t>(owl_cont_1.get_number() / 2);
	owl_cont_1.insert(place_in_the_middle, 20);

	std::cout << owl_cont_1 << std::endl;
	std::cout << "Container size: " << owl_cont_1.get_number() << std::endl;

	// добавление элемента 30 в конец контейнера
	owl_cont_1.push_back(30);

	std::cout << owl_cont_1 << std::endl;
	std::cout << "Container size: " << owl_cont_1.get_number() << std::endl;

	OneWayList<int> owl_cont_2(std::move(owl_cont_1));
	owl_cont_2[3] = 13;
	std::cout << owl_cont_2 << std::endl;

	std::cout << std::endl;
}

// Демонстрация работы контейнера, реализующего двунаправленный список.
void test_two_way_container() {
	std::cout << "\nTwo Way List container testing\n" << std::endl;
	
	TwoWayList<int> twl_cont_1;
	
	for (int i = 0; i < 10; ++i) {
		twl_cont_1.push_back(i);
	}

	std::cout << twl_cont_1 << std::endl;
	std::cout << "Container size: " << twl_cont_1.get_number() << std::endl;

	// удаление третьего (по счёту), пятого и седьмого элементов.
	twl_cont_1.erase(2);
	twl_cont_1.erase(4 - 1); // Далее добавляем -1 и -2, т.к. после каждого удаления изначальная очерёдность элементов меняется.
	twl_cont_1.erase(6 - 2);

	std::cout << twl_cont_1 << std::endl;
	std::cout << "Container size: " << twl_cont_1.get_number() << std::endl;

	// добавление элемента 10 в начало контейнера.
	twl_cont_1.insert(0, 10);

	std::cout << twl_cont_1 << std::endl;
	std::cout << "Container size: " << twl_cont_1.get_number() << std::endl;

	// добавление элемента 20 в середину контейнера.
	size_t place_in_the_middle = static_cast<size_t>(twl_cont_1.get_number() / 2);
	twl_cont_1.insert(place_in_the_middle, 20);

	std::cout << twl_cont_1 << std::endl;
	std::cout << "Container size: " << twl_cont_1.get_number() << std::endl;

	// добавление элемента 30 в конец контейнера
	twl_cont_1.push_back(30);

	std::cout << twl_cont_1 << std::endl;
	std::cout << "Container size: " << twl_cont_1.get_number() << std::endl;

	TwoWayList<int> twl_cont_2;
	twl_cont_2 = std::move(twl_cont_1);
	twl_cont_2[4] = 11414;
	std::cout << twl_cont_2 << std::endl;

	std::cout << std::endl;
}


int main()
{
	test_serial_container();
	test_one_way_container();
	test_two_way_container();

	return 0;
}