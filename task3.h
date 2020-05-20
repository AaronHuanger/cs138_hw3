#ifndef TASK3_H
#define TASK3_H
#include <vector> 
#include <string>
#include <unordered_map>
class Task3{
    public:
        void run();
        void readInput();
        void readOutput();
        void mentorOutput();
        std::string substitute(std::string replace, std::string replacer, std::string target);
        void termPurge();
        std::string termPurge(std::string target);
        void varPurge();
        
    private: 
        std::unordered_map<std::string, std::vector<std::string>> fixProd;
        std::unordered_map<std::string, std::vector<std::string>> prod;
        int varNumber = 1;
};

#endif