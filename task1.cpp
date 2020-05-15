#include <iostream>
#include <sstream> 
#include "task1.h"
int main(int argc, char* argv[]){
    Task1 task1;
    task1.readInput(argv[1]);
}

void Task1::readInput(std::string input){
    std::istringstream ss(input);
    std::string token;

    getline(ss, token, '\n');
    int numLine = std::stoi(token); 

    for(int i = 0; i <= numLine; i++){
        getline(ss, token, '\n');
        while(getline(ss, token, ' ')){
            //how to store grammar production 
        }
    }
}