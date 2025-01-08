#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>

using namespace std;

void blink(vector<long long int> &stones)
{
    for (int i = 0; i < stones.size(); i++) {
        if (std::to_string(stones[i]) == "0")
        {
            stones[i] = 1;
            continue;
        }

        if (std::to_string(stones[i]).length() %2 == 0) {
            string s = std::to_string(stones[i]);
            string firstHalf, secondHalf;
            for (int j = 0; j < s.length(); j++) {
                if (j < s.length()/2) {
                    firstHalf += s[j];
                    continue;
                }
                secondHalf += s[j];
            }

            long long int firstNum = std::stoi(firstHalf);
            long long int secondNum = std::stoi(secondHalf);

            stones.erase(stones.begin() + i);
            stones.insert(stones.begin() + i, {firstNum, secondNum});
            i ++;
            continue;
        }

        stones[i] *= 2024;
    }
}

int blink25WithSingleStone(const long long int &stone)
{
    vector<long long int> stones;
    stones.push_back(stone);
    for (int i = 0; i < 25; i++)
    {
        blink(stones);
    }
    return stones.size();
}

std::map<long long int, long long int> analyzeUnique(vector<long long int> stones)
{
    std::set<long long int> uniqueStones;
    std::map<long long int, long long int> countUniqueStones;
    for (int i = 0; i < stones.size(); i++)
    {
        uniqueStones.emplace(stones[i]);
    }

    for (auto uniqueStone : uniqueStones)
    {
        countUniqueStones.insert(std::make_pair(uniqueStone, 0));
    }

    for (int i = 0; i < stones.size(); i++)
    {
        countUniqueStones[stones[i]]++;
    }

    return countUniqueStones;
}

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

    vector<long long int> stones;
    for (int i = 0; i < input.size(); i++) {
        std::stringstream ss(input[i]);
        int num;
        while (ss >> num)
        {
            stones.push_back(num);
        }
    }

    long long int result = 0;
    // First 25 blinks
    for (int i = 0; i < 25; i++) {
        blink(stones);
    }

    std::map<long long int, long long int> countUniqueStones25 = analyzeUnique(stones);
    std::map<long long int, long long int> countUniqueStoneFor75Blink;
    // Next 50 blink
    for (const auto &pair : countUniqueStones25)
    {
        // Get 50 blink
        vector<long long int> stone50;
        stone50.push_back(pair.first);

        for (int i = 0; i < 25; i++) {
            blink(stone50);
        }

        std::map<long long int, long long int> countUniqueStones50 = analyzeUnique(stone50);
        for (auto uniqueStone50 : countUniqueStones50)
        {
            result += blink25WithSingleStone(uniqueStone50.first) * uniqueStone50.second * pair.second;
        }
    }

    cout << "Result: " << result << endl;
}
