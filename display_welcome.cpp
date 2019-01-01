#include <fstream>
#include <iostream>

void welcome(void);

void welcome(void)
{
    std::string line;
    std::ifstream inFile("welcome_art.txt");
    if(!inFile.is_open())
    {
        std::cerr << "cant open file";
        exit(0);
    }
    while(std::getline(inFile,line))
    {
        std::cout << line << std::endl;
    }
    inFile.close();
}
