#ifndef LAB_1_H
#define LAB_1_H

#include <iostream>
#include <unistd.h>    
#include <sys/wait.h>  
#include <fcntl.h>     
#include <sstream>     
#include <string>
#include <format>
#include <cerrno>
#include <cstring>

void CreateChildProcess(const std::string& filename, int pipefd[2]);
void ReadFromPipe(int pipefd[2], std::ostringstream& output);
void MainTestFunction(const std::string& filename, std::ostringstream& output);

#endif