#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <math.h>

using namespace std;

void parseInput(const std::string &input, std::pair<long int, std::vector<int>> &output)
{
    std::stringstream ss(input);
    long int firstNumber;
    ss >> firstNumber;          // Parse the first number
    output.first = firstNumber; // Assign it to the pair's first element
    // Skip the colon if present
    char colon;
    ss >> colon;
    int num;
    while (ss >> num)
    {
        output.second.push_back(num);
    }
};

bool isMatch(const long int &base, const std::vector<int>& compare) {

    int exponent = compare.size() - 1;

    for (int j = 0; j < pow(2, exponent); j++)
    {
        std::string s = std::bitset<32>(j).to_string();

        s = s.substr(s.length() - exponent);
        long int tmp = compare[0];
        for (int k = 0; k < compare.size() - 1; k++)
        {

            if (s[k] == '0')
            {
                tmp += compare[k + 1];
            }

            if (s[k] == '1')
            {
                tmp *= compare[k + 1];
            }
        }

        if (tmp == base)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<long long, long long>> splitNumber(long long num)
{
    std::vector<std::pair<long long, long long>> result;
    std::string numStr = std::to_string(num);
    int len = numStr.length();

    // Generate all possible splits
    for (int i = 1; i < len; ++i)
    {
        long long firstPart = std::stoll(numStr.substr(0, i));
        long long secondPart = std::stoll(numStr.substr(i));

        // Add the pair to the result
        result.emplace_back(firstPart, secondPart);
    }

    return result;
}

std::vector<int> getFirtHalfOfVector(const std::vector<int> &base, const int &i) {
    std::vector<int> tmp;
    for (int x = 0; x < i; x++){
        tmp.push_back(base[i]);
    }
    return tmp;
}

std::vector<int> getSecondHalfOfVector(const std::vector<int> &base, const int &i)
{
    std::vector<int> tmp;
    for (int x = i; x < base.size(); x++)
    {
        tmp.push_back(base[i]);
    }
    return tmp;
}

int main(int argc, char *argv[])
{
    // Part 2
	vector<string> input;
	string filename = "data/input_test.txt";
    ifstream input_file(filename);

    if (input_file.is_open())

    {
        string line;
        while (std::getline(input_file, line))
        {
			input.push_back(line);
		}
        input_file.close();
    }
    else
    {
        cerr << "Error when open file" << endl;
    }

    long long int result = 0;
    int mapSize = input.size();
    std::pair<long int, std::vector<int>> inputMap[mapSize];

    for (int i = 0; i < mapSize; i++) {
        parseInput(input[i], inputMap[i]);
    }

    for (int i = 0; i < mapSize; i++) {
        if (isMatch(inputMap[i].first, inputMap[i].second)) {
            result += inputMap[i].first;
        } else {
            auto pairs = splitNumber(inputMap[i].first);
            for (const auto &pair : pairs)
            {
                for (int j = 1; j < inputMap[i].second.size(); j++) {
                    std::vector<int> firstHalf = getFirtHalfOfVector(inputMap[i].second, j);
                    std::vector<int> secondHalf = getSecondHalfOfVector(inputMap[i].second, j);

                    bool isFirstPartMatch = isMatch(pair.first, firstHalf);
                    bool isSecondPartMatch = isMatch(pair.second, secondHalf);

                    if (isFirstPartMatch && isSecondPartMatch) {
                        result += inputMap[i].first;
                        break;
                    }
                }
            }
        }
    }
    cout << "Result: " << result << endl;
}
