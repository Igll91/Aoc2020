#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>

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

typedef std::vector<int>::iterator iter;

int findThree(const iter primary, const iter secondary, const iter tertiary, const iter end, const int target)
{
    for(auto currentPrimary = primary; currentPrimary >= (end + 2); currentPrimary--)
    {
        const int primaryValue = (*currentPrimary);

        // keep moving secondary iterator till end (start of vector)
        for (auto currentSecondary = currentPrimary - 1; currentSecondary >= (end + 1); currentSecondary--)
        {
            const int secondaryValue = (*currentSecondary);

            // keep moving tertiary iterator from start of the vector till secondary iterator
            for (auto currentTertiary = currentSecondary - 1; currentTertiary >= end; currentTertiary--)
            {
                const int tertiaryValue = (*currentTertiary);
                const int result = primaryValue + secondaryValue + tertiaryValue;

//                std::cout << "primary: " << primaryValue << " secondary: " << secondaryValue << " tertiary: " << tertiaryValue << " == " << result << std::endl;

                if (result == target) {
                    std::cout << "primary: " << primaryValue << " secondary: " << secondaryValue << " tertiary: " << tertiaryValue << " == " << result << std::endl;

                    std::cout << std::distance(end, currentPrimary) << std::endl;
                    std::cout << std::distance(end, currentSecondary) << std::endl;
                    std::cout << std::distance(end, currentTertiary) << std::endl;

                    return result;
                }
            }
        }
    }

    return -1;
}

int moveLeft(std::vector<int>::iterator iterLow, const std::vector<int>::iterator iterEnd, std::vector<int>::iterator iterHigh, const int target)
{
    const int highValue = (*iterHigh);

    // keep moving low left
    for(auto currentIter = iterLow; currentIter >= iterEnd; currentIter--)
    {
        const int result = (*currentIter) + highValue - target;

        std::cout << "low: " << *currentIter << " high: " << highValue << " == " << (*currentIter) + highValue << std::endl;

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

void firstPartOfTask(std::vector<int> values)
{
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
}

void secondPartOfTask(std::vector<int> values, const int target)
{
    const int lastElement = values.size() - 1;

    std::cout << "Num of elements: " << values.size() << std::endl;

    iter primary = std::next(values.begin(), lastElement);
    iter secondary = std::next(values.begin(), lastElement-1);
    iter tertiary = std::next(values.begin(), lastElement-2);

    findThree(primary, secondary, tertiary, values.begin() ,target);
}

int main()
{
    std::cout << "AoC 2020 Task Day1..." << std::endl;

    auto values = getFileValues<int>("C:\\Users\\Silvio\\AoC\\day1\\input.txt", [](const std::string line) -> int {
       return std::stoi(line);
    });

    std::sort(values.begin(), values.end());

    secondPartOfTask(values, 2020);

    return 0;
}
