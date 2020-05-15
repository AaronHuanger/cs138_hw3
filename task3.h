#ifndef TASK3_H
#define TASK3_H
#include <vector> 
#include <string>
#include <unordered_map>
class Task3{
    public:
        void readInput();
        void readOutput();
        void mentorOutput();
        std::string substitute(std::string replace, std::string replacer, std::string target);
        //std::string termPurge(std::string target);
        void varPurge();
        void termPurge();
        
    private: 
        std::unordered_map<std::string, std::vector<std::string>> prod;
        std::unordered_map<std::string, std::string> singleProds;
        int varNumber = 1;
};

#endif