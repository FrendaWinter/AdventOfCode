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

string convertToTernary(int n, const size_t &requiredLength)
{
    if (n == 0)
        return std::string(requiredLength, '0');
    
    std::string str_ret;
    while (n > 0)
    {
        int digitofternary = n % 3;
        n /= 3;
        std::string str = std::to_string(digitofternary);
        str_ret.insert(0, str);
    }

    if (str_ret.length() == requiredLength)
    {
        return str_ret;
    }

    return std::string(requiredLength - str_ret.length(), '0') + str_ret;
}

bool isMatchBinary(const long int &base, const std::vector<int>& compare) {

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

bool isMatchTernary(const long int &base, const std::vector<int> &compare) {
    int exponent = compare.size() - 1;

    for (int j = 0; j < pow(3, exponent); j++)
    {
        std::string s = convertToTernary(j, exponent);

        long int tmp = compare[0];

        if (base == 192) {
            cout << s << endl;
        }
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

            if (s[k] == '2')
            {
                tmp = stol(std::to_string(tmp) + std::to_string(compare[k + 1]));
            }
        }

        if (tmp == base)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    // Part 2
	vector<string> input;
	string filename = "data/input_day_07.txt";
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
        if (isMatchBinary(inputMap[i].first, inputMap[i].second))
        {
            result += inputMap[i].first;
        }
        else
        {
            if (isMatchTernary(inputMap[i].first, inputMap[i].second)) {
                // cout << inputMap[i].first << endl;
                result += inputMap[i].first;
            };
        }
    }
    cout << "Result: " << result << endl;
}
