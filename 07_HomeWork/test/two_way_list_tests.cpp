#include "two_way_list_container.h"
#include "test_class.h"

#include <gtest/gtest.h>

#include <exception>
#include <stdexcept>

// Тест создания контейнера.
TEST(TwoWayList, CreateContainer) {
    // Arrange
    TwoWayList<int> list_cont(5);

    // Act 
    
    // Assert
    ASSERT_TRUE( !list_cont.empty());
}

// Вставка элементов в конец. 
TEST(TwoWayList, PushBack) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(2);
    list_cont.push_back(13);
    list_cont.push_back(-1);

    // Assert
    ASSERT_TRUE(list_cont.get_number() == 3);
    ASSERT_EQ(list_cont[0], 2);
    ASSERT_EQ(list_cont[1], 13);
    ASSERT_EQ(list_cont[2], -1);
    EXPECT_EQ(list_cont[2], -2); // Намеренно.
}

// Вставка элементов в начало. 
TEST(TwoWayList, PushFront) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(2);
    list_cont.push_front(89);
    list_cont.push_front(135);
    list_cont.push_front(-9);

    // Assert
    ASSERT_TRUE(list_cont.get_number() == 4);
    ASSERT_EQ(list_cont[0], -9);
    ASSERT_EQ(list_cont[1], 135);
    ASSERT_EQ(list_cont[2], 89);
    ASSERT_EQ(list_cont[3], 2);
}

// Вставка элементов в середину. 
TEST(TwoWayList, InsertInTheMiddle) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(1);
    list_cont.push_back(3);
    list_cont.push_back(4);
    list_cont.insert(1, 2);

    // Assert
    ASSERT_TRUE(list_cont.get_number() == 4);
    ASSERT_EQ(list_cont[0], 1);
    ASSERT_EQ(list_cont[1], 2);
    ASSERT_EQ(list_cont[2], 3);
    ASSERT_EQ(list_cont[3], 4);
}

// Удаление элементов из конца. 
TEST(TwoWayList, DeleteLast) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(8732);
    list_cont.push_back(149);
    list_cont.push_back(-45);

    list_cont.pop_back();
    list_cont.pop_back();

    // Assert
    ASSERT_TRUE(list_cont.get_number() == 1);
    ASSERT_EQ(list_cont[0], 8732);
}

// Удаление элементов из начала. 
TEST(TwoWayList, DeleteFirst) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(8732);
    list_cont.push_back(149);
    list_cont.push_back(-45);

    list_cont.pop_front();
    list_cont.pop_front();

    // Assert
    ASSERT_TRUE(list_cont.get_number() == 1);
    ASSERT_EQ(list_cont[0], -45);
}

// Удаление элементов из середины. 
TEST(TwoWayList, DeleteFromTheMiddle) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(8732);
    list_cont.push_back(149);
    list_cont.push_back(-45);

    list_cont.erase(1);

    // Assert
    ASSERT_TRUE(list_cont.get_number() == 2);
    ASSERT_EQ(list_cont[0], 8732);
    ASSERT_EQ(list_cont[1], -45);
}

// Проверка получения элемента и выхода за пределы контейнера.
TEST(TwoWayList, CheckRange) {
    // Arrange
    TwoWayList<int> list_cont;

    // Act 
    list_cont.push_back(8732);
    list_cont.push_back(149);
    list_cont.push_back(-45);
    list_cont.pop_back();

    // Assert
    ASSERT_EQ(list_cont.get_number(), 2);
    EXPECT_THROW(list_cont.at(3) = 3, std::out_of_range);
}

// Проверка копирования одного контейнера в другой. 
TEST(TwoWayList, CopyContainer) {
    // Arrange
    TwoWayList<int> list_cont_one;
    for (int i = 0; i < 9; ++i) {
        list_cont_one.push_back(i + i);
    }

    // Act
    TwoWayList<int> list_cont_two(list_cont_one); // Конструктор копирования.

    TwoWayList<int> list_cont_three;
    list_cont_three = list_cont_one; // Оператор копирования.

    // Assert.
    for (int i = 0; i < 9; ++i) {
        ASSERT_EQ(list_cont_one[i], list_cont_two[i]);
        ASSERT_EQ(list_cont_one[i], list_cont_three[i]);
    }
}

// Проверка вызова деструктора при удалении элементов из контейнера. 
TEST(TwoWayList, CheckDestructor) {
    // Пришлось немного хитрую схему проверки составить.

    // Arrange
    TwoWayList<TestClass> list_cont;
    int* test_pp = nullptr;

    // Act
    list_cont.push_back(TestClass(3));

    list_cont[0].set_ptr_value(&test_pp);
    list_cont[0].get_ptr_value();

    // Assert
    ASSERT_TRUE(test_pp != nullptr);

    // Act
    list_cont.pop_back();

    // Assert
    ASSERT_TRUE(test_pp == nullptr);
}

// Проверка перемещения одного контейнера в другой. 
TEST(TwoWayList, MoveContainer) {
    // Arrange
    TwoWayList<int> list_cont_one;
    for (int i = 0; i < 12; ++i) {
        list_cont_one.push_back(i + i);
    }

    // Act
    TwoWayList<int> list_cont_two(std::move(list_cont_one)); // Конструктор перемещения.


    // Assert.
    ASSERT_EQ(list_cont_one.get_number(), 0);

    ASSERT_EQ(list_cont_two.get_number(), 12);
    for (int i = 0; i < 7; ++i) {
        ASSERT_EQ(list_cont_two[i], i + i);
    }
}

/*
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/