#include<iostream>
#include<vector>
#include<string>
#include<fstream>

void readInput(const std::string&, std::vector<int>&, 
    std::vector<std::vector<int>>&, std::vector<std::vector<int>>&);

// compute the need matrix: need[i][j] = max[i][j] - allocation[i][j]
std::vector<std::vector<int>> computeNeed(const std::vector<std::vector<int>>& max,
                                          const std::vector<std::vector<int>>& allocation);

// banker's safety algorithm. Returns true and fills safeSeq when safe.
bool isSafe(const std::vector<int>& available,
            const std::vector<std::vector<int>>& allocation,
            const std::vector<std::vector<int>>& max,
            std::vector<int>& safeSeq);

int main() {

    const std::string inputFile = "input.txt";

    std::vector<int> available;
    std::vector<std::vector<int>> max;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> need;

    readInput(inputFile, available, max, allocation);

    // compute need and check safety using Banker's algorithm
    need = computeNeed(max, allocation);
    std::vector<int> safeSeq;
    if (isSafe(available, allocation, max, safeSeq)) {
        std::cout << "Safe state. Safe sequence: ";
        for (size_t i = 0; i < safeSeq.size(); ++i) {
            std::cout << "P" << safeSeq[i];
            if (i + 1 < safeSeq.size()) std::cout << " -> ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Unsafe state." << std::endl;
    }



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
                if (*itr == '}') {
                    tmpVec.push_back(std::stoi(tmp));
                    allocation.push_back(tmpVec);
                    tmpVec.clear();
                    ++i;
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
 
        }
        else if(line.find("max") != std::string::npos) {
            int i = 0;
            auto itr = line.begin();
            std::string tmp;
            std::vector<int> tmpVec;
            while (itr != line.end()) {
                if (*itr == '}') {
                    tmpVec.push_back(std::stoi(tmp));
                    max.push_back(tmpVec);
                    tmpVec.clear();
                    ++i;
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


std::vector<std::vector<int>> computeNeed(const std::vector<std::vector<int>>& max,
                                          const std::vector<std::vector<int>>& allocation)
{
    std::vector<std::vector<int>> need;
    if (max.size() != allocation.size()) return need;
    need.resize(max.size());
    for (size_t i = 0; i < max.size(); ++i) {
        size_t cols = std::min(max[i].size(), allocation[i].size());
        need[i].resize(cols);
        for (size_t j = 0; j < cols; ++j) need[i][j] = max[i][j] - allocation[i][j];
    }
    return need;
}

bool isSafe(const std::vector<int>& available,
            const std::vector<std::vector<int>>& allocation,
            const std::vector<std::vector<int>>& max,
            std::vector<int>& safeSeq)
{
    safeSeq.clear();
    size_t nproc = allocation.size();
    if (nproc == 0) return false;
    size_t nres = available.size();

    auto need = computeNeed(max, allocation);

    std::vector<int> work = available;
    std::vector<bool> finish(nproc, false);

    for (size_t count = 0; count < nproc; ++count) {
        bool found = false;
        for (size_t p = 0; p < nproc; ++p) {
            if (finish[p]) continue;
            bool ok = true;
            for (size_t r = 0; r < nres; ++r) {
                int needpr = 0;
                if (p < need.size() && r < need[p].size()) needpr = need[p][r];
                if (needpr > work[r]) { ok = false; break; }
            }
            if (ok) {
                // this process can finish
                for (size_t r = 0; r < nres; ++r) {
                    if (r < allocation[p].size()) work[r] += allocation[p][r];
                }
                safeSeq.push_back(static_cast<int>(p));
                finish[p] = true;
                found = true;
                break;
            }
        }
        if (!found) break;
    }

    for (bool f : finish) if (!f) return false;
    return true;
}
