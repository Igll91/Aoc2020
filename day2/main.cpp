#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

class PasswordPolicy
{
public:
    std::string sequence;
    int limitLow;
    int limitHigh;

    PasswordPolicy(const std::string sequence, const int limitLow, const int limitHigh)
    {
        this->sequence  = sequence;
        this->limitHigh = limitHigh;
        this->limitLow  = limitLow;
    }

    bool isValid(const std::string password)
    {
        int occurrences             = 0;
        std::string::size_type pos  = 0;

        while ((pos = password.find(sequence, pos )) != std::string::npos) {
            ++occurrences;
            pos += sequence.length();
        }

        return occurrences >= limitLow && occurrences <= limitHigh;
    }
};

std::vector<std::pair<PasswordPolicy, std::string>> getFileValues(const std::string filePath)
{
    std::ifstream file;
    std::vector<std::pair<PasswordPolicy, std::string>> values;
    std::string str;

    file.open (filePath, std::ifstream::in);

    if (file.is_open()) {
        std::regex regexp("(\\d+)-(\\d+)\\s([a-z]):\\s(.*)");
        std::smatch match;

        while (std::getline(file, str)) {
            if(std::regex_search(str, match, regexp))
            {
                PasswordPolicy passwordPolicy(match[3], std::stoi(match[1]), std::stoi(match[2]));
                values.push_back({ passwordPolicy, match[4] });
            }
        }

        file.close();
    }

    return values;
}

void taskPartOne(std::vector<std::pair<PasswordPolicy, std::string>> values)
{
    int numOfValidPasswords = 0;
    for(auto val: values)
    {
        std::cout << val.first.sequence << " (" << val.first.limitLow << "," << val.first.limitHigh << ")" << " - " << val.second << std::endl;

        if(val.first.isValid(val.second)){
            numOfValidPasswords++;
        }
    }

    std::cout << "Num of valid passwords: " << numOfValidPasswords << std::endl;
}

int main() {
    std::cout << "Aoc 2020 task Day2!" << std::endl;

    auto values = getFileValues("../input.txt");

    std::cout << "Num of elements: " << values.size() << std::endl;

    taskPartOne(values);

    return 0;
}
