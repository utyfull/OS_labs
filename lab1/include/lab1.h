#ifndef LAB_3_H
#define LAB_3_H

#include <iostream>
#include <unistd.h>    
#include <sys/wait.h>  
#include <fcntl.h>     
#include <sstream>     
#include <string>

void ProcessData(int write_fd);
void CreateChildProcess(const std::string& filename, int pipefd[2]);
void ReadFromPipe(int pipefd[2]);
void MainTestFunction(const std::string& filename);

#endif