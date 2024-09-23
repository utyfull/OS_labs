#ifndef LAB_3_H
#define LAB_3_H

#include <iostream>
#include <unistd.h>    
#include <sys/wait.h>  
#include <fcntl.h>     
#include <sstream>     
#include <string>

void process_data(int write_fd);
pid_t create_child_process(const std::string& filename, int pipefd[2]);
void read_from_pipe(int pipefd[2]);

#endif