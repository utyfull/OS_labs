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

TEST_F(FileTest, CheckSumFromFile) {

    SetFileContent("1 2 3 4 5");
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

    EXPECT_EQ(output.str(), "Сумма: 15\n");
}
