#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void blink(vector<long long int> &stones)
{
    for (int i = 0; i < stones.size(); i++) {
        if (std::to_string(stones[i]).length() == 1 && stones[i] - '0' == 0)
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
            i += 2;
            continue;
        }

        stones[i] *= 1024;
    }
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

    for (int i = 0; i < 25; i++) {
        blink(stones);
    }
    cout << "Result: " << stones.size() << endl;
}
