#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<string> input;

const std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}, // Left
    {-1, 0}, // Up
};

// Recursive function to find all valid paths
void findTrail(std::set<std::pair<int, int>> &trails, int i, int j, int ref)
{
    if (input[i][j] == '9') // Base case: reached height 0
        trails.emplace(std::make_pair(i, j));

    // Explore all four directions
    for (auto direction : directions)
    {
        int ni = i + direction.first;
        int nj = j + direction.second;

        // Check bounds
        if (ni >= 0 && ni < input.size() && nj >= 0 && nj < input[ni].size())
        {
            // Check if the next cell is one height lower
            if (input[ni][nj] == '0' + ref + 1)
            {
                findTrail(trails, ni, nj, ref + 1);
            }
        }
    }
}

int countScore(int i, int j) {
    std::set<std::pair<int, int>> trails;
    findTrail(trails, i, j, 0);
    return trails.size();
}

int main(int argc, char *argv[])
{
    // Part 1
	string filename = "data/input_day_10.txt";
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
            if (input[i][j] == '0') {
                result += countScore(i, j);
            }
        }
    }

    cout << "Result: " << result << endl;
}
