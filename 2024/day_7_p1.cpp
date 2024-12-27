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

int main(int argc, char *argv[])
{
    // Part 1
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

	// Idea
	// Count number of operation n - 1
	// Binary number from 0 to n - 1, each number = operations order
	// 00 = {+ +}, 010 = {+ * +}
	// Count all possible result, add to result
    int mapSize = input.size();
    std::pair<long int, std::vector<int>> inputMap[mapSize];

    for (int i = 0; i < mapSize; i++) {
        parseInput(input[i], inputMap[i]);
    }

    for (int i = 0; i < mapSize; i++) {
        int exponent = inputMap[i].second.size() - 1;

        for (int j = 0; j < pow(2, exponent); j++)
        {
            std::string s = std::bitset<32>(j).to_string();

            s = s.substr(s.length() - exponent);
            long int tmp = inputMap[i].second[0];
            for (int k = 0; k < inputMap[i].second.size() - 1; k++)
            {
                
                if (s[k] == '0')
                {
                    tmp += inputMap[i].second[k + 1];
                }

                if (s[k] == '1')
                {
                    tmp *= inputMap[i].second[k + 1];
                }
            }

            if (tmp == inputMap[i].first) {
                result += inputMap[i].first;
                break;
            }
        }
    }

    cout << "Result: " << result << endl;
}
