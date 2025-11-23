#include<iostream>
#include<vector>
#include<string>
#include<fstream>

const int n = 5; // number of processes
const int m = 3; // number of resource types

void readInput(const std::string&, std::vector<int>&, 
    std::vector<std::vector<int>>&, std::vector<std::vector<int>>&);
std::vector<int> parse(std::string);


int main() {

    const std::string inputFile = "input.txt";

    std::vector<int> available;
    std::vector<std::vector<int>> max;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> need;

    readInput(inputFile, available, max, allocation);

    std::cout << "Allocation Matrix: " << std::endl;
    for (int i = 0; i < allocation.size(); ++i) {
        for (int j = 0; j < allocation[i].size(); ++j) {
            std::cout << allocation[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Max Matrix: " << std::endl;
    for (int i = 0; i < max.size(); ++i) {
        for (int j = 0; j < max[i].size(); ++j) {
            std::cout << max[i][j] << " ";
        }
        std::cout << std::endl;
    }


    std::cout << "Available resources: ";
    for (auto i : available) {
        std::cout << i << " ";
    }
    std::cout << std::endl;



}

void readInput(const std::string& inStr, std::vector<int>& available,
    std::vector<std::vector<int>>& max, std::vector<std::vector<int>>& allocation)
{

    std::ifstream in(inStr);
    if (!in) {
        std::cerr << "Failed to open file: " << inStr << std::endl;
        exit(1);
    }

    std::string line;
    while(std::getline(in,line)) {
        if(line.find("allocation") != std::string::npos){
            int i = 0;
            auto itr = line.begin();
            std::string tmp;
            std::vector<int> tmpVec;
            while (itr != line.end()) {
                std::cerr << *itr << std::endl;
                if (*itr == '{') {
                    allocation.push_back(tmpVec);
                    tmpVec.clear();
                    ++i;
                }
                else if (*itr == '}') {
                    tmpVec.push_back(std::stoi(tmp));
                    tmp = "";
                }
                else if (*itr == ',') {
                    tmpVec.push_back(std::stoi(tmp));
                    tmp = "";
                }
                else if (*itr > 47 && *itr < 58)
                    tmp += *itr;
                ++itr;
            }
            allocation.push_back(tmpVec);
        }
        else if(line.find("max") != std::string::npos) {
            std::cerr << "made it 1" <<  std::endl;
            int i = 0;
            auto itr = line.begin();
            std::string tmp;
            std::vector<int> tmpVec;
            while (itr != line.end()) {
                std::cerr << *itr << std::endl;
                if (*itr == '{') {
                    max.push_back(tmpVec);
                    tmpVec.clear();
                    ++i;
                }
                else if (*itr == '}') {
                    tmpVec.push_back(std::stoi(tmp));
                    tmp = "";
                }
                else if (*itr == ',') {
                    tmpVec.push_back(std::stoi(tmp));
                    tmp = "";
                }
                else if (*itr > 47 && *itr < 58)
                    tmp += *itr;
                ++itr;
            }
            max.push_back(tmpVec);

        }
        else if(line.find("available") != std::string::npos) {
            auto itr = line.begin();
            std::string tmp;
            while (itr != line.end()) {
                if (*itr == ',') {
                    available.push_back(std::stoi(tmp));
                    tmp = "";
                }
                else if (*itr > 47 && *itr < 58)
                    tmp += *itr;
                ++itr;
            }
            available.push_back(std::stoi(tmp));
        }
    }

}

