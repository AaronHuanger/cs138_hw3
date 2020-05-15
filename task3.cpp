#include <sstream>
#include <iostream>
#include "task3.h"
int main(int argc, char* argv[]){
    Task3 task3;
    //std::cout << task3.substitute("A", "D1", "ABA") << std::endl;
    //std::cout << task3.termPurge("aAaAaAaAb") << std::endl;
    task3.readInput();
    task3.readOutput();
}

void Task3::readInput(){
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

        if(prod.find(leftProd) == prod.end()){ //if you cannot find production, make new vector
            prod.insert(std::pair<std::string, std::vector<std::string>>(leftProd, {(rightProd)}));
        }else{
            prod.at(leftProd).push_back((rightProd));
        }
        if(rightProd.length() == 1 && islower(rightProd[0])){
            singleProds.insert(std::pair<std::string, std::string> (rightProd, leftProd)); // stores single unit productions.
        }
    }
    termPurge();
    varPurge();
    //---------------------------testing purposes------------------------------------------------------------->s
    /*for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        std::cout << it->first << " => ";
        for(int i = 0; i < prod.at(it->first).size(); i++){
            std::cout << prod.at(it->first).at(i) << " " ;
        }
        std::cout << "\n";
    }*/
}
void Task3::mentorOutput(){
    int numProd = 0;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        numProd += it->second.size();
    }
    std::cout << numProd <<std::endl;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        for(int i = 0; i < prod.at(it->first).size(); i++){
            std::cout << it->first << "->";
            std::cout << prod.at(it->first).at(i) << std::endl;
        }
    }
}
void Task3::readOutput(){
    int numProd = 0;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        numProd += it->second.size();
    }
    std::cout << numProd <<std::endl;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        for(int i = 0; i < prod.at(it->first).size(); i++){
            std::cout << it->first << " ";
            std::cout << prod.at(it->first).at(i) << std::endl;
        }
    }
}

std::string Task3::substitute(std::string replace, std::string replacer, std::string target){
    std::string result = target;
    while(result.find(replace) != result.npos){
        result = result.substr(0, result.find(replace)) + replacer + result.substr(result.find(replace) + replace.length());
    }
    return result;
}
/*
std::string Task3::termPurge(std::string target){
    std::vector<std::string> terms;
    std::string temp = target;
    int numVar = 0;
    int numTerm = 0;
    for(int i = 0; i < temp.length(); i++){
        if(isdigit(temp[i])){
            continue;
        }else if(islower(temp[i]) || temp.substr(i,1) == "_"){
            numTerm++;
            terms.push_back(temp.substr(i,1));
            /*for(int i = 0; i < terms.size(); i++){
                std::cout << terms[i] << std::endl;
            }*/ /*
        }else if(isupper(temp[i])){
            numVar++;
        }
    }
    if(numVar > 0 || numTerm > 1){
        std::string newVar = "X" + std::to_string(varNumber);
        for(int i = 0; i < terms.size(); i++){
            temp = substitute(terms[i], newVar, temp);
            
            prod.insert(std::pair<std::string, std::vector<std::string>>(newVar, {terms[i]}));

            varNumber++;
            newVar = "X" + std::to_string(varNumber); //continues to execute the loop. Not inteded but it still works. 
        }
    }
    //std::cout << "numVar: " << numVar << "numTerm: " << numTerm << std::endl;
    return temp;
}*/
void Task3::termPurge(){
    int varCount = 0; 
    int termCount = 0;
    std::string temp;
    std::vector<std::string> terms;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){ //gets all the terms that need to be purged
        for(int i = 0; i < prod.at(it->first).size(); i++){
            temp = prod.at(it->first).at(i);
            for(int i = 0; i < temp.length(); i++){
                if(isdigit(temp[i])){
                    continue;
                }else if(islower(temp[i]) || temp.substr(i,1) == "_"){
                    termCount++;
                }else if(isupper(temp[i])){
                    varCount++;
                }
                if((varCount > 0 && termCount > 0) || termCount > 2){
                    terms.push_back(temp.substr(i,1));
                }
                termCount =0;
                varCount = 0;
            }
        }
    }   
    //term purging begins here
    std::string leftProd = "";
    newVar = "X" + std::to_string(varNumber);
    for(int i = 0; i < terms.size(); i++){
        if(singleProds.find(terms[i]) != singleProds.end()){
            leftProd = singleProds.at(terms[i]);
            if(prod.at(leftProd).size() > 1){
                leftProd = "";
            }   
        }
        if(leftProd == ""){
            varNumber++;
            newVar = "X" + std::to_string(varNumber);
        }
        for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){ //gets all the terms that need to be purged
            for(int i = 0; i < prod.at(it->first).size(); i++){
                temp = prod.at(it->first).at(i);
                for(int i = 0; i < temp.length(); i++){
                    if(temp.substr(i,1) == terms[i]){
                        if(leftProd != ""){
                            prod.at(it->first).at(i)
                        }
                    }
                }
            }
        }   
    }
    
}
void Task3::varPurge(){
    std::string digits = "";
    int varCount = 0; 
    std::string temp;
    std::vector<std::string> vars;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        for(int i = 0; i < prod.at(it->first).size(); i++){
            temp = prod.at(it->first).at(i);
            for(int i = 0; i < temp.length(); i++){
                if(islower(temp[i]) || temp.substr(i,1) == "_"){
                    continue;
                }else if(isdigit(temp[i])){
                    digits += temp.substr(i,1);
                }else if(isupper(temp[i])){
                    if(varCount != 0){
                        vars[varCount-1] += digits;
                        digits = "";
                    }
                    varCount++;
                    vars.push_back(temp.substr(i,1));
                }
            }
            if(varCount != 0){ // catches the last digits
                vars[varCount-1] += digits;
                digits = "";
            }
            varCount = 0;
            std::string newVar = "X" + std::to_string(varNumber);
            while(vars.size() > 2){                
                prod.insert(std::pair<std::string, std::vector<std::string>>(newVar, {vars[0] + vars[1]}));
                vars.erase(vars.begin());
                vars.shrink_to_fit();
                vars[1] = newVar;
                varNumber++;
                newVar = "X" + std::to_string(varNumber);
            }
            if(vars.size() == 2){
                prod.at(it->first).at(i) = vars[0] + vars[1];
            }
            vars.clear();
        }
    }   
}