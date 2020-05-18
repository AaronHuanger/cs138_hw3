#ifndef TASK1_H
#define TASK1_H

#include <string>
#include <vector>
#include <set>
class Task1
{
    public: 
        void readInput();
        void readOutput();
        void onionize();
        void findLambda(); //step1
        bool lambdaCheck(std::string second);
        void makeProductions(); //step2;
        void recursiveHelp(std::vector<int> positions, std::string first, std::string second, int pos);
        void removeLambda();
    private:
        std::set<std::pair<std::string, std::string>> p;
        std::set<std::pair<std::string, std::string>> vn;
        std::set<std::pair<std::string, std::string>> vnprime;
};
#endif