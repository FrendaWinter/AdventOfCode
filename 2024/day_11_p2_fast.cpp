#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> input;
    string filename = "data/input_day_11.txt";
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
    std::map<long long int, long long int> countUniqueStones;
    // Init value
    for (int i = 0; i < input.size(); i++)
    {
        std::stringstream ss(input[i]);
        int num;
        while (ss >> num)
        {
            countUniqueStones.insert(std::make_pair(num, 1));
        }
    }

    for (int i = 0; i < 75; i++)
    {
        std::map<long long int, long long int> tmp = countUniqueStones;

        for (auto stone : tmp) {
            if (stone.first == 0)
            {
                // Stone from 0 -> 1, so stone[0] -= count of stone 0
                // Stone[1] += count of stone 0
                countUniqueStones[0] -= stone.second;
                if (countUniqueStones.count(1) > 0) {
                    countUniqueStones[1] += stone.second;
                } else {
                    countUniqueStones[1] = stone.second;
                }
                continue;
            }

            if (std::to_string(stone.first).length() % 2 == 0)
            {
                string s = std::to_string(stone.first);
                string firstHalf, secondHalf;
                for (int j = 0; j < s.length(); j++)
                {
                    if (j < s.length() / 2)
                    {
                        firstHalf += s[j];
                        continue;
                    }
                    secondHalf += s[j];
                }
                // stone -> 2 stones
                long long int firstNum = std::stoi(firstHalf);
                long long int secondNum = std::stoi(secondHalf);
                // Count -- for current stone
                countUniqueStones[stone.first] -= stone.second;
                // ++ count for first half stone
                if (countUniqueStones.count(firstNum) > 0)
                {
                    countUniqueStones[firstNum] += stone.second;
                } else {
                    countUniqueStones[firstNum] = stone.second;
                }
                // ++ count for second half stone
                if (countUniqueStones.count(secondNum) > 0)
                {
                    countUniqueStones[secondNum] += stone.second;
                }
                else
                {
                    countUniqueStones[secondNum] = stone.second;
                }
                continue;
            }
            
            // Stone of case 3
            countUniqueStones[stone.first] -= stone.second;

            long long int newStone = stone.first * 2024;
            if (countUniqueStones.count(newStone) > 0)
            {
                countUniqueStones[newStone] += stone.second;
            }
            else
            {
                countUniqueStones[newStone] = stone.second;
            }
        }
    }

    for (auto uniqueStone : countUniqueStones)
    {
        result += uniqueStone.second;
    }

    cout << "Result: " << result << endl;
}
