#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>
#include <regex>

using namespace std;

int main(int argc, char *argv[])
{
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

    std::vector<std::pair<long long int, long long int>> buttonA;
    std::vector<std::pair<long long int, long long int>> buttonB;
    std::vector<std::pair<long long int, long long int>> prizes;

    std::regex patternA("Button A: X\\+(-?\\d+), Y\\+(-?\\d+)");
    std::regex patternB("Button B: X\\+(-?\\d+), Y\\+(-?\\d+)");
    std::regex patternP("Prize: X\\=(-?\\d+), Y\\=(-?\\d+)");
    for (long long int i = 0; i < input.size(); i++)
    {
        std::smatch matches;

        if (std::regex_search(input[i], matches, patternA))
        {
            if (matches.size() == 3)
            {
                long long int x = std::stoi(matches[1].str());
                long long int y = std::stoi(matches[2].str());

                buttonA.push_back(std::make_pair(x, y));
            }
        }

        if (std::regex_search(input[i], matches, patternB))
        {
            if (matches.size() == 3)
            {
                long long int x = std::stoi(matches[1].str());
                long long int y = std::stoi(matches[2].str());

                buttonB.push_back(std::make_pair(x, y));
            }
        }

        if (std::regex_search(input[i], matches, patternP))
        {
            if (matches.size() == 3)
            {
                long long int x = std::stoi(matches[1].str()) + 10000000000000;
                long long int y = std::stoi(matches[2].str()) + 10000000000000;

                prizes.push_back(std::make_pair(x, y));
            }
        }
    }

    // for (long long int i = 0; i < buttonA.size(); i++)
    // {
    // cout << buttonA[i].first << " " << buttonA[i].second << endl;
    // cout << buttonB[i].first << " " << buttonB[i].second << endl;
    // cout << prizes[i].first << " " << prizes[i].second << endl;
    // }

    for (int i = 0; i < buttonA.size(); i++)
    {
        long long int A = (prizes[i].first * buttonB[i].second - prizes[i].second * buttonB[i].first) / (buttonA[i].first * buttonB[i].second - buttonA[i].second * buttonB[i].first);
        long long int B = (prizes[i].second * buttonA[i].first - prizes[i].first * buttonA[i].second) / (buttonA[i].first * buttonB[i].second - buttonA[i].second * buttonB[i].first);

        if (buttonA[i].first * A + buttonB[i].first * B == prizes[i].first && buttonA[i].second * A + buttonB[i].second * B == prizes[i].second)
        {
            result += 3 * A + B;
        }
    }

    cout << "Result: " << result << endl;
}
