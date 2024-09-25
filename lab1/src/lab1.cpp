#include "lab1.h"


void ProcessData(int write_fd) {
    std::string line;

    while (std::getline(std::cin, line)) {
        // поток, а почему бы и нет, меньше писать
        std::istringstream iss(line);
        float num, sum = 0;

        if (line.empty()) {
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

void CreateChildProcess(const std::string& filename, int pipefd[2]) {
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
        ProcessData(pipefd[1]); 

        _exit(0);
    }
}

void ReadFromPipe(int pipefd[2]) {
    close(pipefd[1]);

    // чтение данных из pipe и вывод их на экран
    char buffer[1024];
    int n;
    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        std::cout.write(buffer, n);  
    }

    close(pipefd[0]);
}

void MainTestFunction(const std::string& filename) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        std::cerr << "Ошибка при создании pipe" << std::endl;
        exit(EXIT_FAILURE);
    }

    CreateChildProcess(filename, pipefd);

    ReadFromPipe(pipefd);

    wait(nullptr);
}