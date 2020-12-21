#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> getFileValues(const std::string filePath, std::function<T(const std::string)> func)
{
    std::ifstream file;
    std::vector<T> values;
    std::string str;

    file.open (filePath, std::ifstream::in);

    if (file.is_open()) {
        while (std::getline(file, str)) {
            values.push_back(func(str));
        }

        file.close();
    }

    return values;
}

int moveLeft(std::vector<int>::iterator iterLow, const std::vector<int>::iterator iterEnd, std::vector<int>::iterator iterHigh, const int target)
{
    const int highValue = (*iterHigh);

    // keep moving low left
    for(auto iter = iterLow; iter >= iterEnd; iter--)
    {
        const int result = (*iter) + highValue - target;

        std::cout << "low: " << *iter << " high: " << highValue << " == " << (*iter) + highValue << std::endl;

        // calculation found
        if (result == 0){
            return result;
        }

        else if (result < 0){
            // move right both values...
            return moveLeft(iterLow+1, iterEnd, iterHigh+1, target);
        }
    }

    // move both left as none of the combinations
    return moveLeft(iterLow-1, iterEnd, iterHigh-1, target);
}

int moveRight(std::vector<int>::iterator iterHigh, const std::vector<int>::iterator iterEnd, std::vector<int>::iterator iterLow, const int target)
{
    const int lowValue = *iterLow;

    // keep moving low left
    for(auto iter = iterHigh; iter <= iterEnd; iter++)
    {
        const int result = *iter + lowValue - target;

        // calculation found
        if (result == 0){
            return result;
        }

        else if (result > 0){
            // move left both values...
            return moveRight(iterHigh-1, iterEnd, iterLow-1, target);
        }
    }

    // move both right as none of the combinations
    return moveRight(iterHigh+1, iterEnd, iterLow+1, target);
}

int main() {
    std::cout << "AoC 2020 Task Day1..." << std::endl;

    auto values = getFileValues<int>("C:\\Users\\Silvio\\AoC\\day1\\input.txt", [](const std::string line) -> int {
       return std::stoi(line);
    });

    std::sort(values.begin(), values.end());

    const int middleElement = values.size() / 2;
    const int target        = 2020;

    std::vector<int>::iterator iterLow  = std::next(values.begin(), middleElement-1);
    std::vector<int>::iterator iterHigh = std::next(values.begin(), middleElement);

    const int result = (*iterLow) + (*iterHigh) - target;

    if(result > 0)
    {
        const int fR = moveLeft(iterLow, values.begin(), iterHigh, target);
        std::cout << "FR: " << fR << std::endl;
    }
    else
    {
        const int fR = moveRight(iterHigh, values.end(), iterLow, target);
        std::cout << "FR: " << fR << std::endl;
    }

    return 0;
}
