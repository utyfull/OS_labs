#include "lab1.h"


int main() {
    int pipefd[2]; // дескрипторы pipe

    if (pipe(pipefd) == -1) {
        std::cerr << "Ошибка при создании pipe" << std::endl;
        return 1;
    }

    std::cout << "Введите имя файла: ";
    std::string filename;
    std::cin >> filename;

    CreateChildProcess(filename, pipefd);
    ReadFromPipe(pipefd);

    wait(nullptr);
    
    return 0;
}