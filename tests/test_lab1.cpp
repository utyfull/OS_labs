#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include "lab1.h"

class FileTest : public ::testing::Test {
protected:
    std::string fileName;
    std::string fileContent;

    void SetFileContent(const std::string& content) {
        fileContent = content;
    }

    void SetUp() override {
        fileName = "test_file.txt"; 
    }

    void TearDown() override {
        std::remove(fileName.c_str());
    }

    void CreateTestFile(const std::string& fileName, const std::string& content) {
        std::ofstream outFile(fileName);
        outFile << content;
        outFile.close();
    }
};

TEST_F(FileTest, StandartPositiveSum) {

    SetFileContent("1.2 2.2 3.2 4.2 5.2");
    CreateTestFile(fileName, fileContent);

    // Создаем строковый поток для перехвата вывода std::cout
    std::ostringstream output;
    
    // Сохраняем старый буфер std::cout
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    
    // Перенаправляем std::cout на наш строковый поток
    std::cout.rdbuf(output.rdbuf());

    // Вызываем тестируемую функцию
    MainTestFunction(fileName);

    // Восстанавливаем оригинальный std::cout
    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(output.str(), "Сумма: 16\n");
}

TEST_F(FileTest, StandartNegativeSum) {

    SetFileContent("-1.1 -1.1 -2.2 -1.1");
    CreateTestFile(fileName, fileContent);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    MainTestFunction(fileName);

    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(output.str(), "Сумма: -5.5\n");
}

TEST_F(FileTest, StandartMeshSum) {

    SetFileContent("-1.1 1.25 2.4 -1.05");
    CreateTestFile(fileName, fileContent);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    MainTestFunction(fileName);

    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(output.str(), "Сумма: 1.5\n");
}

TEST_F(FileTest, OnlyZeroSum) {

    SetFileContent("0 0 0 0");
    CreateTestFile(fileName, fileContent);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    MainTestFunction(fileName);

    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(output.str(), "Сумма: 0\n");
}