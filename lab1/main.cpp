#include "lab1.h"


int main() {

    std::ostringstream output;

    std::cout << "Введите имя файла: ";
    std::string filename;
    std::cin >> filename;

    MainTestFunction(filename, output);
    
    return 0;
}