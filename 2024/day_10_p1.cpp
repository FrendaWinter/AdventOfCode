#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <math.h>

using namespace std;

vector<string> input;

const std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}, // Left
    {-1, 0}, // Up
};

int countPoint(int i, int j, int ref) 
{
    int result = 0;

    for (auto direction : directions) {
        if (input[i][j] == '0')
            return 1;
        
        i += direction.first;
        j += direction.second;

        if (i >= input.size() || i < 0) return 0;
        if (j >= input[i].size() || j < 0)
            return 0;


        
        if (input[i][j] == '0' + ref)
        {
            cout << i << " " << j << endl;
            cout << "in: " << input[i][j] << endl;
            result += countPoint(i, j, ref - 1);
        }
        else
        {
           continue;
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    // Part 1
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

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].length(); j++) {
            if (input[i][j] == '9') {
                result += countPoint(i, j, 9);
                // cout << result << endl;
            }
        }
    }

    cout << "Result: " << result << endl;
}
