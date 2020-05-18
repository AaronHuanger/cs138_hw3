#include <iostream>
#include <sstream> 
#include "task1.h"
#include <bitset>
int main(int argc, char* argv[]){
    Task1 task1;
    task1.readInput();
    task1.readOutput();
}

void Task1::readInput(){
    int numProd;
    std::string tempProd;
    std::string leftProd;
    std::string rightProd;

    std::cin >> numProd;
    std::getline(std::cin, tempProd);
    for(int i = 0; i < numProd; i++){
        std::getline(std::cin, tempProd);
        leftProd = tempProd.substr(0, tempProd.find(" "));
        rightProd = tempProd.substr(tempProd.find(" ") + 1);

        p.insert(std::pair<std::string, std::string>(leftProd, rightProd));
    }
    findLambda();
    makeProductions();
    removeLambda();
}

void Task1::readOutput(){
    int pSize = p.size();
    std::cout << pSize << std::endl;
    /*for(int i = 0; i < pSize; i++){
        std::cout << p[i].first << " " << p[i].second << std::endl;
    }*/
    for (std::set<std::pair<std::string, std::string>>::iterator it=p.begin(); it!=p.end(); ++it)
    std::cout << it->first << " " << it->second << std::endl;
}

void Task1::onionize(){
    for(std::set<std::pair<std::string, std::string>>::iterator it = vnprime.begin(); it!= vnprime.end(); ++it){
        if(vn.find(*it) != vn.end()){
            //std::cout << "found something" <<std::endl;
        }else{
            vn.insert(*it);
            std::cout << "vn: " << it-> first << " " << it-> second <<  " " << std::endl;
        }
    }
}

void Task1::findLambda(){
    //inserts all lambda productions in vn
    for (std::set<std::pair<std::string, std::string>>::iterator it=p.begin(); it!=p.end(); ++it){ 
        if(it->second == "_"){
            vn.insert(*it);
            vnprime.insert(*it); //prevents vnprime from being empty. allows it to enter first while iteration
        }
    }
    while(!(vnprime.empty())){
        onionize();
        vnprime.clear();
        for (std::set<std::pair<std::string, std::string>>::iterator it=p.begin(); it!=p.end(); ++it){ 
            if(lambdaCheck(it->second)){
                if(vn.find(*it) == vn.end()){
                     vnprime.insert(*it);
                     //std::cout << "vprime: " << it-> first << " " << it-> second <<  " " << std::endl;
                }
            }
        }
    }
}

bool Task1::lambdaCheck(std::string second){
    bool letterIsLambda = false;
    bool isLambda = true;
    for(int i = 0; i < second.length(); i++){
        letterIsLambda = false;
        for(std::set<std::pair<std::string, std::string>>::iterator it=vn.begin(); it!=vn.end(); ++it){
            if(second.substr(i,1) == it->first){
                letterIsLambda = true;
            }
        }
        if(letterIsLambda == false){
            isLambda = false;
            break;
        }
    }
    return isLambda;
}

void Task1::makeProductions(){
    std::vector<int> positions;
    for(std::set<std::pair<std::string, std::string>>::iterator it=p.begin(); it!=p.end(); ++it){
        for(std::set<std::pair<std::string, std::string>>::iterator its=vn.begin(); its!=vn.end(); ++its){
            //std::cout << it->first << ": " << it->second << std::endl;
            if(it->second.find(its->first) != -1){
                positions.push_back(it->second.find(its->first));
            }
        } 
        for(int i = 0; i < positions.size(); i++){
            //std::cout << "Position: " << i << " : " << positions[i] <<std:: endl;
        }
        recursiveHelp(positions, it->first, it->second, 0);
        //std::cout << "GOT HERE" << std::endl;
        positions.clear();
        //std::cout << "Got here 2" << std::endl;
    }
}

void Task1::recursiveHelp(std::vector<int> positions, std::string first, std::string second, int pos){
    //std::cout << "positions.size() : " << positions.size() -1 << std::endl;
    //std::cout << "pos: " << pos <<std::endl;
    //std::cout <<  "True or False: " << (pos > positions.size()-1) << std::endl;
    if(pos == positions.size()){ // Note: position.size() -1 = some astronomically large number when the size of position is 0
        //std::cout << "doesit get here? " <<std::endl;
        return;
    }else{
        std::string temp;
        recursiveHelp(positions, first, second, pos +1);
        recursiveHelp(positions, first, second.replace(positions[pos],1,"_"), pos +1);
        temp = second;
        while(temp.find("_") != -1){
            temp.replace(temp.find("_"),1,"");
        }
        p.insert(std::pair<std::string, std::string> (first, temp));
    }
}
void Task1::removeLambda(){
    std::vector<std::set<std::pair<std::string, std::string>>::iterator> its;
    for(std::set<std::pair<std::string, std::string>>::iterator it=p.begin(); it!=p.end(); ++it){
        if(it->second == "_"){
            its.push_back(it);
            //p.erase(it);
        }
    }
    for(int i=0; i < its.size(); i++){
        p.erase(its[i]);
    }
}