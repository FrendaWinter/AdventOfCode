#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Part 1
	vector<string> input;
	string filename = "data/input_day_09.txt";
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

    string s = input[0];
    string tmp;
    for (int i = 0; i < s.length(); i++) {
        int n = std::stoi(std::to_string(s[i]));

        if (i % 2 == 0) {
            tmp.append(std::string(n, i + '0'));
        } else {
            tmp.append(std::string(n, '.'));
        }
    }

    cout << tmp << endl;
    cout << "Result: " << result << endl;
}
