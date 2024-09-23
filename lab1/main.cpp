#include "lab1.h"


int main() {
    int pipefd[2]; // lескрипторы pipe
    pid_t pid;

    if (pipe(pipefd) == -1) {
        std::cerr << "Ошибка при создании pipe" << std::endl;
        return 1;
    }

    std::cout << "Введите имя файла: ";
    std::string filename;
    std::cin >> filename;

    pid = create_child_process(filename, pipefd);

    read_from_pipe(pipefd);

    wait(nullptr);

    return 0;
}