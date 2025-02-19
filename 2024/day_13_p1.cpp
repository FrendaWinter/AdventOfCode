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

    int result = 0;

    std::vector<std::pair<int, int>> buttonA;
    std::vector<std::pair<int, int>> buttonB;
    std::vector<std::pair<int, int>> prizes;

    std::regex patternA("Button A: X\\+(-?\\d+), Y\\+(-?\\d+)");
    std::regex patternB("Button B: X\\+(-?\\d+), Y\\+(-?\\d+)");
    std::regex patternP("Prize: X\\=(-?\\d+), Y\\=(-?\\d+)");
    for (int i = 0; i < input.size(); i++)
    {
        std::smatch matches;

        if (std::regex_search(input[i], matches, patternA))
        {
            if (matches.size() == 3)
            {
                int x = std::stoi(matches[1].str());
                int y = std::stoi(matches[2].str());

                buttonA.push_back(std::make_pair(x, y));
            }
        }

        if (std::regex_search(input[i], matches, patternB))
        {
            if (matches.size() == 3)
            {
                int x = std::stoi(matches[1].str());
                int y = std::stoi(matches[2].str());

                buttonB.push_back(std::make_pair(x, y));
            }
        }

        if (std::regex_search(input[i], matches, patternP))
        {
            if (matches.size() == 3)
            {
                int x = std::stoi(matches[1].str());
                int y = std::stoi(matches[2].str());

                prizes.push_back(std::make_pair(x, y));
            }
        }
    }

    // for (int i = 0; i < buttonA.size(); i++)
    // {
    // cout << buttonA[i].first << " " << buttonA[i].second << endl;
    // cout << buttonB[i].first << " " << buttonB[i].second << endl;
    // cout << prizes[i].first << " " << prizes[i].second << endl;
    // }

    for (int i = 0; i < buttonA.size(); i++)
    {
        int maxB = 0;
        std::pair<int, int> countPush(0, 0);
        for (int j = 0; j < 101; j++)
        {
            // Find maxB that have possible minA
            if (j * buttonB[i].first <= prizes[i].first && j * buttonB[i].second < prizes[i].second &&
                (prizes[i].first - j * buttonB[i].first) % buttonA[i].first == 0 &&
                (prizes[i].second - j * buttonB[i].second) % buttonA[i].second == 0)
            {
                maxB = j;
                // find minA from MaxB, minA must < 101 and fit both first and second
                int minA = (prizes[i].first - maxB * buttonB[i].first) / buttonA[i].first;
                if (minA < 101 && minA * buttonA[i].first == prizes[i].first - maxB * buttonB[i].first &&
                    minA * buttonA[i].second == prizes[i].second - maxB * buttonB[i].second)
                {
                    countPush = std::make_pair(minA, maxB);
                }
            }
        }
        // Count token
        result += 3 * countPush.first + countPush.second;
    }

    cout << "Result: " << result << endl;
}
