#include "lab1.h"

void CreateChildProcess(const std::string& filename, int pipefd[2]) {
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Ошибка при создании процесса" << std::endl;
        exit(1);
    }

    if (pid == 0) { // Дочерний процесс

        std::string pipeFdStr = std::to_string(pipefd[1]); 
        char* args[] = {
            const_cast<char*>("/workspaces/OS_labs/build/lab1/divergent"), 
            const_cast<char*>(filename.c_str()), 
            const_cast<char*>(pipeFdStr.c_str()), 
            nullptr
        };

        if (execvp(args[0], args) == -1) {
            perror("Ошибка при запуске дочерней программы");
            exit(1);
        }

        _exit(0);
    }
}

void ReadFromPipe(int pipefd[2], std::ostringstream& output) {
    close(pipefd[1]);

    // чтение данных из pipe и вывод их на экран
    char buffer[1024];
    int n;
    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        output.write(buffer, n);  
        std::cout.write(buffer, n);
    }

    close(pipefd[0]);
}

void MainTestFunction(const std::string& filename, std::ostringstream& output) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        std::cerr << "Ошибка при создании pipe" << std::endl;
        exit(1);
    }

    CreateChildProcess(filename, pipefd);

    ReadFromPipe(pipefd, output);

    wait(nullptr);
}