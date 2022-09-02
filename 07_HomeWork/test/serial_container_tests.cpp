#include "serial_container.h"

#include <gtest/gtest.h>
#include <exception>
#include <stdexcept>
#include <vector>

// Тест создания контейнера.
TEST(SerialContainer, CreateContainer) {
    // Arrange
    SerialContainer<int> scont(5);

    // Act (empty for this test)
    int *data_ptr = nullptr;
    data_ptr = scont.get_data();

    // Assert
    ASSERT_TRUE(data_ptr != nullptr);
}

// Вставка элементов в конец. 
TEST(SerialContainer, PushBack) {
    // Arrange
    SerialContainer<int> scont;

    // Act (empty for this test)
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

    // Act (empty for this test)
    scont.push_back(2);
    scont.insert(0, 89);
    scont.insert(0, 135);
    scont.insert(0, -9);

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

    // Act (empty for this test)
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

    // Act (empty for this test)
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);

    scont.erase(scont.get_number() - 1);
    scont.erase(scont.get_number() - 1);

    // Assert
    ASSERT_TRUE(scont.get_number() == 1);
    ASSERT_EQ(scont[0], 8732);
}

// Удаление элементов из начала. 
TEST(SerialContainer, DeleteFirst) {
    // Arrange
    SerialContainer<int> scont(3);

    // Act (empty for this test)
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);

    scont.erase( 0 );
    scont.erase( 0 );

    // Assert
    ASSERT_TRUE(scont.get_number() == 1);
    ASSERT_EQ(scont[0], -45);
}

// Удаление элементов из середины. 
TEST(SerialContainer, DeleteFromTheMiddle) {
    // Arrange
    SerialContainer<int> scont(3);

    // Act (empty for this test)
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

    // Act (empty for this test)
    scont.push_back(8732);
    scont.push_back(149);
    scont.push_back(-45);
    scont.pop_back();

    // Assert
    ASSERT_EQ( scont.get_number(), 2);
    EXPECT_THROW( scont.at(3)=3, std::out_of_range);
}
/*
TEST(List, PushBack) {
    // Arrange
    const size_t count = 10;
    otus::List<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list.size(), count);
    ASSERT_FALSE(list.empty());
}

TEST(Lst, PopBack) {
    // Arrange 
    const size_t count = 10;
    otus::List<size_t> list;

    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Act
    for (size_t i = 0; i < count; ++i) {
        list.pop_back();
    }

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}
*/
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}