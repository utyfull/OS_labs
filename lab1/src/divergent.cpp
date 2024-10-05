#include "lab1.h"

void ProcessData(int writeFd) {
    float num, sum = 0;

    while (std::cin >> num) {
        sum += num;
    }

    std::string resultStr = std::format("Сумма: {}\n", sum);

    ssize_t bytesWritten = write(writeFd, resultStr.c_str(), resultStr.size());

    if (bytesWritten == -1) {
        std::cerr << std::format("Ошибка при записи: {}\n", strerror(errno));
    } else if (static_cast<size_t>(bytesWritten) < resultStr.size()) {
         std::cerr << std::format("Предупреждение: записано только {} байт(а) из {}\n", 
                                 bytesWritten, resultStr.size());
    }

    close(writeFd);
}

int main(int, char* argv[]) {

    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        std::cerr << "Ошибка при открытии файла" << std::endl;
        exit(1);
    }

    dup2(file, STDIN_FILENO);
    close(file);

    int writeFd = atoi(argv[2]);
    ProcessData(writeFd); 

    return 0;
}
