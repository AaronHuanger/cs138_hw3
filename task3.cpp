#include <sstream>
#include <iostream>
#include "task3.h"
#include <set>
int main(int argc, char* argv[]){
    Task3 task3;
    //std::cout << task3.substitute("A", "D1", "ABA") << std::endl;
    //std::cout << task3.termPurge("aAaAaAaAb") << std::endl;
    task3.run();
}

void Task3::run(){
    readInput();
    while(!isCNF()){
        termPurge();
        varPurge();
    }
    readOutput();
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
        while(leftProd.find("_") != -1){
            leftProd.replace(leftProd.find("_"),1,"");
        }
        while(rightProd.find("_") != -1){
            rightProd.replace(rightProd.find("_"),1,"");
        }
        if(prod.find(leftProd) == prod.end()){ //if you cannot find production, make new vector
            /*if(rightProd.length() == 1 || (rightProd.length() == 2 && isupper(rightProd[0]) && isupper(rightProd[1]))){
                prod.insert(std::pair<std::string, std::vector<std::string>>(leftProd, {rightProd}));
            }
            fixProd.insert(std::pair<std::string, std::vector<std::string>>(leftProd, {rightProd}));
        }else{
            if(rightProd.length() == 1 || (rightProd.length() == 2 && isupper(rightProd[0]) && isupper(rightProd[1]))){
                prod.at(leftProd).push_back((rightProd));
            }
            fixProd.at(leftProd).push_back((rightProd));
        }*/
            prod.insert(std::pair<std::string, std::vector<std::string>>(leftProd, {rightProd}));
        }else{
            prod.at(leftProd).push_back((rightProd));
        }
    }
    //---------------------------testing purposes------------------------------------------------------------->s
    /*for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        std::cout << it->first << " => ";
        for(int i = 0; i < prod.at(it->first).size(); i++){
            std::cout << prod.at(it->first).at(i) << " " ;
        }
        std::cout << "\n";
    }*/
}
bool Task3::isCNF(){
    bool isCNF = true;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        for(int i = 0; i < it->second.size(); i++){
            std::string temp = it->second[i];
            int varCount = 0;
            int termCount = 0;
            for(int j = 0; j < temp.length(); j++){ //iterate through every letter of the string
                if(isdigit(temp[j])){ //do nothing if you see a digit 
                    continue;
                }else if(islower(temp[j]) || temp.substr(j,1) == "_"){
                    termCount++;
                }else if(isupper(temp[j])){
                    varCount++;
                }
            }
            if(termCount > 1 || (varCount > 0 && termCount > 0) || varCount > 2){
                isCNF = false;
            }
        }
    }
    return isCNF;
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
        for(int i = 0; i < it->second.size(); i++){
            std::cout << it->first << " ";
            std::cout << it->second[i] << std::endl;
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
void Task3::termPurge(){
    std::string newVar = "X" + std::to_string(varNumber);
    //std::unordered_map<std::string, std::vector<std::string>> tempProds;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        //go through every element and remove and make it so that any variable that contains more than 1 term or 
        //contains a terminal along with a variable should be removed. while loop should be implemented in the case
        //where there are many different terms.
        for(int i = 0; i < it->second.size(); i++){ //iterate through every right hand side of the string
            std::string temp = it->second[i];
            std::set<std::string> diffTerms;
            int varCount = 0;
            int termCount = 0;
            for(int j = 0; j < temp.length(); j++){ //iterate through every letter of the string
                if(isdigit(temp[j])){ //do nothing if you see a digit 
                    continue;
                }else if(islower(temp[j]) || temp.substr(j,1) == "_"){
                    termCount++;
                    if(diffTerms.find(temp.substr(j,1)) == diffTerms.end()){
                        diffTerms.insert(temp.substr(j,1));
                    }
                }else if(isupper(temp[j])){
                    varCount++;
                }
            }
            if(termCount > 1 || (varCount > 0 && termCount >0)){ //replace terminals with variables. 
                for(std::set<std::string>::iterator its=diffTerms.begin(); its!=diffTerms.end(); ++its){
                    //std::cout << it->second[i] << std::endl;
                    //it->second[i] = substitute(*its, newVar, it->second[i]);
                    while(it->second[i].find(*its) != -1){
                        it->second[i].replace(it->second[i].find(*its),1, newVar);
                    }
                    prod.insert(std::pair<std::string, std::vector<std::string>>(newVar, {*its}));
                    ++varNumber;
                    newVar = "X" + std::to_string(varNumber);
                }
            }
            //reset all count variables;
            varCount = 0;
            termCount = 0;
            diffTerms.clear();
        }
    }
    //error: couldn't transfer vector portion of fix prod into prod correctly.
    //transfer all elements of fixProd to prod
    /*for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=fixProd.begin(); it!=fixProd.end(); ++it){
        for(int i = 0; i < it->second.size(); i++){
            if(prod.begin)
        }
    }*/
}
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
            }*/
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
}
void Task3::varPurge(){
    std::string digits = "";
    int varCount = 0; 
    std::string temp;
    std::string newVar;
    std::vector<std::string> vars;
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=prod.begin(); it!=prod.end(); ++it){
        for(int i = 0; i < prod.at(it->first).size(); i++){
            temp = it->second[i];
            for(int i = 0; i < temp.length(); i++){
                if(islower(temp[i])){
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
            newVar = "X" + std::to_string(varNumber);
            while(vars.size() > 2){                
                prod.insert(std::pair<std::string, std::vector<std::string>>(newVar, {vars[0] + vars[1]}));
                vars.erase(vars.begin());
                vars.shrink_to_fit();
                vars[0] = newVar;
                varNumber++;
                newVar = "X" + std::to_string(varNumber);
            }
            if(vars.size() == 2){
                prod.at(it->first).at(i) = vars[0] + vars[1];
            }
            vars.clear();
        }
    }
    /*//transfer all elements of fixProd to prod
    for (std::unordered_map<std::string, std::vector<std::string>>::iterator it=fixProd.begin(); it!=fixProd.end(); ++it){
        prod.insert(*it);
    }   */
}