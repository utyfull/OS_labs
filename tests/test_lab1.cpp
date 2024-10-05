#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include <random>
#include "lab1.h"

class TempFile {
public:
    TempFile(const std::string& content) {

        std::srand(static_cast<unsigned>(std::time(0)));

        fileName = "test_file_" + std::to_string(std::rand()) + ".txt"; 

        std::ofstream outFile(fileName);
        if (!outFile) {
            throw std::runtime_error("Не удалось создать временный файл");
        }
        outFile << content;
        outFile.close();
    }

    ~TempFile() {

        std::remove(fileName.c_str());
    }

    std::string getFileName() const {
        return fileName;
    }

private:
    std::string fileName;
};

TEST(FileTest, StandartPositiveSum) {
    TempFile tempFile("1.2 2.2 3.2 4.2 5.2");

    std::ostringstream output;

    MainTestFunction(tempFile.getFileName(), output);

    EXPECT_EQ(output.str(), "Сумма: 16\n");
}

TEST(FileTest, StandartNegativeSum) {

    TempFile tempFile("-1.1 -1.1 -2.2 -1.1");

    std::ostringstream output;

    MainTestFunction(tempFile.getFileName(), output);

    EXPECT_EQ(output.str(), "Сумма: -5.5\n");
}

TEST(FileTest, StandartMeshSum) {

    TempFile tempFile("-1.1 1.25 2.4 -1.05");

    std::ostringstream output;

    MainTestFunction(tempFile.getFileName(), output);

    EXPECT_EQ(output.str(), "Сумма: 1.5\n");
}

TEST(FileTest, OnlyZeroSum) {

    TempFile tempFile("0 0 0 0");

    std::ostringstream output;

    MainTestFunction(tempFile.getFileName(), output);

    EXPECT_EQ(output.str(), "Сумма: 0\n");
}