#include "lab1.h"


void process_data(int write_fd) {
    std::string line;
    int counter{0};

    while (std::getline(std::cin, line)) {
        // поток, а почему бы и нет, меньше писать
        std::istringstream iss(line);
        float num, sum = 0;

        if (line.empty()) {
            std::cout << "Пустая строка." << std::endl;
            continue; 
        }

        while (iss >> num) {
            sum += num;
        }

        std::ostringstream result;
        result << "Сумма: " << sum << std::endl;

        std::string result_str = result.str();
        write(write_fd, result_str.c_str(), result_str.size());
    }

    close(write_fd);
}

pid_t create_child_process(const std::string& filename, int pipefd[2]) {
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Ошибка при создании процесса" << std::endl;
        exit(1);
    }

    if (pid == 0) { // дочерний процесс
        int file = open(filename.c_str(), O_RDONLY);
        if (file == -1) {
            std::cerr << "Ошибка при открытии файла" << std::endl;
            exit(1);
        }

        dup2(file, STDIN_FILENO);
        close(file);

        close(pipefd[0]); 
        process_data(pipefd[1]); 

        _exit(0);
    }

    return pid; 
}

void read_from_pipe(int pipefd[2]) {
    close(pipefd[1]);

    // чтение данных из pipe и вывод их на экран
    char buffer[1024];
    int n;
    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, n);
    }

    close(pipefd[0]);
}