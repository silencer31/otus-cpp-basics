#include "serial_container.h"
#include "test_class.h"

#include <gtest/gtest.h>
#include <exception>
#include <stdexcept>

// Тест создания контейнера.
TEST(SerialContainer, CreateContainer) {
    // Arrange
    SerialContainer<int> scont(5);

    // Act 
    int *data_ptr = nullptr;
    data_ptr = scont.get_data();

    // Assert
    ASSERT_TRUE(data_ptr != nullptr);
}

// Вставка элементов в конец. 
TEST(SerialContainer, PushBack) {
    // Arrange
    SerialContainer<int> scont;

    // Act 
    scont.push_back(2);
    scont.push_back(13);
    scont.push_back(-1);

    // Assert
    ASSERT_TRUE(scont.get_number() == 3);
    ASSERT_EQ(scont[0], 2);
    ASSERT_EQ(scont[1], 13);
    ASSERT_EQ(scont[2], -1);
    EXPECT_EQ(scont[2], -2); // Намеренно.
}

// Вставка элементов в начало. 
TEST(SerialContainer, PushFront) {
    // Arrange
    SerialContainer<int> scont(3);

    // Act 
    scont.push_back(2);
    scont.push_front(89);
    scont.push_front(135);
    scont.push_front(-9);

    // Assert
    ASSERT_TRUE(scont.get_number() == 4);
    ASSERT_EQ(scont[0], -9);
    ASSERT_EQ(scont[1], 135);
    ASSERT_EQ(scont[2], 89);
    ASSERT_EQ(scont[3], 2);
}

// Вставка элементов в середину. 
TEST(SerialContainer, InsertInTheMiddle) {
    // Arrange
    SerialContainer<int> scont(4);

    // Act 
    scont.push_back(1);
    scont.push_back(3);
    scont.push_back(4);
    scont.insert(1, 2);

    // Assert
    ASSERT_TRUE(scont.get_number() == 4);
    ASSERT_EQ(scont[0], 1);
    ASSERT_EQ(scont[1], 2);
    ASSERT_EQ(scont[2], 3);
    ASSERT_EQ(scont[3], 4);
}

// Удаление элементов из конца. 
TEST(SerialContainer, DeleteLast) {
    // Arrange
    SerialContainer<int> scont(3);

    // Act 
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);

    scont.pop_back();
    scont.pop_back();

    // Assert
    ASSERT_TRUE(scont.get_number() == 1);
    ASSERT_EQ(scont[0], 8732);
}

// Удаление элементов из начала. 
TEST(SerialContainer, DeleteFirst) {
    // Arrange
    SerialContainer<int> scont(3);

    // Act 
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);

    scont.pop_front();
    scont.pop_front();

    // Assert
    ASSERT_TRUE(scont.get_number() == 1);
    ASSERT_EQ(scont[0], -45);
}

// Удаление элементов из середины. 
TEST(SerialContainer, DeleteFromTheMiddle) {
    // Arrange
    SerialContainer<int> scont(3);

    // Act 
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);

    scont.erase(1);

    // Assert
    ASSERT_TRUE(scont.get_number() == 2);
    ASSERT_EQ(scont[0], 8732);
    ASSERT_EQ(scont[1], -45);
}

// Проверка получения элемента и выхода за пределы контейнера.
TEST(SerialContainer, CheckRange) {
    // Arrange
    SerialContainer<int> scont(4);

    // Act 
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);
    scont.pop_back();

    // Assert
    ASSERT_EQ( scont.get_number(), 2);
    EXPECT_THROW( scont.at(3)=3, std::out_of_range);
}

// Проверка копирования одного контейнера в другой. 
TEST(SerialContainer, CopyContainer) {
    // Arrange
    SerialContainer<int> scont_one(7);
    for (int i = 0; i < 7; ++i) {
        scont_one.push_back(i+i);
    }

    // Act
    SerialContainer<int> scont_two(scont_one); // Конструктор копирования.

    SerialContainer<int> scont_three;
    scont_three = scont_one; // Оператор копирования.

    // Assert.
    for (int i = 0; i < 7; ++i) {
        ASSERT_EQ(scont_one[i], scont_two[i]);
        ASSERT_EQ(scont_one[i], scont_three[i]);
    }
}

// Проверка вызова деструктора при удалении элементов из контейнера. 
TEST(SerialContainer, CheckDestructor) {
    // Пришлось немного хитрую схему проверки составить.
    
    // Arrange
    SerialContainer<TestClass> scont(1);
    int* test_pp = nullptr;
    
    // Act
    scont.push_back(TestClass(3));

    scont[0].set_ptr_value(&test_pp);
    scont[0].get_ptr_value();
    
    // Assert
    ASSERT_TRUE(test_pp != nullptr);
 
     // Act
    scont.pop_back();
 
    // Assert
    ASSERT_TRUE( test_pp == nullptr);
}

// Проверка перемещения одного контейнера в другой. 
TEST(SerialContainer, MoveContainer) {
    // Arrange
    SerialContainer<int> scont_one(7);
    for (int i = 0; i < 7; ++i) {
        scont_one.push_back(i + i);
    }

    // Act
    SerialContainer<int> scont_two(std::move(scont_one)); // Конструктор перемещения.


    // Assert.
    ASSERT_EQ(scont_one.get_number(), 0);

    ASSERT_EQ(scont_two.get_number(), 7);
    for (int i = 0; i < 7; ++i) {
        ASSERT_EQ(scont_two[i], i + i);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}